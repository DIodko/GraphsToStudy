#include "TheoryForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace System::IO;

Void GraphsToStudy::TheoryForm::onShown(System::Object^ sender, System::EventArgs^ e)
{
	StreamReader^ textFile = File::OpenText(taskName + ".txt");

	String^ str = "";
	while ((str = textFile->ReadLine()) != nullptr)
	{
		this->textBox1->Text += str + Environment::NewLine;
	}

	Image^ image = gcnew Bitmap(taskName + ".jpg");
	this->pictureBox1->Image = image;
}

Void GraphsToStudy::TheoryForm::onCloseButtonClick(System::Object^ sender, System::EventArgs^ e)
{
	this->Close();
}

Void GraphsToStudy::TheoryForm::onSelectionChanged(System::Object^ sender, System::EventArgs^ e)
{
	taskName = this->comboBox1->Text;
	this->textBox1->Text = "";
	onShown(sender, e);
}
