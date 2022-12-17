#include "GraphsToVisualize.h"
#include <math.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace System::Drawing;

Void GraphsToVisualize::VisualizationForm::onShown(System::Object^ sender, System::EventArgs^ e)
{
    array<Vertex^>^ vertices = gcnew array<Vertex^>(size); // инициализируется основной массив с вершинами, которые потом будут выводиться
    CalculatePositions(vertices); // рассчитываются позиции вершин в графе с использованием логики маршрутов и уровней
    VisualizeGraph(vertices); // отрисовываются вершины и линии между ними
    VisualizeTables(); // визуализируются нужные таблицы, кнопки, надписи и т.д.
}

// визуализирует граф
Void GraphsToVisualize::VisualizationForm::VisualizeGraph(array<Vertex^>^ vertices) // беру первую вершину, строю ее в начальной точке, прохожусь по ее строке в матрице и строю вершины, в которые из нее можно попасть 
{
    bool drawArrows = (taskName->Contains("Демукрон")) ? true : false;

    int radius = diameter / 2;
    int offset = radius / 2 - 5;
    pictureBox1->Image = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
    Pen^ pen = gcnew Pen(Color::Black, 2.0f);
    Brush^ brush = Brushes::Black;
    Brush^ whiteBrush = Brushes::White;
    Drawing::Font^ font = gcnew Drawing::Font("Arial", 14);
    Graphics^ graph = Graphics::FromImage(pictureBox1->Image);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (matrix[i][j] > 0)
            {
                graph->DrawLine(pen, vertices[i]->X + radius, vertices[i]->Y + radius,
                    vertices[j]->X + radius, vertices[j]->Y + radius);
                if (drawArrows)
                {
                    // найти длину начальной линии
                    int deltaX = (vertices[j]->X - vertices[i]->X);
                    int deltaY = (vertices[j]->Y - vertices[i]->Y);
                    float length = sqrt(deltaX * deltaX + deltaY * deltaY);

                    // найти отношение длины к разнице игриков
                    float ux = (float)deltaX / length;
                    float uy = (float)deltaY / length;

                    // находим новые значения разницы между координатами
                    length -= radius;
                    int newDeltaX = length * ux;
                    int newDeltaY = length * uy;

                    int newX = vertices[i]->X + newDeltaX + radius;
                    int newY = vertices[i]->Y + newDeltaY + radius;

                    ux = (float)newDeltaX / length;
                    uy = (float)newDeltaY / length;

                    float vx = -uy;
                    float vy = ux;

                    array<Point>^ arrow = gcnew array<Point>(3);
                    arrow[0] = Point(newX, newY);
                    arrow[1] = Point(round(newX - 20 * ux + 5 * vx),
                                      round(newY - 20 * uy + 5 * vy));
                    arrow[2] = Point(round(newX - 20 * ux - 5 * vx),
                                      round(newY - 20 * uy - 5 * vy));

                    graph->FillPolygon(brush, arrow);
                    graph->DrawPolygon(pen, arrow);
                }
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        graph->DrawEllipse(pen, vertices[i]->X, vertices[i]->Y, diameter, diameter);
        graph->FillEllipse(whiteBrush, vertices[i]->X, vertices[i]->Y, diameter, diameter);
        if (i < 9)
        {
            graph->DrawString(vertices[i]->Name, font, brush, vertices[i]->X + radius / 2, vertices[i]->Y + radius / 2.5);
        }
        else
        {
            graph->DrawString(vertices[i]->Name, font, brush, vertices[i]->X + radius / 2 - 5, vertices[i]->Y + radius / 2.5);
        }
    }
}

// добавляет вершину на уровень
void GraphsToVisualize::VisualizationForm::AddToLevel(int levelIndex, int vertexIndex, array<array<int>^>^ levels)
{
    int length = levels[levelIndex]->Length;
    Array::Resize(levels[levelIndex], length + 1);
    levels[levelIndex][length] = vertexIndex;
}

