#include "ShortestPathForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace System::Drawing;

Void GraphsToStudy::ShortestPathForm::onShown(System::Object^ sender, System::EventArgs^ e)
{
    int amountOfLevels = CalculateLevels(); // ��������� ����� ������� ��������� �� ����� �������
    CalculatePositions(amountOfLevels);
    VisualizeGraph();
    VisualizeTables();
}

Void GraphsToStudy::ShortestPathForm::VisualizeGraph() // ���� ������ �������, ����� �� � ��������� �����, ��������� �� �� ������ � ������� � ����� �������, � ������� �� ��� ����� ������� 
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
                Trace::WriteLine("��������� ����� �� " + (i + 1) + " ������� � " + (j + 1));
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
        Trace::WriteLine("��������� " + (i + 1) + " �������");
    }
}

// ���������� �� ������� ��������� �� ����� ������� ����� ������� ���������, ���������� ���������� ����������� �������
int GraphsToStudy::ShortestPathForm::CalculateLevels()
{
    levels = gcnew array<array<int>^>(size);
    levels[size - 1] = gcnew array<int>(0);
    int addedVerticesAmount = 1;

    for (int levelIndex = 0; levelIndex < size - 1; levelIndex++)
    {
        levels[levelIndex] = gcnew array<int>(0);
        if (levelIndex == 0) // ���� ������ �������, ������� � ���� ������ �������
        {
            Array::Resize(levels[levelIndex], 1);
            levels[0][0] = 1; //� ������� ��� ������� ������ ����� ������ �������
            Trace::WriteLine("������� 1 ��������� � ������� 0");
        }
        else
        {
            int prevLevelIndex = levelIndex - 1;
            for (int i = 0; i < levels[prevLevelIndex]->Length; i++) // ���� ������ ���� ������ ����������� ������
            {
                int vertexIndex = levels[prevLevelIndex][i] - 1;
                for (int j = 0; j < size - 1; j++) // ���� ������ ������ � ������� ��������� ��� ������� ����������� ������
                {
                    if (matrix[vertexIndex][j] > 0 && vertexIndex != j && !IsInLevels(j, levelIndex + 1)) // ��������� �������, ������� �������� ������, ��������� � ���� ����� ���� ��� ��������� ������� �������
                    {// ���� �� ������� ���� ���� � ��������� �������  
                        /*if (matrix[j][size - 1] > 0)
                        {
                            AddToLevel(size - 1, j);
                        }
                        else
                        {*/
                        AddToLevel(levelIndex, j);
                        //}
                        addedVerticesAmount++;
                        if (addedVerticesAmount == size - 1)
                        {
                            addedVerticesAmount++;
                            levels[levelIndex + 1] = gcnew array<int>(0);
                            AddToLevel(levelIndex + 1, size - 1);
                        }
                        Trace::WriteLine("������� " + (j + 1).ToString() + " ��������� � ������� " + levelIndex.ToString());
                    }
                }
            }
        }
        if (addedVerticesAmount == size)
            return levelIndex + 1; // ���������� ������ ���������� ����������� �������
    }
    return -1;
}

// ��������� ������� �� �������
void GraphsToStudy::ShortestPathForm::AddToLevel(int levelIndex, int vertexIndex)
{
    int length = levels[levelIndex]->Length;
    Array::Resize(levels[levelIndex], length + 1);
    levels[levelIndex][length] = vertexIndex + 1;
}

// ��������� ���� �� ������� � ��� ����������� �������
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

// ��������������� ������������ ������� ������ �� ������ ������
void GraphsToStudy::ShortestPathForm::CalculatePositions(int amountOfLevels)
{
    vertices = gcnew array<Vertex^>(size);
    int X = 20;
    int Y = this->pictureBox1->Height / 2;

    vertices[0] = gcnew Vertex;
    vertices[0]->Name = (1).ToString();
    vertices[0]->X = X;
    vertices[0]->Y = Y;
    Trace::WriteLine("������� ���������� 1 �������, �: " + X + ", Y: " + Y);
    for (int i = 1; i < amountOfLevels; i++) // ���� ������ ������� �������� �������
    {
        int levelSize = levels[i]->Length;
        X += 110 * (levelSize + 1) / 2;
        int Ymodifier = (i - 1) * 20;
        int Xmodifier = (i - 1) * 40;
        int multiplier = -1;
        if (levelSize % 2 == 0)
        {
            Ymodifier += 40 + (i - 1) * 20;
            Xmodifier += 60;
        }
        for (int j = 0; j < levelSize; j++) // ���� ������ ������� �������
        {
            multiplier = -multiplier;
            int vertex = levels[i][j];

            vertices[vertex - 1] = gcnew Vertex;
            vertices[vertex - 1]->Name = vertex.ToString();
            vertices[vertex - 1]->X = X - Xmodifier;
            vertices[vertex - 1]->Y = Y + Ymodifier * multiplier;
            Trace::WriteLine("������� ���������� " + vertex + " �������, " "�: " + vertices[vertex - 1]->X + ", Y : " + vertices[vertex - 1]->Y);
            
            if ((j % 2 == 1 && levelSize % 2 == 0) || (j % 2 == 0 && levelSize % 2 == 1))// ��� �������� ����� ������ ��������� ������, ���������, ��������� ���, ���������...
            {
                Ymodifier += 50 + (i - 1) * 20;
                Xmodifier += 100 + (j - 1) * 20;
            }
        }
    }
    int vertex = levels[amountOfLevels][0] - 1;
    vertices[vertex] = gcnew Vertex;
    vertices[vertex]->Name = (size).ToString();
    vertices[vertex]->X = X + 60;
    vertices[vertex]->Y = Y;
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