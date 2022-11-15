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
	array<array<int>^>^ matrix = GenerateMatrix(size);
	
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

array<array<int>^>^ GraphsToStudy::MainForm::GenerateMatrix(int size)
{
	//array<array<int>^>^ matrix = gcnew array<array<int>^>(size);
	//Random^ rand = gcnew Random();
	//Random^ rand_help = gcnew Random();
	//for (int i = 0; i < size; i++) {
	//	matrix[i] = gcnew array<int>(size);
	//}
	//for (int i = 0; i < size; i++)
	//{
	//	int tempJ = -1;
	//	int not_null_str = 0;
	//	for (int j = i + 1; j < size; j++)
	//	{
	//		int true_random = rand->Next(0, 101);
	//		if (true_random > 5) {
	//			matrix[i][j] = 0;
	//		}
	//		else
	//		{
	//			tempJ = j;
	//			matrix[i][j] = rand->Next(1, 15);
	//			not_null_str++;
	//		}
	//		matrix[j][i] = matrix[i][j];
	//	}
	//	if (not_null_str == 0 && i + 2 < size) {
	//		int j = rand->Next(i + 1, size - 1);
	//		matrix[i][j] = rand->Next(1, 15);
	//		matrix[j][i] = matrix[i][j];
	//		tempJ = j;
	//		not_null_str++;
	//	}
	//	if (not_null_str == 1 && i + 2 < size)
	//	{
	//		int j = rand->Next(i + 1, size);
	//		while (j == tempJ) {
	//			j = rand->Next(i + 1, size);
	//		}
	//		matrix[i][j] = rand->Next(1, 15);
	//		matrix[j][i] = matrix[i][j];
	//	}
	//}
	////	Отладочный вывод матрицы
	//for (int i = 0; i < size; i++)
	//{
	//	for (int j = 0; j < size; j++)
	//	{
	//		Trace::Write(matrix[i][j] + " ");
	//	}
	//	Trace::WriteLine(" ");
	//}
	array<int>^ amounts = gcnew array<int>(size);
	array<array<int>^>^ matrix = gcnew array<array<int>^>(size);
	Random^ rand = gcnew Random();
	for (int i = 0; i < size; i++) {
		matrix[i] = gcnew array<int>(size);
	}

	for (int i = 0; i < size; i++)
	{
		int amountOfLines = 2;
		//int amountOfLines = rand->Next(2, 4);
		for (int j = 0; j < i; j++)
		{
			if (matrix[i][j] != 0)
			{
				amountOfLines--;
			}
		}

		while (amountOfLines > 0)
		{
			FillRandom(i, matrix, size, amounts);
			amountOfLines--;
		}

	}
	//	Отладочный вывод матрицы
	for (int i = 0; i < size; i++)
	{
		Trace::Write((i + 1) + ": ");
		for (int j = 0; j < size; j++)
		{
			Trace::Write(matrix[i][j] + " ");
		}
		Trace::WriteLine("");
	}
	return matrix;
}

// не должны перезаписывать уже созданное значение, не должны записывать на главную диагональ
// не должно быть больше 4 путей в вершину, если есть путь в 1, не должно быть пути в 20 и наоборот
void GraphsToStudy::MainForm::FillRandom(int index, array<array<int>^>^ matrix, int size, array<int>^ amounts)
{ 
	Random^ rand = gcnew Random();
	int j = rand->Next(0, size); 
	//while (matrix[index][j] > 0 || index == j || amounts[j] >= 3 || abs(index - j) == size - 1
	while (matrix[index][j] > 0 || index == j || amounts[j] >= 4 || abs(index - j) == size - 1
		 || BetweenFirstLast(index, matrix, size, j))
	{
		j = rand->Next(0, size);
	}
	amounts[j]++;
	amounts[index]++;
	matrix[index][j] = rand->Next(1, 15);
	matrix[j][index] = matrix[index][j];
} 


bool GraphsToStudy::MainForm::BetweenFirstLast(int index, array<array<int>^>^ matrix, int size, int j)
{
	return (matrix[0][j] > 0 && index == size - 1) || 
		   (matrix[size - 1][j] > 0 && index == 0) || 
		   (matrix[0][index] > 0 && j == size - 1) || 
		   (matrix[size - 1][index] > 0 && j == 0);
}