// рассчитывает позиции вершин
void GraphsToVisualize::VisualizationForm::CalculatePositions(array<Vertex^>^ vertices)
{
    array<array<int>^>^ levels = gcnew array<array<int>^>(size);
    array<int>^ markedVertices = gcnew array<int>(size);
    array<int>^ verticesOffsets = gcnew array<int>(size);

    int maxX = 0;
    int maxY = 0;
    int beforePrevVertex = 0;
    int prevVertex = 0;
    int currentVertex = 0;
    int amountOfLevels = 0;

    int xIncValue = 140;
    int xDefaultValue = 200;
    int yDefaultValue = this->pictureBox1->Height / 2 - size * 20;
    int markedAmount = 1;

    int X = xDefaultValue;
    int Y = yDefaultValue;

    markedVertices[0] = 1;

    while (markedAmount != size - 1) // пока не все вершины помечены
    {
        beforePrevVertex = prevVertex;
        prevVertex = currentVertex;
        currentVertex = NextNotMarked(currentVertex, markedVertices, verticesOffsets); // попытка найти непомеченную вершину для текущей
        markedAmount++;
        if (currentVertex == -1) // если для текущей вершины уже все помечены, найти первую непомеченную для первой
        {
            currentVertex = NextNotMarked(0, markedVertices, verticesOffsets); // попытка найти непомеченную вершину для первой
            X = xDefaultValue;
            Y += 100;
            if (currentVertex == -1) // если и для первой вершины уже все помечены, найти любую непомеченную
            {
                ////Trace::WriteLine("Не можем попасть в конец или в непомеченную");
                Y -= 100;
                for (int i = 0; i < size; i++) // обнуление смещений
                {
                    verticesOffsets[i] = 0;
                }
                for (int i = 0; i < size; i++) // сам поиск непомеченной вершины
                {
                    if (markedVertices[i] == 0)
                    {
                        currentVertex = i;
                        break;
                    }
                }
            }
        }

        if (prevVertex != 0 && matrix[0][currentVertex] > 0) // если мы не из первой вершины попали в вершину, в которую есть путь из первой, сбросить значения
        {
            X = xDefaultValue;
            Y = maxY + 100;
            ////Trace::WriteLine("Предотвращена линия из 1 через весь граф");
            for (int i = 0; i < size; i++)
            {
                verticesOffsets[i] = 0;
            }
        }

        if (currentVertex == size - 1) // если мы попали в последнюю вершину то мы сбрасываем значения и ничего не строим
        {
            markedVertices[currentVertex] = 0;
            markedAmount--;
            ////Trace::WriteLine("Пришли в конец");
            for (int i = 0; i < size; i++)
            {
                verticesOffsets[i] = 0;
            }
            currentVertex = 0;
            X = xDefaultValue;
            Y = maxY + 100;
            ////Trace::WriteLine("Y: " + Y);
        }
        else // стандартное заполнение значений для обычной вершины
        {
            X += xIncValue - verticesOffsets[currentVertex];
            Y += verticesOffsets[currentVertex];
            maxX = (maxX < X) ? X : maxX;
            maxY = (maxY < Y) ? Y : maxY;
            markedVertices[currentVertex] = 1;
            for (int i = 0; i < size; i++) // проверка на странную ошибку, когда у вершины создаются координаты, уже имеющиеся у другой вершины
            {
                if (vertices[i] != nullptr && vertices[i]->X == X && vertices[i]->Y == Y)
                {
                    Y += 100;
                    X += 200;
                    ////Trace::WriteLine("Проблема одинаковых координат предотвращена");
                }
            }
            vertices[currentVertex] = gcnew Vertex;
            vertices[currentVertex]->Name = (currentVertex + 1).ToString();
            vertices[currentVertex]->X = X;
            vertices[currentVertex]->Y = Y;
            ////Trace::WriteLine("Вершина " + (currentVertex + 1) + " добавлена со смещением " + verticesOffsets[currentVertex]);
            ////Trace::WriteLine("Созданы координаты " + (currentVertex + 1) + " вершины, Х: " + X + ", Y: " + Y);
            // проверка на принадлежность добавленной вершины к уровню по координатам
            if ((X - xDefaultValue) % xIncValue == 0 && X != 20)
            {
                int levelIndex = (float)(X - xDefaultValue) / xIncValue - 1;
                if (levels[levelIndex] == nullptr)
                {
                    levels[levelIndex] = gcnew array<int>(0);
                    amountOfLevels++;
                }
                AddToLevel(levelIndex, currentVertex, levels);
            }
        }
    }

    // отладочный вывод уровней
    for (int i = 0; i < amountOfLevels; i++)
    {
        ////Trace::Write((i + 1) + ": ");
        for (int j = 0; j < levels[i]->Length; j++)
        {
            ////Trace::Write((levels[i][j] + 1) + " ");
        }
        ////Trace::WriteLine("");
    }

    AddOffsetsBasedOnLevels(levels, vertices, maxX, amountOfLevels);

    vertices[0] = gcnew Vertex;
    vertices[0]->Name = (1).ToString();
    vertices[0]->X = 20;
    vertices[0]->Y = (maxY - yDefaultValue) / 2 + yDefaultValue;

    vertices[size - 1] = gcnew Vertex;
    vertices[size - 1]->Name = (size).ToString();
    vertices[size - 1]->Y = (maxY - yDefaultValue) / 2 + yDefaultValue;
    vertices[size - 1]->X = maxX + xIncValue;
}

