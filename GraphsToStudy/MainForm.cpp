#include "MainForm.h"
#include "ShortestPathForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;

void main(array<String^>^ args)
{
	Application::EnableVisualStyles;
	Application::SetCompatibleTextRenderingDefault(false);

	GraphsToStudy::MainForm form;
	Application::Run(% form);
}

Void GraphsToStudy::MainForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{	
	//Генерируем матрицу смежности для алгоритма Дейкстры
	size = Convert::ToInt32(this->comboBox1->Text);
	array<array<int>^>^ matrix = gcnew array<array<int>^>(size);
	Random^ rand = gcnew Random();
	Random^ rand_help = gcnew Random();
	int k = 1;
	for (int i = 0; i < size; i++) {
		matrix[i] = gcnew array<int>(size);
	}
	for (int i = 0; i < size; i++)
	{	
		int not_null_str = 0;
		for (int j = k; j < size; j++)
		{
			int true_random = rand->Next(0, 101);
			if (true_random > 25) {
				matrix[i][j] = 0;
			}
			else
			{
				matrix[i][j] = rand->Next(1, 15);
				not_null_str++;
			}
			matrix[j][i] = matrix[i][j];
		}
		if (not_null_str == 0) {
			int j = rand->Next(1, size);
			matrix[i][j] = rand->Next(1, 15);
			matrix[j][i] = matrix[i][j];
		}
		k++;
	}
	//Отладочный вывод матрицы
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Trace::Write(matrix[i][j] + " ");
		}
		Trace::WriteLine( " ");
	}
	
	
	//Массивы для временных меток и постоянных меток
	array<int>^ ways = gcnew array<int>(size);
	ways[0] = 0;
	for (int i = 1; i < size; i++) {
		ways[i] = 10000;
	}
	array<int>^ markers = gcnew array<int>(size);
	markers[0] = 1;
	for (int i = 1; i < size; i++) {
		markers[i] = 0;
	}
	// Ищем минимальный путь алгоритмом Дейкстры

	int Xt = 0; //текущая вершина
	while (markers[size-1] == 0) {
		for (int j = 0; j < size; j++) {
			if (matrix[Xt][j] != 0) {
				int temp_marker = (ways[j] > (ways[Xt] + matrix[Xt][j])) ? ways[Xt] + matrix[Xt][j] : ways[j];
				ways[j] = temp_marker;
			}		
		}
		int min_marker = 10000;
		for (int i = 0; i < size; i++) {
			if (markers[i] != 1 && ways[i] < min_marker) {
				Xt = i;
			}
		}
		markers[Xt] = 1;
	}
	Trace::WriteLine(ways[size-1]);



	GraphsToStudy::ShortestPathForm^ newShortestPathForm = gcnew GraphsToStudy::ShortestPathForm("Алгоритм Дейкстры", matrix, size);
	newShortestPathForm->Show();
}