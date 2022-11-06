#include "ShortestPathForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace System::Drawing;

Void GraphsToStudy::ShortestPathForm::onShown(System::Object^ sender, System::EventArgs^ e)
{
    int amountOfLevels = CalculateLevels(); // вычисляет какие вершины находятся на каких уровнях
    CalculatePositions(amountOfLevels);
    VisualizeGraph(sender);
}

Void GraphsToStudy::ShortestPathForm::VisualizeGraph(System::Object^ sender) // беру первую вершину, строю ее в начальной точке, прохожусь по ее строке в матрице и строю вершины, в которые из нее можно попасть 
{
    int radius = diameter / 2;
    pictureBox1->Image = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
    Pen^ pen = gcnew Pen(Color::Black, 1.0f);
    Brush^ brush = Brushes::Black;
    Brush^ whiteBrush = Brushes::White;
    Drawing::Font^ font = gcnew Drawing::Font("Arial", 20);
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
        graph->DrawEllipse(pen, vertices[i]->X, vertices[i]->Y, diameter, diameter);
        graph->FillEllipse(whiteBrush, vertices[i]->X, vertices[i]->Y, diameter, diameter);
        graph->DrawString(vertices[i]->Name, font, brush, vertices[i]->X + 15, vertices[i]->Y + 10);
        Trace::WriteLine("Построена " + (i + 1) + " вершина");

        //Trace::WriteLine("Рисуется все для " + (i + 1).ToString() + " вершины");
        //for (int j = i + 1; j < size; j++) // для вершины строятся смежные ей
        //{
        //    Trace::WriteLine("i: " + i.ToString() + " j: " + j.ToString() + " значение в матрице: " + matrix[i][j].ToString());
        //    if (matrix[i][j] == 1)
        //    {
        //        if (positions[j] == nullptr)
        //        {
        //            String^ name = (j + 1).ToString();
        //            positions[j] = gcnew Position;
        //            positions[j]->X = positions[i]->X + 100;
        //            positions[j]->Y = positions[i]->Y + 100 * drawnRoots;
        //            graph->DrawEllipse(pen, positions[j]->X, positions[j]->Y, diameter, diameter);
        //            graph->DrawString(name, font, brush, positions[j]->X + 15, positions[j]->Y + 10);
        //            drawnRoots++;
        //            Trace::WriteLine("Отрисована вершина " + name);
        //        }
        //        if (positions[i] != nullptr)
        //        {
        //            Trace::WriteLine("Отрисована линия от " + (i + 1).ToString() + " вершины до " + (j + 1).ToString());
        //            graph->DrawLine(pen, positions[i]->X, positions[i]->Y, positions[j]->X, positions[j]->Y);
        //        }
        //    }
        //}
    }
}

// определяет по матрице смежности на каких уровнях какие вершины находятся, возвращает количество построенных уровней
int GraphsToStudy::ShortestPathForm::CalculateLevels()
{
    levels = gcnew array<array<int>^>(size);
    int addedVerticesAmount = 1;

    for (int levelIndex = 0; levelIndex < size; levelIndex++)
    {
        levels[levelIndex] = gcnew array<int>(0);
        if (levelIndex == 0) // если первый уровень, помещаю в него первую вершину
        {
            Array::Resize(levels[levelIndex], 1);
            levels[0][0] = 1; //в массиве для первого уровня номер первой вершины
            Trace::WriteLine("Вершина 1 добавлена в уровень 0");
        }
        else
        {
            int prevLevelIndex = levelIndex - 1;
            for (int i = 0; i < levels[prevLevelIndex]->Length; i++) // цикл обхода всех вершин предыдущего уровня
            {
                int vertexIndex = levels[prevLevelIndex][i] - 1;
                for (int j = 0; j < size - 1; j++) // цикл обхода строки в матрице смежности для вершины предудыщего уровня
                {
                    if (matrix[vertexIndex][j] > 0 && vertexIndex != j && !IsInLevels(j, levelIndex + 1)) // учитываем уровень, который строится сейчас, поскольку в него может быть уже добавлена текущая вершина
                    {
                        AddToLevel(levelIndex, j);
                        addedVerticesAmount++;
                        if (addedVerticesAmount == size - 1)
                        {
                            addedVerticesAmount++;
                            levels[levelIndex + 1] = gcnew array<int>(0);
                            AddToLevel(levelIndex + 1, size - 1);
                        }
                        Trace::WriteLine("Вершина " + (j + 1).ToString() + " добавлена в уровень " + levelIndex.ToString());
                    }
                }
            }
        }
        if (addedVerticesAmount == size)
            return levelIndex + 2; // возвращаем точное количество добавленных уровней
    }
    return -1;
}

// добавляет вершину на уровень
void GraphsToStudy::ShortestPathForm::AddToLevel(int levelIndex, int vertexIndex)
{
    int length = levels[levelIndex]->Length;
    Array::Resize(levels[levelIndex], length + 1);
    levels[levelIndex][length] = vertexIndex + 1;
}

// проверяет есть ли вершина в уже построенных уровнях
bool GraphsToStudy::ShortestPathForm::IsInLevels(int vertexIndex, int curAmountOfLevels)
{
    for (int i = 0; i < curAmountOfLevels; i++)
    {
        for (int j = 0; j < levels[i]->Length; j++)
        {
            if (levels[i][j] == vertexIndex + 1)
                return true;
        }
    }
    return false;
}

// последовательно рассчитывает позиции вершин на каждом уровне
void GraphsToStudy::ShortestPathForm::CalculatePositions(int amountOfLevels)
{
    vertices = gcnew array<Vertex^>(size);
    int X = 20;
    int Y = this->pictureBox1->Height / 2;

    vertices[0] = gcnew Vertex;
    vertices[0]->Name = (1).ToString();
    vertices[0]->X = X;
    vertices[0]->Y = Y;
    Trace::WriteLine("Созданы координаты 1 вершины, Х: " + X + ", Y: " + Y);
    for (int i = 1; i < amountOfLevels; i++) // цикл обхода массива массивов уровней
    {
        int levelSize = levels[i]->Length;
        X += 100 * (levelSize + 1) / 2;
        int modifier = 0;
        int multiplier = 1;
        if (levelSize % 2 == 0)
        {
            modifier += 50;
        }
        for (int j = 0; j < levelSize; j++) // цикл обхода массива уровней
        {
            multiplier = -multiplier;
            int vertex = levels[i][j];

            vertices[vertex - 1] = gcnew Vertex;
            vertices[vertex - 1]->Name = vertex.ToString();
            vertices[vertex - 1]->X = X - modifier;
            vertices[vertex - 1]->Y = Y + modifier * multiplier;
            Trace::WriteLine("Созданы координаты " + vertex + " вершины, " "Х: " + vertices[vertex - 1]->X + ", Y : " + vertices[vertex - 1]->Y);
            
            if ((j % 2 == 1 && levelSize % 2 == 0) || (j % 2 == 0 && levelSize % 2 == 1))// при нечетном колве вершин построили первую, увеличили, построили две, увеличили...
            {
                modifier += 100;
            }
        }
    }
}