// добавляет к позициям вершин смещения основываясь на массиве уровней
void GraphsToVisualize::VisualizationForm::AddOffsetsBasedOnLevels(array<array<int>^>^ levels, array<Vertex^>^ vertices, int maxX, int amountOfLevels)
{
    int levelOffset = 0;
    int offset = 0;
    int maxOffset = 0;
    for (int i = 0; i < amountOfLevels; i++) // добавление смещений вершинам на каждом уровне
    {
        int length = levels[i]->Length;

        levelOffset += (offset > 0) ? offset : 0;
        offset = 0;

        // смещение по уровню для центральных на нем вершин
        if (length % 2 == 0)
        {
            vertices[levels[i][length / 2 - 1]]->X += levelOffset;
            ////Trace::WriteLine("Для вершины " + (levels[i][length / 2 - 1] + 1) + " задано смещение " + levelOffset + " из-за уровня " + (i + 1));
            maxX = (vertices[levels[i][length / 2 - 1]]->X > maxX) ? vertices[levels[i][length / 2 - 1]]->X : maxX;

            vertices[levels[i][length / 2]]->X += levelOffset;
            ////Trace::WriteLine("Для вершины " + (levels[i][length / 2] + 1) + " задано смещение " + levelOffset + " из-за уровня " + (i + 1));
            maxX = (vertices[levels[i][length / 2]]->X > maxX) ? vertices[levels[i][length / 2]]->X : maxX;
        }
        else
        {
            vertices[levels[i][length / 2]]->X += levelOffset;
            ////Trace::WriteLine("Для вершины " + (levels[i][length / 2] + 1) + " задано смещение " + levelOffset + " из-за уровня " + (i + 1));
            maxX = (vertices[levels[i][length / 2]]->X > maxX) ? vertices[levels[i][length / 2]]->X : maxX;
        }

        // смещение остальных пар вершин на уровне
        for (int j = length / 2 + 1; j < length; j++) // 
        {
            offset -= (j - 1) * 50 - (j - 2) * 25;

            vertices[levels[i][length - 1 - j]]->X += offset + levelOffset;
            maxX = (vertices[levels[i][length - 1 - j]]->X > maxX) ? vertices[levels[i][length - 1 - j]]->X : maxX;
            ////Trace::WriteLine("Для вершины " + (levels[i][length - 1 - j] + 1) + " задано смещение " + offset + " " + levelOffset + " из-за уровня " + (i + 1));

            vertices[levels[i][j]]->X += offset + levelOffset;
            maxX = (vertices[levels[i][j]]->X > maxX) ? vertices[levels[i][j]]->X : maxX;
            ////Trace::WriteLine("Для вершины " + (levels[i][j] + 1) + " задано смещение " + offset + " " + levelOffset + " из-за уровня " + (i + 1));
        }
    }
}

