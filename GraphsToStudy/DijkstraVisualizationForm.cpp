﻿#include "DijkstraVisualizationForm.h"
#include <math.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace System::Drawing;

Void DijkstraVisualization::DijkstraVisualizationForm::onShown(System::Object^ sender, System::EventArgs^ e)
{
    array<Vertex^>^ vertices = gcnew array<Vertex^>(size); // инициализируется основной массив с вершинами, которые потом будут выводиться
    CalculatePositions(vertices); // рассчитываются позиции вершин в графе с использованием логики маршрутов и уровней
    VisualizeGraph(vertices); // отрисовываются вершины и линии между ними
    VisualizeTables(); // визуализируются нужные таблицы, кнопки, надписи и т.д.
}

Void DijkstraVisualization::DijkstraVisualizationForm::VisualizeGraph(array<Vertex^>^ vertices) // беру первую вершину, строю ее в начальной точке, прохожусь по ее строке в матрице и строю вершины, в которые из нее можно попасть 
{
    int radius = diameter / 2;
    int offset = radius / 2 - 5;
    pictureBox1->Image = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
    Pen^ pen = gcnew Pen(Color::Black, 1.0f);
    Brush^ brush = Brushes::Black;
    Brush^ whiteBrush = Brushes::White;
    Drawing::Font^ font = gcnew Drawing::Font("Arial", 14);
    Graphics^ graph = Graphics::FromImage(pictureBox1->Image);
    
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (matrix[i][j] > 0)
            {
                graph->DrawLine(pen, vertices[i]->X + radius, vertices[i]->Y + radius,
                    vertices[j]->X + radius, vertices[j]->Y + radius);
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
void DijkstraVisualization::DijkstraVisualizationForm::AddToLevel(int levelIndex, int vertexIndex, array<array<int>^>^ levels)
{
    int length = levels[levelIndex]->Length;
    Array::Resize(levels[levelIndex], length + 1);
    levels[levelIndex][length] = vertexIndex;
}

void DijkstraVisualization::DijkstraVisualizationForm::CalculatePositions(array<Vertex^>^ vertices)
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
                //Trace::WriteLine("Не можем попасть в конец или в непомеченную");
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
            //Trace::WriteLine("Предотвращена линия из 1 через весь граф");
            for (int i = 0; i < size; i++)
            {
                verticesOffsets[i] = 0;
            }
        }

        if (currentVertex == size - 1) // если мы попали в последнюю вершину то мы сбрасываем значения и ничего не строим
        {
            markedVertices[currentVertex] = 0;
            markedAmount--;
            //Trace::WriteLine("Пришли в конец");
            for (int i = 0; i < size; i++)
            {
                verticesOffsets[i] = 0;
            }
            currentVertex = 0;
            X = xDefaultValue;
            Y = maxY + 100;
            //Trace::WriteLine("Y: " + Y);
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
                    //Trace::WriteLine("Проблема одинаковых координат предотвращена");
                }
            }
            vertices[currentVertex] = gcnew Vertex;
            vertices[currentVertex]->Name = (currentVertex + 1).ToString();
            vertices[currentVertex]->X = X;
            vertices[currentVertex]->Y = Y;
            //Trace::WriteLine("Вершина " + (currentVertex + 1) + " добавлена со смещением " + verticesOffsets[currentVertex]);
            //Trace::WriteLine("Созданы координаты " + (currentVertex + 1) + " вершины, Х: " + X + ", Y: " + Y);
            // проверка на принадлежность добавленной вершины к уровню по координатам
            if ((X - xDefaultValue) % xIncValue == 0 && X != 20)
            {
                int levelIndex = (X - xDefaultValue) / xIncValue - 1;
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
        //Trace::Write((i + 1) + ": ");
        for (int j = 0; j < levels[i]->Length; j++)
        {
            //Trace::Write((levels[i][j] + 1) + " ");
        }
        //Trace::WriteLine("");
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

void DijkstraVisualization::DijkstraVisualizationForm::AddOffsetsBasedOnLevels(array<array<int>^>^ levels, array<Vertex^>^ vertices, int maxX, int amountOfLevels)
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
            //Trace::WriteLine("Для вершины " + (levels[i][length / 2 - 1] + 1) + " задано смещение " + levelOffset + " из-за уровня " + (i + 1));
            maxX = (vertices[levels[i][length / 2 - 1]]->X > maxX) ? vertices[levels[i][length / 2 - 1]]->X : maxX;

            vertices[levels[i][length / 2]]->X += levelOffset;
            //Trace::WriteLine("Для вершины " + (levels[i][length / 2] + 1) + " задано смещение " + levelOffset + " из-за уровня " + (i + 1));
            maxX = (vertices[levels[i][length / 2]]->X > maxX) ? vertices[levels[i][length / 2]]->X : maxX;
        }
        else 
        {
            vertices[levels[i][length / 2]]->X += levelOffset;
            //Trace::WriteLine("Для вершины " + (levels[i][length / 2] + 1) + " задано смещение " + levelOffset + " из-за уровня " + (i + 1));
            maxX = (vertices[levels[i][length / 2]]->X > maxX) ? vertices[levels[i][length / 2]]->X : maxX;
        }

        // смещение остальных пар вершин на уровне
        for (int j = length / 2 + 1; j < length; j++) // 
        {
            offset -= (j - 1) * 50 - (j - 2) * 25;

            vertices[levels[i][length - 1 - j]]->X += offset + levelOffset;
            maxX = (vertices[levels[i][length - 1 - j]]->X > maxX) ? vertices[levels[i][length - 1 - j]]->X : maxX;
            //Trace::WriteLine("Для вершины " + (levels[i][length - 1 - j] + 1) + " задано смещение " + offset + " " + levelOffset + " из-за уровня " + (i + 1));

            vertices[levels[i][j]]->X += offset + levelOffset;
            maxX = (vertices[levels[i][j]]->X > maxX) ? vertices[levels[i][j]]->X : maxX;
            //Trace::WriteLine("Для вершины " + (levels[i][j] + 1) + " задано смещение " + offset + " " + levelOffset + " из-за уровня " + (i + 1));
        }
    }
}

