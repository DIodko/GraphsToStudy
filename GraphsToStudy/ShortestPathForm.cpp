#include "ShortestPathForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace System::Drawing;

Void GraphsToStudy::ShortestPathForm::onShown(System::Object^ sender, System::EventArgs^ e)
{
    VisualizeGraph(sender);
}

Void GraphsToStudy::ShortestPathForm::VisualizeGraph(System::Object^ sender) // беру первую вершину, строю ее в начальной точке, прохожусь по ее строке в матрице и строю вершины, в которые из нее можно попасть 
{
    CalculateLevels(); // вычисляет какие вершины находятся на каких уровнях
    pictureBox1->Image = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
    pen = gcnew Pen(Color::Black, 1.0f);
    brush = Brushes::Black;
    font = gcnew Drawing::Font("Arial", 20);
    graph = Graphics::FromImage(pictureBox1->Image);

    for (int i = 0; i < size; i++)
    {
        //int drawnRoots = 0;
        if (i == 0) // если первая вершина, строю ее
        {
            positions[i] = gcnew Position;
            String^ name = (i + 1).ToString();
            positions[i]->X = 20;
            positions[i]->Y = 225;
            graph->DrawEllipse(pen, positions[i]->X, positions[i]->Y, diameter, diameter);
            graph->DrawString(name, font, brush, positions[i]->X + 15, positions[i]->Y + 10);
            Trace::WriteLine("Построена первая вершина");
        }
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

void GraphsToStudy::ShortestPathForm::CalculateLevels()
{
    positions = gcnew array<Position^>(size);
    levels = gcnew array<array<int>^>(size);

    for (int levelIndex = 0; levelIndex < size - 1; levelIndex++)
    {
        levels[levelIndex] = gcnew array<int>(size);
        if (levelIndex == 0) // если первая вершина, помещаю ее в уровень
        {
            levels[0][0] = 1; //в массиве для первого уровня номер первой вершины
            Trace::WriteLine("Вершина 0 добавлена в уровень 0");
        }
        else
        {
            int prevLevelIndex = levelIndex - 1;
            for (int i = 0; levels[prevLevelIndex][i] != 0 && i < size; i++) // для вершин с индексами 0, 1, 2 в массиве levels[level_index] будет 1, 2, 3
            {
                int rootIndex = levels[prevLevelIndex][i] - 1;
                for (int j = 0; j < size; j++)
                {
                    if (matrix[rootIndex][j] > 0 && rootIndex != j && !IsInLevels(j))
                    {
                        AddToLevel(levelIndex, j);
                        Trace::WriteLine("Вершина " + (j).ToString() + " добавлена в уровень " + levelIndex.ToString());
                    }
                }
            }
        }
    }
}

// добавляет вершину на уровень
void GraphsToStudy::ShortestPathForm::AddToLevel(int levelIndex, int rootIndex)
{
    for (int i = 0; i < size; i++)
    {
        if (levels[levelIndex][i] == 0)
        {
            levels[levelIndex][i] = rootIndex + 1;
            break;
        }
    }
}

// проверяет есть ли вершина в уже построенных уровнях, много бесполезных итераций
bool GraphsToStudy::ShortestPathForm::IsInLevels(int rootIndex)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size && levels[i] != nullptr; j++)
        {
            if (levels[i][j] == rootIndex + 1)
                return true;
        }
    }
    return false;
}

