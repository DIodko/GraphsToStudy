#include "ShortestPathForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace System::Drawing;

Void GraphsToStudy::ShortestPathForm::onShown(System::Object^ sender, System::EventArgs^ e)
{
    //int amountOfLevels = CalculateLevels(); // ��������� ����� ������� ��������� �� ����� �������
    CalculatePositions();
    VisualizeGraph(vertices);
    VisualizeTables();
}

Void GraphsToStudy::ShortestPathForm::VisualizeGraph(array<Vertex^>^ vertices) // ���� ������ �������, ����� �� � ��������� �����, ��������� �� �� ������ � ������� � ����� �������, � ������� �� ��� ����� ������� 
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

//���������� �� ������� ��������� �� ����� ������� ����� ������� ���������, ���������� ���������� ����������� �������
//int GraphsToStudy::ShortestPathForm::CalculateLevels()
//{
//    levels = gcnew array<array<int>^>(size);
//    levels[size - 1] = gcnew array<int>(0);
//    int addedVerticesAmount = 1;
//
//    for (int levelIndex = 0; levelIndex < size - 1; levelIndex++)
//    {
//        levels[levelIndex] = gcnew array<int>(0);
//        if (levelIndex == 0) // ���� ������ �������, ������� � ���� ������ �������
//        {
//            Array::Resize(levels[levelIndex], 1);
//            levels[0][0] = 0; //� ������� ��� ������� ������ ����� ������ �������
//            Trace::WriteLine("������� 1 ��������� � ������� 0");
//        }
//        else
//        {
//            int prevLevelIndex = levelIndex - 1;
//            for (int i = 0; i < levels[prevLevelIndex]->Length; i++) // ���� ������ ���� ������ ����������� ������
//            {
//                int vertexIndex = levels[prevLevelIndex][i];
//                for (int j = 0; j < size - 1; j++) // ���� ������ ������ � ������� ��������� ��� ������� ����������� ������
//                {
//                    if (matrix[vertexIndex][j] > 0 && vertexIndex != j && !IsInLevels(j, levelIndex + 1)) // ��������� �������, ������� �������� ������, ��������� � ���� ����� ���� ��� ��������� ������� �������
//                    {
//                        AddToLevel(levelIndex, j);
//                        addedVerticesAmount++;
//                        if (addedVerticesAmount == size - 1)
//                        {
//                            addedVerticesAmount++;
//                            levels[levelIndex + 1] = gcnew array<int>(0);
//                            AddToLevel(levelIndex + 1, size - 1);
//                        }
//                        Trace::WriteLine("������� " + (j + 1).ToString() + " ��������� � ������� " + levelIndex.ToString());
//                    }
//                }
//            }
//        }
//        if (addedVerticesAmount == size)
//            return levelIndex + 1; // ���������� ������ ���������� ����������� �������
//    }
//    return -1;
//}
//
//// ��������� ������� �� �������
void GraphsToStudy::ShortestPathForm::AddToLevel(int levelIndex, int vertexIndex)
{
    int length = levels[levelIndex]->Length;
    Array::Resize(levels[levelIndex], length + 1);
    levels[levelIndex][length] = vertexIndex;
}
//
//// ��������� ���� �� ������� � ��� ����������� �������, ���������� ����� ������
//bool GraphsToStudy::ShortestPathForm::IsInLevels(int vertexIndex, int curAmountOfLevels)
//{
//    for (int i = 0; i < curAmountOfLevels; i++)
//    {
//        for (int j = 0; j < levels[i]->Length; j++)
//        {
//            if (levels[i][j] == vertexIndex)
//                return true;
//        }
//    }
//    return false;
//}