Void DijkstraVisualization::DijkstraVisualizationForm::VisualizeTables()
{
    int GridColumnWidth = 25;
    dataGridView1->Height = 22 * size + 20;
    dataGridView1->Width = GridColumnWidth * size + 52;

    for (int i = 0; i < size; i++)
    {
        dataGridView1->Columns->Add((i + 1).ToString(), (i + 1).ToString());
        dataGridView1->Columns[i]->Width = GridColumnWidth;
        dataGridView1->Columns[i]->SortMode = DataGridViewColumnSortMode::NotSortable;
    }
    
    for (int i = 0; i < size; i++) // заполнение матрицы смежности
    {
        dataGridView1->Rows->Add();
        dataGridView1->Rows[i]->HeaderCell->Value = (i + 1).ToString();
        for (int j = 0; j < size; j++)
        {
            dataGridView1->Rows[i]->Cells[j]->Value = matrix[i][j];
        }
    }

    dataGridView2->TopLeftHeaderCell->Value = "Итерация";
    dataGridView2->Height = 22 * size + 20;
    dataGridView2->Width = GridColumnWidth * (size + 1) + 72;

    label2->Location = System::Drawing::Point(1218, dataGridView1->Location.Y + dataGridView1->Height + 10);
    dataGridView2->Location = System::Drawing::Point(1218, label2->Location.Y + 30);
    
    checkSolutionButton->Location = System::Drawing::Point(1218, dataGridView2->Location.Y + dataGridView2->Height + 20);
    showSolutionButton->Location = System::Drawing::Point(checkSolutionButton->Location.X + 150, checkSolutionButton->Location.Y);

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
    }
}

int DijkstraVisualization::DijkstraVisualizationForm::NextNotMarked(int currentVertex, array<int>^ markedVertices, array<int>^ verticesOffsets)
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

Void DijkstraVisualization::DijkstraVisualizationForm::CheckSolution(System::Object^ sender, System::EventArgs^ e)
{
    String^ errorMessage = "";
    for (int i = 0; i < size; i++)
    {
        if (dataGridView2->Rows[size - 1]->Cells[i + 1]->Value != nullptr)
        {
            String^ cellValue = dataGridView2->Rows[size - 1]->Cells[i + 1]->Value->ToString();
            if (cellValue[cellValue->Length - 1] == '*')
                cellValue = cellValue->Remove(cellValue->Length - 1);
            if (ways[size - 1][i] != Convert::ToInt32(cellValue))
            {
                errorMessage += "Неверное значение пути в " + (i + 1) + " вершину (ожидается: " + ways[size - 1][i] +
                    ", написано: " + cellValue + ")" + Environment::NewLine;
            }
        }
        else
        {
            errorMessage += "Не заполнено значение пути в " + (i + 1) + " вершину (ожидается: " + ways[size - 1][i] 
                + ")" + Environment::NewLine;
        }
    }
    if (errorMessage == "")
    {
        errorMessage = "Ошибок нет. Хорошая работа!";
    }
    //textBox1->Location = System::Drawing::Point(1218, checkSolutionButton->Location.Y + 70);
    textBox1->Visible = true;
    textBox1->Text = errorMessage;
}

Void DijkstraVisualization::DijkstraVisualizationForm::ShowSolution(System::Object^ sender, System::EventArgs^ e)
{
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            dataGridView2->Rows[i]->Cells[0]->Value = "-";
        }
        else
        {
            dataGridView2->Rows[i]->Cells[0]->Value = correctMarkers[i];
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