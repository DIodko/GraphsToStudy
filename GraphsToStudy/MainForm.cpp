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
	int size = Convert::ToInt32(this->comboBox1->Text);
	array<array<int>^>^ matrix = gcnew array<array<int>^>(size);
	array<int>^ ways = gcnew array<int>(size);

	DijkstraGeneration::GenerateMatrix(matrix, size);
	DijkstraGeneration::SolveDijkstra(ways, size, matrix);

	GraphsToVisualize::VisualizeDijkstra(matrix, size, ways);
	//GraphsToVisualize::VisualizeDijkstra(matrix, size, ways);
}
