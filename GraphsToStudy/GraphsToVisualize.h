#pragma once

namespace GraphsToVisualize {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	void VisualizeDijkstra(array<array<int>^>^ matrix, int size, array<array<int>^>^ ways, array<int>^ correctMarkers);
	void VisualizeDemoucron(array<array<int>^>^ matrix, int size, array<array<int>^>^ levels);

	public ref class VisualizationForm : public System::Windows::Forms::Form
	{
	public:
		VisualizationForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		VisualizationForm(array<array<int>^>^ _matrix, int _size, array<array<int>^>^ _ways, array<int>^ _correctMarkers)
		{
			matrix = _matrix;
			size = _size;
			ways = _ways;
			correctMarkers = _correctMarkers;
			taskName = "Алгоритм Дейкстры";
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		VisualizationForm(array<array<int>^>^ _matrix, int _size, array<array<int>^>^ _levels)
		{
			matrix = _matrix;
			size = _size;
			levels = _levels;
			taskName = "Алгоритм Демукрона";
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~VisualizationForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::DataGridView^ conditionGridView;
	private: System::Windows::Forms::Label^ conditionLabel;
	private: System::Windows::Forms::DataGridView^ dataGridView2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ checkSolutionButton;

	private: System::Windows::Forms::Button^ showSolutionButton;
	private: System::Windows::Forms::TextBox^ textBox1;




	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->conditionGridView = (gcnew System::Windows::Forms::DataGridView());
			this->conditionLabel = (gcnew System::Windows::Forms::Label());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->checkSolutionButton = (gcnew System::Windows::Forms::Button());
			this->showSolutionButton = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->conditionGridView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";			
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->Size = System::Drawing::Size(1200, 720);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// conditionGridView
			// 
			this->conditionGridView->AllowUserToAddRows = false;
			this->conditionGridView->AllowUserToDeleteRows = false;
			this->conditionGridView->AllowUserToResizeColumns = false;
			this->conditionGridView->AllowUserToResizeRows = false;
			this->conditionGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->conditionGridView->Location = System::Drawing::Point(1218, 37);
			this->conditionGridView->Name = L"conditionGridView";
			this->conditionGridView->ReadOnly = true;
			this->conditionGridView->RowHeadersWidth = 50;
			this->conditionGridView->ShowRowErrors = false;
			this->conditionGridView->Size = System::Drawing::Size(240, 150);
			this->conditionGridView->TabIndex = 1;
			// 
			// conditionLabel
			// 
			this->conditionLabel->AutoSize = true;
			this->conditionLabel->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Bold));
			this->conditionLabel->Location = System::Drawing::Point(1218, 12);
			this->conditionLabel->Name = L"conditionLabel";
			this->conditionLabel->Size = System::Drawing::Size(173, 23);
			this->conditionLabel->TabIndex = 2;
			this->conditionLabel->Text = L"Матрица смежности";
			// 
			// dataGridView2
			// 
			this->dataGridView2->AllowUserToAddRows = false;
			this->dataGridView2->AllowUserToDeleteRows = false;
			this->dataGridView2->AllowUserToResizeColumns = false;
			this->dataGridView2->AllowUserToResizeRows = false;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Location = System::Drawing::Point(1218, 360);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->RowHeadersWidth = 70;
			this->dataGridView2->ShowRowErrors = false;
			this->dataGridView2->Size = System::Drawing::Size(240, 150);
			this->dataGridView2->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Bold));
			this->label2->Location = System::Drawing::Point(1219, 344);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(81, 23);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Решение";
			// 
			// checkSolutionButton
			// 
			this->checkSolutionButton->BackColor = System::Drawing::Color::White;
			this->checkSolutionButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14));
			this->checkSolutionButton->Location = System::Drawing::Point(1218, 740);
			this->checkSolutionButton->Name = L"checkSolutionButton";
			this->checkSolutionButton->Size = System::Drawing::Size(120, 60);
			this->checkSolutionButton->TabIndex = 5;
			this->checkSolutionButton->Text = L"Проверить решение";
			this->checkSolutionButton->UseVisualStyleBackColor = true;
			this->checkSolutionButton->Click += gcnew System::EventHandler(this, &VisualizationForm::CheckSolution);
			// 
			// showSolutionButton
			// 
			this->showSolutionButton->BackColor = System::Drawing::Color::White;
			this->showSolutionButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14));
			this->showSolutionButton->Location = System::Drawing::Point(1372, 740);
			this->showSolutionButton->Name = L"showSolutionButton";
			this->showSolutionButton->Size = System::Drawing::Size(120, 60);
			this->showSolutionButton->TabIndex = 6;
			this->showSolutionButton->Enabled = false;
			this->showSolutionButton->Text = L"Показать решение";
			this->showSolutionButton->UseMnemonic = false;
			this->showSolutionButton->UseVisualStyleBackColor = true;
			this->showSolutionButton->Click += gcnew System::EventHandler(this, &VisualizationForm::ShowSolution);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(12, 750);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true; 
			this->textBox1->ScrollBars = ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(500, 197);
			this->textBox1->TabIndex = 7;
			this->textBox1->Visible = false;
			// 
			// DijkstraVisualizationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1800, 959);
			this->BackColor = System::Drawing::Color::FromArgb(179, 229, 252);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->showSolutionButton);
			this->Controls->Add(this->checkSolutionButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->conditionLabel);
			this->Controls->Add(this->conditionGridView);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"DijkstraVisualizationForm";
			this->Text = L"Решение задания";
			this->Shown += gcnew System::EventHandler(this, &VisualizationForm::onShown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->conditionGridView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		ref struct Vertex
		{
			String^ Name;
			int X;
			int Y;
		};

		Void onShown(System::Object^ sender, System::EventArgs^ e); // при вызове формы вызывает все остальные функции для вывода
		Void VisualizeGraph(array<Vertex^>^ vertices); 
		Void VisualizeTables();
		Void CheckSolution(System::Object^ sender, System::EventArgs^ e);
		Void ShowSolution(System::Object^ sender, System::EventArgs^ e);

		// функции ответственные за корректную визуализацию графа
		void AddOffsetsBasedOnLevels(array<array<int>^>^ levels, array<Vertex^>^ vertices, int maxX, int amountOfLevels);
		void AddToLevel(int levelIndex, int vertexIndex, array<array<int>^>^ levels);
		void CalculatePositions(array<Vertex^>^ vertices);
		int NextNotMarked(int currentVertex, array<int>^ markedVertices, array<int>^ verticesOffsets);

		const int diameter = 30;
		String^ taskName;
		array<array<int>^>^ levels;
		array<int>^ correctMarkers;
		array<array<int>^>^ ways;
		array<array<int>^>^ matrix; // содержит матрицу смежности
		int size; // содержит количество вершин
	};
}