// визуализирует таблицы в зависимости от типа задания
Void GraphsToVisualize::VisualizationForm::VisualizeTables()
{
    int GridColumnWidth = 25;
    conditionGridView->Height = 22 * size + 20;
    conditionGridView->Width = GridColumnWidth * size + 52;

    for (int i = 0; i < size; i++)
    {
        conditionGridView->Columns->Add((i + 1).ToString(), (i + 1).ToString());
        conditionGridView->Columns[i]->Width = GridColumnWidth;
        conditionGridView->Columns[i]->SortMode = DataGridViewColumnSortMode::NotSortable;
    }

    for (int i = 0; i < size; i++) // заполнение матрицы смежности
    {
        conditionGridView->Rows->Add();
        conditionGridView->Rows[i]->HeaderCell->Value = (i + 1).ToString();
        for (int j = 0; j < size; j++)
        {
            conditionGridView->Rows[i]->Cells[j]->Value = matrix[i][j];
        }
    }

    label2->Location = System::Drawing::Point(1218, conditionGridView->Location.Y + conditionGridView->Height + 10);
    dataGridView2->Location = System::Drawing::Point(1218, label2->Location.Y + 30);

    if (taskName == "Алгоритм Дейкстры")
    {
        label2->Text = "Решение (Для обозначения бесконечного пути введите " + L"∞" + ")";
        dataGridView2->TopLeftHeaderCell->Value = "Итерация";
        dataGridView2->Height = 22 * size + 20;
        dataGridView2->Width = GridColumnWidth * (size + 1) + 72;

        dataGridView2->Columns->Add("0", "X");
        dataGridView2->Columns[0]->Width = GridColumnWidth;
        dataGridView2->Columns[0]->SortMode = DataGridViewColumnSortMode::NotSortable;

        for (int i = 0; i < size; i++)
        {
            dataGridView2->Columns->Add((i + 1).ToString(), (i + 1).ToString());
            dataGridView2->Columns[i + 1]->Width = GridColumnWidth;
            dataGridView2->Columns[i + 1]->SortMode = DataGridViewColumnSortMode::NotSortable;
        }

        for (int i = 0; i < size; i++)
        {
            dataGridView2->Rows->Add();
            dataGridView2->Rows[i]->HeaderCell->Value = (i).ToString();
            for (int j = 0; j < size; j++)
            {
                dataGridView2->Rows[i]->Cells[j + 1]->Value = L"∞";
            }
            dataGridView2->Rows[i]->Cells[1]->Value = "0*";
        }
        dataGridView2->Rows[0]->Cells[0]->Value = "-";
    }
    else if (taskName == "Алгоритм Демукрона")
    {
        label2->Text = "Решение (Вводить вершины через \", \")";
        dataGridView2->TopLeftHeaderCell->Value = "Уровень";
        dataGridView2->Height = 20;
        dataGridView2->Width = 222;

        dataGridView2->Columns->Add("0", "Список вершин на уровне");
        dataGridView2->Columns[0]->Width = 150;
        dataGridView2->Columns[0]->SortMode = DataGridViewColumnSortMode::NotSortable;

        for (int i = 0; i < levels->Length && levels[i] != nullptr && levels[i]->Length != 0; i++)
        {
            dataGridView2->Height += 22;
            dataGridView2->Rows->Add();
            dataGridView2->Rows[i]->HeaderCell->Value = (i + 1).ToString();
        }
    }

    checkSolutionButton->Location = System::Drawing::Point(1218, dataGridView2->Location.Y + dataGridView2->Height + 20);
    showSolutionButton->Location = System::Drawing::Point(checkSolutionButton->Location.X + 150, checkSolutionButton->Location.Y);
}

// находит индекс следующей непомеченной вершины
int GraphsToVisualize::VisualizationForm::NextNotMarked(int currentVertex, array<int>^ markedVertices, array<int>^ verticesOffsets)
{
    bool foundNotMarked = false;
    int newVertex = -1;
    for (int i = 0; i < size; i++)
    {
        if (matrix[currentVertex][i] != 0 && (markedVertices[i] == 0) && !foundNotMarked) // если новая вершина не помечена и в нее есть путь из текущей
        {
            newVertex = i;
            foundNotMarked = true;
        }
        else if (matrix[currentVertex][i] != 0 && markedVertices[i] == 0 && currentVertex != 0)
        {
            verticesOffsets[i] = 100;
            break;
        }
    }
    if (foundNotMarked)
        return newVertex;
    return -1;
}

