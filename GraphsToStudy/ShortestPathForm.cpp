#include "ShortestPathForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace System::Drawing;

Void GraphsToStudy::ShortestPathForm::onShown(System::Object^ sender, System::EventArgs^ e)
{
    int amountOfLevels = CalculateLevels(); // ��������� ����� ������� ��������� �� ����� �������
    CalculatePositions(amountOfLevels);
    VisualizeGraph(sender);
}

Void GraphsToStudy::ShortestPathForm::VisualizeGraph(System::Object^ sender) // ���� ������ �������, ����� �� � ��������� �����, ��������� �� �� ������ � ������� � ����� �������, � ������� �� ��� ����� ������� 
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
        Trace::WriteLine("��������� " + (i + 1) + " �������");

        //Trace::WriteLine("�������� ��� ��� " + (i + 1).ToString() + " �������");
        //for (int j = i + 1; j < size; j++) // ��� ������� �������� ������� ��
        //{
        //    Trace::WriteLine("i: " + i.ToString() + " j: " + j.ToString() + " �������� � �������: " + matrix[i][j].ToString());
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
        //            Trace::WriteLine("���������� ������� " + name);
        //        }
        //        if (positions[i] != nullptr)
        //        {
        //            Trace::WriteLine("���������� ����� �� " + (i + 1).ToString() + " ������� �� " + (j + 1).ToString());
        //            graph->DrawLine(pen, positions[i]->X, positions[i]->Y, positions[j]->X, positions[j]->Y);
        //        }
        //    }
        //}
    }
}

// ���������� �� ������� ��������� �� ����� ������� ����� ������� ���������, ���������� ���������� ����������� �������
int GraphsToStudy::ShortestPathForm::CalculateLevels()
{
    levels = gcnew array<array<int>^>(size);
    int addedVerticesAmount = 1;

    for (int levelIndex = 0; levelIndex < size; levelIndex++)
    {
        levels[levelIndex] = gcnew array<int>(0);
        if (levelIndex == 0) // ���� ������ �������, ������� �� � �������
        {
            Array::Resize(levels[levelIndex], 1);
            levels[0][0] = 1; //� ������� ��� ������� ������ ����� ������ �������
            Trace::WriteLine("������� 0 ��������� � ������� 0");
        }
        else
        {
            int prevLevelIndex = levelIndex - 1;
            for (int i = 0; i < levels[prevLevelIndex]->Length; i++) // ���� ������ ���� ������ ����������� ������
            {
                int rootIndex = levels[prevLevelIndex][i] - 1;
                for (int j = 0; j < size; j++) // ���� ������ ������ � ������� ��������� ��� ������� ����������� ������
                {
                    if (matrix[rootIndex][j] > 0 && rootIndex != j && !IsInLevels(j, levelIndex + 1)) // ��������� �������, ������� �������� ������, ��������� � ���� ����� ���� ��� ��������� ������� �������
                    {
                        AddToLevel(levelIndex, j);
                        addedVerticesAmount++;
                        Trace::WriteLine("������� " + (j).ToString() + " ��������� � ������� " + levelIndex.ToString());
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
    int Y = 225;

    vertices[0] = gcnew Vertex;
    vertices[0]->Name = (1).ToString();
    vertices[0]->X = X;
    vertices[0]->Y = Y;
    Trace::WriteLine("������� ���������� ������ �������");
    for (int i = 1; i < amountOfLevels; i++) // ���� ������ ������� �������� �������
    {
        X += 100;
        int modifier = 0;
        int multiplier = 1;
        int levelSize = levels[i]->Length;
        if (levelSize % 2 == 0)
        {
            modifier += 50;
        }
        for (int j = 0; j < levelSize; j++) // ���� ������ ������� ������� +100 -200 +300 -400
        {
            multiplier = -multiplier;
            int vertex = levels[i][j];

            vertices[vertex - 1] = gcnew Vertex;
            vertices[vertex - 1]->Name = vertex.ToString();
            vertices[vertex - 1]->X = X;
            vertices[vertex - 1]->Y = Y + modifier * multiplier;
            Trace::WriteLine("������� ���������� " + vertex + " �������");            
            
            if (j % 2 == 1)
            {
                modifier += 100;
            }
        }
    }
}
