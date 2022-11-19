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
	array<array<int>^>^ correct_ways = gcnew array<array<int>^>(size);
	array<int>^ correct_markers = gcnew array<int>(size);
	array<int>^ ways = gcnew array<int>(size);
	ways[0] = 0;
	for (int i = 1; i < size; i++) {
		ways[i] = 1000000;
	}
	array<int>^ markers = gcnew array<int>(size);
	markers[0] = 1;
	for (int i = 1; i < size; i++) {
		markers[i] = 0;
	}
	// Ищем минимальный путь алгоритмом Дейкстры

	int curr_vertex = 0; //текущая вершина
	for (int k = 0; markers[size - 1] == 0; k++) { // заполняем size меток, по одной на каждой итерации
		correct_ways[k] = gcnew array<int>(size);
		for (int j = 0; j < size; j++) { // проходимся по строке в матрице для текущей вершины
			if (matrix[curr_vertex][j] != 0) { // если есть путь
				// если значение пути в вершину больше чем значение пути в эту вершину и из нее в ту то обновляем
				ways[j] = (ways[j] > (ways[curr_vertex] + matrix[curr_vertex][j])) ? ways[curr_vertex] + matrix[curr_vertex][j] : ways[j];
			}		
		}
		int min_marker = 1000000;
		for (int i = 0; i < size; i++) { //проходимся по всем вершинам
			if (markers[i] != 1 && ways[i] < min_marker) { // если вершина не помечена постоянной и значение пути в нее минимально помечаем постоянной
				curr_vertex = i;
				min_marker = ways[i];
			}
		}
		ways->CopyTo(correct_ways[k], 0);
		correct_markers[k] = curr_vertex;
		markers[curr_vertex] = 1;
	}
	Trace::WriteLine(ways[size-1]);

	GraphsToStudy::ShortestPathForm^ newShortestPathForm = gcnew GraphsToStudy::ShortestPathForm("Алгоритм Дейкстры", matrix, size);
	newShortestPathForm->Show();
}

array<array<int>^>^ GraphsToStudy::MainForm::GenerateMatrix(int size)
{
	array<int>^ vertices = gcnew array<int>(size);
	array<array<int>^>^ matrix = gcnew array<array<int>^>(size);
	//{ 
	//	{ 0, 0, 9, 0, 5, 8, 0 },
	//	{ 0, 0, 0, 0, 0, 3, 1 },
	//	{ 9, 0, 0, 6, 0, 0, 0 },
	//	{ 0, 0, 6, 0, 0, 0, 9 },
	//	{ 5, 0, 0, 0, 0, 0, 7 },
	//	{ 8, 3, 0, 0, 0, 0, 0 },
	//	{ 0, 1, 0, 9, 7, 0, 0 },
	//};
	array<array<int>^>^ routes = gcnew array<array<int>^>(size);
	Random^ rand = gcnew Random();
	for (int i = 0; i < size; i++) {
		matrix[i] = gcnew array<int>(size);
		routes[i] = gcnew array<int>(size);
		vertices[i] = 1;
	}
	//создание маршрутов
	
	int counter = 0;
	for (int i = 0; i < size && counter < size - 2; i++) {
		int j = 0;
		bool routeDone = false;
		while (!routeDone) {
			int probability = rand->Next(0, 100);
			if ((probability < 50 && j < 4) || j < 2) {
				int num = rand->Next(1, size - 1);
				while (vertices[num] == 0)
				{
					num = rand->Next(1, size - 1);
				}
				routes[i][j] = num;
				vertices[num] = 0;
				j++;
				counter++;
			}
			if (counter == size - 2 || (probability >= 50 && j >= 2) || j >= 4) {
				routes[i][j] = size - 1;
				routeDone = true;
			}
		}
		
	}

	//for (int i = 0; i < size; i++)
	//{
	//	Trace::Write((i + 1) + ": ");
	//	for (int j = 0; j < size; j++)
	//	{
	//		Trace::Write(routes[i][j] + " ");
	//	}
	//	Trace::WriteLine("");
	//}

	//заполнение матрицы
	for (int i = 0; i < size && routes[i][0] != 0; i++) { // цикл для обхода путей
		matrix[0][routes[i][0]] = rand->Next(1, 15);
		matrix[routes[i][0]][0] = matrix[0][routes[i][0]];
		for (int j = 0; j < size - 1; j++) { // цикл для обхода пути
			if (routes[i][j + 1] != 0) {
				int index1 = routes[i][j];
				int index2 = routes[i][j + 1];
				matrix[index1][index2] = rand->Next(1, 15);
				matrix[index2][index1] = matrix[index1][index2];
			}
			else break;
		}
	}
	if (routes[1][0] == 0) // если один маршрут, добавить случайную связь
	{
		matrix[routes[0][0]][routes[0][2]] = rand->Next(1, 15);
		matrix[routes[0][2]][routes[0][0]] = matrix[routes[0][0]][routes[0][2]];
	}

	//	Отладочный вывод матрицы
	//for (int i = 0; i < size; i++)
	//{
	//	Trace::Write((i + 1) + ": ");
	//	for (int j = 0; j < size; j++)
	//	{
	//		Trace::Write(matrix[i][j] + " ");
	//	}
	//	Trace::WriteLine("");
	//}
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
