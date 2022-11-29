#include "MainForm.h"
#include "DijkstraGeneration.h"
#include "GraphsToVisualize.h"
//#include "DemoucronGeneration.h"

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
	int size = 0;

	if (!int::TryParse(comboBox1->Text, size) || size < 5 || size > 15) {
		MessageBox::Show("Введите число от 5 до 15");
		return;
	}
	
	array<array<int>^>^ matrix = gcnew array<array<int>^>(size);
	array<array<int>^>^ ways = gcnew array<array<int>^>(size);
	array<int>^ correctMarkers = gcnew array<int>(size);

	DijkstraGeneration::GenerateMatrix(matrix, size);
	DijkstraGeneration::SolveDijkstra(ways, size, matrix, correctMarkers);

	GraphsToVisualize::VisualizeDijkstra(matrix, size, ways, correctMarkers);
}
