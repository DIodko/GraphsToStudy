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
    pictureBox1->Image = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
    Pen^ pen = gcnew Pen(Color::Black, 1.0f);
    Brush^ brush = Brushes::Black;
    Drawing::Font^ font = gcnew Drawing::Font("Arial", 20);
    Graphics^ graph = Graphics::FromImage(pictureBox1->Image);
    positions = gcnew array<Position^>(size);

    for (int i = 0; i < size; i++)
    {
        positions[i] = gcnew Position;
        if (i == 0)
        {
            String^ name = i.ToString();
            positions[i]->X = 20;
            positions[i]->Y = 225;
            graph->DrawEllipse(pen, positions[i]->X, positions[i]->Y, 50, 50);
            graph->DrawString(name, font, brush, positions[i]->X + 15, positions[i]->Y + 10);
        }
        //for (int j = 0; j < size; j++)
        //{
        //    if (matrix[i][j] == 1)
        //    {

        //    }
        //}
    }
}


