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
	size = 5;
	array<array<int>^>^ matrix = gcnew array<array<int>^>(size);
	for (int i = 0; i < size; i++)
	{
		matrix[i] = gcnew array<int>(size);
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = (i + j) % 2;
		}
	}
	GraphsToStudy::ShortestPathForm^ newShortestPathForm = gcnew GraphsToStudy::ShortestPathForm("Тип задания", matrix, size);
	newShortestPathForm->Show();
}