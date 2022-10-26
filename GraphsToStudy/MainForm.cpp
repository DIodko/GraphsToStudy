#include "MainForm.h"
#include "ShortestPathForm.h"

using namespace System;
using namespace System::Windows::Forms;

void main(array<String^>^ args)
{
	Application::EnableVisualStyles;
	Application::SetCompatibleTextRenderingDefault(false);

	GraphsToStudy::MainForm form;
	Application::Run(% form);
}

Void GraphsToStudy::MainForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	GraphsToStudy::ShortestPathForm^ newShortestPathForm = gcnew GraphsToStudy::ShortestPathForm();
	newShortestPathForm->Show();
	//newShortestPathForm->onShown(sender, e);
}