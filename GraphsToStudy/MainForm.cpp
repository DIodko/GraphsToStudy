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

	GraphsToSolve::MainForm form;
	Application::Run(% form);
}

Void GraphsToSolve::MainForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{	
	//Генерируем матрицу смежности для алгоритма Дейкстры

	if (matrix == nullptr)
	{
		matrix = gcnew array<array<int>^>(size);
		ways = gcnew array<array<int>^>(size);
		correctMarkers = gcnew array<int>(size);

		DijkstraGeneration::GenerateMatrix(matrix, size);
		DijkstraGeneration::SolveDijkstra(ways, size, matrix, correctMarkers);
	}

	GraphsToVisualize::VisualizeDijkstra(matrix, size, ways, correctMarkers);

	/*ResetCurrentValues();*/
}


Void GraphsToSolve::MainForm::ShowMatrix(System::Object^ sender, System::EventArgs^ e)
{
	this->button3->Enabled = true;
	this->button1->Enabled = true;
	this->label3->Visible = true;
	this->label4->Visible = false;
	dataGridView1->Columns->Clear();

	matrix = gcnew array<array<int>^>(size);
	ways = gcnew array<array<int>^>(size);
	correctMarkers = gcnew array<int>(size);

	DijkstraGeneration::GenerateMatrix(matrix, size);
	DijkstraGeneration::SolveDijkstra(ways, size, matrix, correctMarkers);

	int GridColumnWidth = 25;
	dataGridView1->Height = 22 * size + 20;
	dataGridView1->Width = GridColumnWidth * size + 52;

	for (int i = 0; i < size; i++)
	{
		dataGridView1->Columns->Add((i + 1).ToString(), (i + 1).ToString());
		dataGridView1->Columns[i]->Width = GridColumnWidth;
		dataGridView1->Columns[i]->SortMode = DataGridViewColumnSortMode::NotSortable;
	}

	for (int i = 0; i < size; i++) // заполнение матрицы смежности
	{
		dataGridView1->Rows->Add();
		dataGridView1->Rows[i]->HeaderCell->Value = (i + 1).ToString();
		for (int j = 0; j < size; j++)
		{
			dataGridView1->Rows[i]->Cells[j]->Value = matrix[i][j];
		}
	}

	this->dataGridView1->Location = System::Drawing::Point(this->Width / 2 - this->dataGridView1->Width - 20, 161);
	this->label3->Location = System::Drawing::Point(this->dataGridView1->Location.X, 135);

	dataGridView2->Visible = false;
	dataGridView1->Visible = true;
}


Void GraphsToSolve::MainForm::ShowSolution(System::Object^ sender, System::EventArgs^ e)
{
	this->label4->Visible = true;
	this->button3->Enabled = false;

	if (matrix == nullptr)
	{
		ShowMatrix(sender, e);
	}

	dataGridView2->Columns->Clear();
	int GridColumnWidth = 25;

	dataGridView2->TopLeftHeaderCell->Value = "Итерация";
	dataGridView2->Height = 22 * size + 20;
	dataGridView2->Width = GridColumnWidth * (size + 1) + 72;

	dataGridView2->Columns->Add("0", "X");
	dataGridView2->Columns[0]->Width = GridColumnWidth;
	dataGridView2->Columns[0]->SortMode = DataGridViewColumnSortMode::NotSortable;

	for (int i = 0; i < size; i++)
	{
		dataGridView2->Columns->Add((i + 1).ToString(), (i + 1).ToString());
		dataGridView2->Columns[i + 1]->Width = GridColumnWidth;
		dataGridView2->Columns[i + 1]->SortMode = DataGridViewColumnSortMode::NotSortable;
	}

	for (int i = 0; i < size; i++) 
	{
		dataGridView2->Rows->Add();
		dataGridView2->Rows[i]->HeaderCell->Value = (i).ToString();

		if (i == 0)
		{
			dataGridView2->Rows[i]->Cells[0]->Value = "-";
		}
		else
		{
			dataGridView2->Rows[i]->Cells[0]->Value = correctMarkers[i];
		}
		for (int j = 0; j < size; j++)
		{
			dataGridView2->Rows[i]->Cells[j + 1]->Value = (ways[i][j] > 500) ? L"∞" : ways[i][j].ToString();
			bool isMarked = false;
			for (int k = 0; k < i + 1; k++)
			{
				if (correctMarkers[k] == j + 1)
					isMarked = true;
			}
			if (isMarked)
			{
				dataGridView2->Rows[i]->Cells[j + 1]->Value += "*";
			}
		}
	}

	dataGridView2->Visible = true;
}

Void GraphsToSolve::MainForm::DifferentTaskSelected(System::Object^ sender, System::EventArgs^ e)
{
	this->label3->Visible = false;
	this->label4->Visible = false;

	this->dataGridView1->Visible = false;
	this->dataGridView2->Visible = false;

	this->button1->Enabled = false;
	this->button3->Enabled = false;

	ResetCurrentValues();
}

Void GraphsToSolve::MainForm::ResetCurrentValues()
{
	matrix = nullptr;
	ways = nullptr;
	correctMarkers = nullptr;
}

Void GraphsToSolve::MainForm::DifferentVertexAmountSelected(System::Object^ sender, System::EventArgs^ e)
{
	this->label3->Visible = false;
	this->label4->Visible = false;

	this->dataGridView1->Visible = false;
	this->dataGridView2->Visible = false;

	this->button1->Enabled = false;
	this->button3->Enabled = false;

	size = Convert::ToInt32(this->comboBox1->Text);

	ResetCurrentValues();
}

