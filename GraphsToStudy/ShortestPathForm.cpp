#include "ShortestPathForm.h"

using namespace System;
using namespace System::Windows::Forms;

Void GraphsToStudy::ShortestPathForm::onShown(System::Object^ sender, System::EventArgs^ e)
{
    DrawGraph(sender, e);
}

Void GraphsToStudy::ShortestPathForm::DrawGraph(System::Object^ sender, System::EventArgs^ e)
{
    Graphics^ g = pictureBox1->CreateGraphics();
    Pen^ p = gcnew Pen(Color::Blue, 1.0f);
    Point pt1 = Point(10, 10);
    Point pt2 = Point(100, 100);
    g->DrawLine(p, pt1, pt2);
}

Void GraphsToStudy::ShortestPathForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    DrawGraph(sender, e);
}

