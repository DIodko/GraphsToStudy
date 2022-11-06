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
	//array<array<int>^>^ matrix = gcnew array<array<int>^>(size);
	//for (int i = 0; i < size; i++)
	//{
	//	matrix[i] = gcnew array<int>(size);
	//	for (int j = 0; j < size; j++)
	//	{
	//		matrix[i][j] = (i + j) % 2;
	//	}
	//}
	array<array<int>^>^ matrix = gcnew array<array<int>^>{ 
	////   1  2  3  4  5
	//	{1, 0, 1, 0, 1}, // 1 вершина, "1" на графе  1 0 1 0 0
	//	{0, 1, 1, 0, 1}, // 2 вершина, "2" на графе  0
	//	{1, 1, 1, 1, 0}, // 3 вершина, "3" на графе  1 1
	//	{0, 0, 1, 1, 1}, // 4 вершина, "4" на графе  0 0 0
	//	{1, 1, 0, 1, 1}};// 5 вершина, "5" на графе  0 0 0 0
	//   1  2  3  4  5
		{1, 0, 0, 0, 1}, // 1 вершина, "1" на графе  1 0 1 0 0
		{0, 1, 1, 1, 1}, // 2 вершина, "2" на графе  0
		{0, 1, 1, 1, 0}, // 3 вершина, "3" на графе  1 1
		{0, 1, 1, 0, 1}, // 4 вершина, "4" на графе  0 0 0
		{1, 1, 0, 1, 1}};// 5 вершина, "5" на графе  0 0 0 0
	GraphsToStudy::ShortestPathForm^ newShortestPathForm = gcnew GraphsToStudy::ShortestPathForm("Тип задания", matrix, size);
	newShortestPathForm->Show();
}