#include "ShortestPathForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;

Void GraphsToStudy::ShortestPathForm::onShown(System::Object^ sender, System::EventArgs^ e)
{
    DrawGraph(sender);
}

Void GraphsToStudy::ShortestPathForm::DrawGraph(System::Object^ sender)
{
    pictureBox1->Image = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
    Pen^ p = gcnew Pen(Color::Blue, 1.0f);
    Point pt1 = Point(10, 10);
    Point pt2 = Point(100, 100);
    Graphics^ g = Graphics::FromImage(pictureBox1->Image);
    g->DrawLine(p, pt1, pt2);
}