// проверяет правильность решения в зависимости от типа задания
Void GraphsToVisualize::VisualizationForm::CheckSolution(System::Object^ sender, System::EventArgs^ e)
{
    showSolutionButton->Enabled = true;
    String^ resultMessage = "";
    if (taskName == "Алгоритм Дейкстры")
    {
        for (int i = 0; i < size; i++)
        {
            if (dataGridView2->Rows[size - 1]->Cells[i + 1]->Value != nullptr)
            {
                int value = 0;
                String^ cellValue = dataGridView2->Rows[size - 1]->Cells[i + 1]->Value->ToString();
                if (cellValue[cellValue->Length - 1] == '*')
                {
                    cellValue = cellValue->Remove(cellValue->Length - 1);
                }
                if (!Int32::TryParse(cellValue, value))
                {
                    resultMessage = "Ошибка. Введенное значение не принадлежит к целочисленному типу";
                    break;
                }
                if (ways[size - 1][i] != Convert::ToInt32(cellValue))
                {
                    resultMessage += "Неверное значение пути в " + (i + 1) + " вершину" + Environment::NewLine;
                }
            }
            else
            {
                resultMessage += "Не заполнено значение пути в " + (i + 1) + " вершину" + Environment::NewLine;
            }
        }
    }
    else if (taskName == "Алгоритм Демукрона")
    {
        for (int i = 0; i < levels->Length && levels[i] != nullptr && levels[i]->Length != 0; i++) // проход по строчкам для сравнения заполненных в них значений с массивом уровней
        {
            String^ cellValue = (dataGridView2->Rows[i]->Cells[0]->Value != nullptr) ? dataGridView2->Rows[i]->Cells[0]->Value->ToString() : "";
            for(int j = 0; j < levels[i]->Length; j++)
            {   
                int vertex = levels[i][j];
                // проверка на наличие вершины из уровней внутри в уровнях снаружи
                if (cellValue->Length > vertex.ToString()->Length)
                {
                    if (cellValue->IndexOf(" " + vertex + ",") == -1 &&
                        cellValue->IndexOf(vertex + ",") != 0 &&
                        cellValue->IndexOf(" " + vertex) != cellValue->Length - 1 - vertex.ToString()->Length)
                    {
                        resultMessage += "Вершина " + vertex + " отсутствует в уровне " + (i + 1) + Environment::NewLine;
                    }
                }
                else if (cellValue->IndexOf(vertex.ToString()) != 0)
                {
                    resultMessage += "Вершина " + vertex + " отсутствует в уровне " + (i + 1) + Environment::NewLine;
                }
            }
        }
    }
    if (resultMessage == "")
    {
        resultMessage = "Ошибок нет. Хорошая работа!";
    }
    textBox1->Visible = true;
    textBox1->Text = resultMessage;
}

// выводит корректное решение в зависимости от типа задания
Void GraphsToVisualize::VisualizationForm::ShowSolution(System::Object^ sender, System::EventArgs^ e)
{
    this->dataGridView2->ReadOnly = true;
    showSolutionButton->Enabled = false;
    checkSolutionButton->Enabled = false;
    if (taskName == "Алгоритм Дейкстры")
    {
        for (int i = 0; i < size; i++)
        {
            if (i == 0)
            {
                dataGridView2->Rows[i]->Cells[0]->Value = "-";
            }
            else
            {
                dataGridView2->Rows[i]->Cells[0]->Value = correctMarkers[i - 1];
            }
            for (int j = 0; j < size; j++)
            {
                dataGridView2->Rows[i]->Cells[j + 1]->Value = (ways[i][j] > 500) ? L"∞" : ways[i][j].ToString();
                bool isMarked = false;
                for (int k = 0; k < i + 1; k++)
                {
                    if (correctMarkers[k] == j + 1)
                        isMarked = true;
                }
                if (isMarked)
                {
                    dataGridView2->Rows[i]->Cells[j + 1]->Value += "*";
                }
            }
        }
    }
    else if (taskName == "Алгоритм Демукрона")
    {
        for (int i = 0; i < levels->Length && levels[i] != nullptr && levels[i]->Length != 0; i++)
        {
            dataGridView2->Rows[i]->Cells[0]->Value = levels[i][0].ToString();

            for (int j = 1; j < levels[i]->Length; j++)
            {
                dataGridView2->Rows[i]->Cells[0]->Value += ", " + levels[i][j].ToString();
            }
        }
    }
}

// функция с помощью которой другие модули должны вызывать этот для визуализации алгоритма Дейкстры
void GraphsToVisualize::VisualizeDijkstra(array<array<int>^>^ matrix, int size, array<array<int>^>^ ways, array<int>^ correctMarkers)
{
	GraphsToVisualize::VisualizationForm^ VisualizationForm = gcnew GraphsToVisualize::VisualizationForm(matrix, size, ways, correctMarkers);
	VisualizationForm->Show();
}

// функция с помощью которой другие модули должны вызывать этот для визуализации алгоритма Демукрона
void GraphsToVisualize::VisualizeDemoucron(array<array<int>^>^ matrix, int size, array<array<int>^>^ levels)
{
    GraphsToVisualize::VisualizationForm^ VisualizationForm = gcnew GraphsToVisualize::VisualizationForm(matrix, size, levels);
    VisualizationForm->Show();
}
