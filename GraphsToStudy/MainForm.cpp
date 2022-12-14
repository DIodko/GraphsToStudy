#include "MainForm.h"
#include "GraphsToSolve.h"
#include "GraphsToVisualize.h"
#include "TheoryForm.h"

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

// функция для решения задания, которая визуализирует текущее сформированное задание в зависимости от задания
Void GraphsToStudy::MainForm::VisualizeTask(System::Object^ sender, System::EventArgs^ e)
{	
	if (comboBox2->Text == "Поиск величины кратчайшего пути с помощью алгоритма Дейкстры")
	{
		GraphsToVisualize::VisualizeDijkstra(matrix, size, ways, correctMarkers);
	}
	else if (comboBox2->Text == "Определение уровней графа с помощью алгоритма Демукрона")
	{
		GraphsToVisualize::VisualizeDemoucron(matrix, size, levels);
	}
}

// функция, которая вызывается первой, формирует задание, решает его и выводит матрицу смежности в зависимости от задания
Void GraphsToStudy::MainForm::ShowMatrix(System::Object^ sender, System::EventArgs^ e)
{
	if (!Int32::TryParse(this->comboBox1->Text, size))
	{
		MessageBox::Show("Некорректное число вершин", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		ResetCurrentValues(sender, e);
		this->comboBox1->Text = "5";
		return;
	}
	if (size < 5 || size > 15)
	{
		MessageBox::Show("Некорректное число вершин", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		ResetCurrentValues(sender, e);
		this->comboBox1->Text = "5";
		return;
	}


	if (comboBox2->Text == "Поиск величины кратчайшего пути с помощью алгоритма Дейкстры")
	{
		matrix = gcnew array<array<int>^>(size);
		ways = gcnew array<array<int>^>(size);
		correctMarkers = gcnew array<int>(size);

		GraphsToSolve::GenerateDijkstra(matrix, size);
		GraphsToSolve::SolveDijkstra(matrix, size, ways, correctMarkers);
	}
	else if (comboBox2->Text == "Определение уровней графа с помощью алгоритма Демукрона")
	{
		matrix = gcnew array<array<int>^>(size);
		levels = gcnew array<array<int>^>(size);

		GraphsToSolve::GenerateDemoucron(matrix, size);
		GraphsToSolve::SolveDemoucron(matrix, size, levels);
	}
	else
	{
		MessageBox::Show("Некорректное задание", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		comboBox2->Text = "Поиск величины кратчайшего пути с помощью алгоритма Дейкстры";
		ResetCurrentValues(sender, e);
		return;
	}

	dataGridView1->Columns->Clear();
	this->button3->Enabled = true;
	this->button1->Enabled = true;
	this->label3->Visible = true;
	this->label4->Visible = false;
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

Void GraphsToStudy::MainForm::ShowTheory(System::Object^ sender, System::EventArgs^ e)
{
	GraphsToStudy::TheoryForm^ theoryForm = gcnew GraphsToStudy::TheoryForm(comboBox2->Text);
	theoryForm->Show();
}

// функция, которая выводит решение по нажатию кнопки разными способами в зависимости от задания
Void GraphsToStudy::MainForm::ShowSolution(System::Object^ sender, System::EventArgs^ e)
{
	this->label4->Visible = true;
	this->button3->Enabled = false;
	this->button1->Enabled = false;

	dataGridView2->Columns->Clear();
	int GridColumnWidth = 25;

	if (comboBox2->Text == "Поиск величины кратчайшего пути с помощью алгоритма Дейкстры")
	{
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
				dataGridView2->Rows[i]->Cells[0]->Value = correctMarkers[i - 1];
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
	}
	else if (comboBox2->Text == "Определение уровней графа с помощью алгоритма Демукрона")
	{
		dataGridView2->TopLeftHeaderCell->Value = "Уровень";
		dataGridView2->Height = 20;
		dataGridView2->Width = 222;

		dataGridView2->Columns->Add("0", "Список вершин на уровне");
		dataGridView2->Columns[0]->Width = 150;
		dataGridView2->Columns[0]->SortMode = DataGridViewColumnSortMode::NotSortable;

		for (int i = 0; i < levels->Length && levels[i] != nullptr && levels[i]->Length != 0; i++)
		{
			dataGridView2->Height += 22;	
			dataGridView2->Rows->Add();
			dataGridView2->Rows[i]->HeaderCell->Value = (i + 1).ToString();

			dataGridView2->Rows[i]->Cells[0]->Value = levels[i][0].ToString();

			for (int j = 1; j < levels[i]->Length; j++)
			{
				dataGridView2->Rows[i]->Cells[0]->Value += ", " + levels[i][j].ToString();
			}
		}
	}
	dataGridView2->Visible = true;
}

// изменяет свойства компонентов формы при изменении задания
Void GraphsToStudy::MainForm::ResetCurrentValues(System::Object^ sender, System::EventArgs^ e)
{
	matrix = nullptr;
	ways = nullptr;
	correctMarkers = nullptr;

	this->label3->Visible = false;
	this->label4->Visible = false;

	this->dataGridView1->Visible = false;
	this->dataGridView2->Visible = false;

	this->button1->Enabled = false;
	this->button3->Enabled = false;
}

// изменяет свойства компонентов формы при изменении количества вершин
Void GraphsToStudy::MainForm::DifferentVertexAmountSelected(System::Object^ sender, System::EventArgs^ e)
{
	size = Convert::ToInt32(this->comboBox1->Text);

	ResetCurrentValues(sender, e);
}