// ��������������� ������������ ������� ������ �� ������ ������
void GraphsToStudy::ShortestPathForm::CalculatePositions()
{
    int maxX = 0;
    int maxY = 0;
    vertices = gcnew array<Vertex^>(size);
    levels = gcnew array<array<int>^>(size);
    array<int>^ markedVertices = gcnew array<int>(size);
    array<int>^ verticesOffsets = gcnew array<int>(size);
    int markedAmount = 1;
    int currentVertex = 0;
    int X = 20;
    int Y = this->pictureBox1->Height / 2 - size * 20;
    int amountOfLevels = 0;

    markedVertices[0] = 1;
    vertices[0] = gcnew Vertex;
    vertices[0]->Name = (1).ToString();
    vertices[0]->X = X;
    vertices[0]->Y = this->pictureBox1->Height / 2;
    Trace::WriteLine("������� ���������� 1 �������, �: " + X + ", Y: " + this->pictureBox1->Height / 2);
    while (markedAmount != size - 1) // ���� �� ��� ������� ��������
    {
        currentVertex = NextNotMarked(currentVertex, markedVertices, verticesOffsets);
        markedAmount++; 
        if (currentVertex == -1) // ���� ��� ������� ������� ��� ��� ��������, ����� ����� ������������
        {
            currentVertex = NextNotMarked(0, markedVertices, verticesOffsets); // ������� ����� ������������ ������� ��� ������
            X = 20;
            Y += 100;
            if (currentVertex == -1)
            {
                Trace::WriteLine("�� ����� ������� � ����� ��� � ������������");
                Y -= 100;
                for (int i = 0; i < size; i++)
                {
                    verticesOffsets[i] = 0;
                }
                for (int i = 0; i < size; i++)
                {
                    if (markedVertices[i] == 0)
                    {
                        currentVertex = i; // ���� �� ���� ������� ����� ������� � 10, �� ��� ���� ����� ���, ���� ����� �������, ���� �������� ��������
                        for (int k = currentVertex; k < size && matrix[currentVertex][size - 1] > 0; k++)
                        {
                            if (matrix[currentVertex][k] > 0)
                            {
                                verticesOffsets[k] += 100;
                            }
                        }
                        break;
                    }
                }
            }
        }
        // ���� ����� ������������, �� ��������� � � ������� �� ����������
        //int levelIndex = (X - 20) / 140 - 1;
        //if (levels[levelIndex] == nullptr)
        //{
        //    levels[levelIndex] = gcnew array<int>(0);
        //    amountOfLevels++;
        //}
        //Trace::WriteLine("������� " + (currentVertex + 1) + " ��������� �� ������� " + levelIndex + " �� ��������� " + verticesOffsets[currentVertex]);
        Trace::WriteLine("������� " + (currentVertex + 1) + " ��������� �� ��������� " + verticesOffsets[currentVertex]);
        //AddToLevel(levelIndex, currentVertex);
        Trace::WriteLine("������� ���������� " + (currentVertex + 1) + " �������, �: " + X + ", Y: " + Y);
        if (currentVertex == size - 1)
        {
            markedVertices[currentVertex] = 0;
            markedAmount--;
            Trace::WriteLine("������ � �����");
            for (int i = 0; i < size; i++)
            {
                verticesOffsets[i] = 0;
            }
            currentVertex = 0;
            X = 20;
            Y = maxY + 100;
            Trace::WriteLine("Y: " + Y);
        }
        else
        {
            X += 140 - verticesOffsets[currentVertex];
            Y += verticesOffsets[currentVertex];
            maxX = (maxX < X) ? X : maxX;
            maxY = (maxY < Y) ? Y : maxY;
            markedVertices[currentVertex] = 1;
            vertices[currentVertex] = gcnew Vertex;
            vertices[currentVertex]->Name = (currentVertex + 1).ToString();
            vertices[currentVertex]->X = X;
            vertices[currentVertex]->Y = Y;
        }
    }
    //for (int i = 0; i < amountOfLevels; i++)
    //{
    //    int length = levels[i]->Length;
    //    for (int j = 0; j < length; j++)
    //    {
    //        vertices[levels[i][j]]->X += fabs((float)j - (float)(length - 1) / 2) * 50;
    //        Trace::WriteLine("��� ������� " + (levels[i][j] + 1) + " ������ �������� " + fabs((float)j - (float)(length - 1) / 2) * 50);
    //    }
    //}
    vertices[size - 1] = gcnew Vertex;
    vertices[size - 1]->Name = (size).ToString();
    vertices[size - 1]->Y = this->pictureBox1->Height / 2;
    vertices[size - 1]->X = maxX + 100;
}

Void GraphsToStudy::ShortestPathForm::VisualizeTables()
{
    dataGridView1->Height = 22 * size + 20;
    dataGridView1->Width = 30 * size + 52;

    dataGridView2->Height = 22 * size + 20;
    dataGridView2->Width = 30 * size + 112;

    for (int i = 0; i < size; i++)
    {
        dataGridView1->Columns->Add((i + 1).ToString(), (i + 1).ToString());
        dataGridView1->Columns[i]->Width = 30;
        dataGridView1->Columns[i]->SortMode = DataGridViewColumnSortMode::NotSortable;
    }

    for (int i = 0; i < size; i++)
    {
        array<int>^ values = gcnew array<int>(size);
        dataGridView1->Rows->Add();
        dataGridView1->Rows[i]->HeaderCell->Value = (i + 1).ToString();
        for (int j = 0; j < size; j++)
        {
            dataGridView1->Rows[i]->Cells[j]->Value = matrix[i][j];
        }
    }

    label2->Location = System::Drawing::Point(1218, dataGridView1->Location.Y + dataGridView1->Height + 10);
    dataGridView2->Location = System::Drawing::Point(1218, label2->Location.Y + 30);

    dataGridView2->Columns->Add("0", "��������");
    dataGridView2->Columns[0]->Width = 30;
    dataGridView2->Columns[0]->SortMode = DataGridViewColumnSortMode::NotSortable;
    dataGridView2->Columns->Add("1", "x");
    dataGridView2->Columns[1]->Width = 30;
    dataGridView2->Columns[1]->SortMode = DataGridViewColumnSortMode::NotSortable;
    for (int i = 0; i < size; i++)
    {
        dataGridView2->Columns->Add((i + 2).ToString(), (i + 1).ToString());
        dataGridView2->Columns[i]->Width = 30;
        dataGridView2->Columns[i]->SortMode = DataGridViewColumnSortMode::NotSortable;
    }
}

int GraphsToStudy::ShortestPathForm::NextNotMarked(int currentVertex, array<int>^ markedVertices, array<int>^ verticesOffsets)
{
    bool foundNotMarked = false;
    int newVertex = -1;
    for (int i = 0; i < size; i++)
    {
        if (matrix[currentVertex][i] != 0 && (markedVertices[i] == 0) && !foundNotMarked) // ���� ����� ������� �� �������� � � ��� ���� ���� �� �������
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