#pragma once

namespace DijkstraVisualization {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для ShortestPathForm
	/// </summary>
	public ref class DijkstraVisualizationForm : public System::Windows::Forms::Form
	{
	public:
		DijkstraVisualizationForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		DijkstraVisualizationForm(array<array<int>^>^ m, int s, array<array<int>^>^ w, array<int>^ cm)
		{
			ways = w;
			matrix = m;
			size = s;
			correctMarkers = cm;
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~DijkstraVisualizationForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Label^ label1;
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
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->checkSolutionButton = (gcnew System::Windows::Forms::Button());
			this->showSolutionButton = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1200, 720);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToResizeColumns = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(1218, 37);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersWidth = 50;
			this->dataGridView1->ShowRowErrors = false;
			this->dataGridView1->Size = System::Drawing::Size(240, 150);
			this->dataGridView1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Calibri", 14));
			this->label1->Location = System::Drawing::Point(1218, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(173, 23);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Матрица смежности";
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
			this->label2->Font = (gcnew System::Drawing::Font(L"Calibri", 14));
			this->label2->Location = System::Drawing::Point(1219, 344);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(81, 23);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Решение";
			// 
			// checkSolutionButton
			// 
			this->checkSolutionButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14));
			this->checkSolutionButton->Location = System::Drawing::Point(1218, 740);
			this->checkSolutionButton->Name = L"checkSolutionButton";
			this->checkSolutionButton->Size = System::Drawing::Size(120, 60);
			this->checkSolutionButton->TabIndex = 5;
			this->checkSolutionButton->Text = L"Проверить решение";
			this->checkSolutionButton->UseVisualStyleBackColor = true;
			this->checkSolutionButton->Click += gcnew System::EventHandler(this, &DijkstraVisualizationForm::CheckSolution);
			// 
			// showSolutionButton
			// 
			this->showSolutionButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14));
			this->showSolutionButton->Location = System::Drawing::Point(1372, 740);
			this->showSolutionButton->Name = L"showSolutionButton";
			this->showSolutionButton->Size = System::Drawing::Size(120, 60);
			this->showSolutionButton->TabIndex = 6;
			this->showSolutionButton->Text = L"Показать решение";
			this->showSolutionButton->UseMnemonic = false;
			this->showSolutionButton->UseVisualStyleBackColor = true;
			this->showSolutionButton->Click += gcnew System::EventHandler(this, &DijkstraVisualizationForm::ShowSolution);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(12, 750);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(500, 197);
			this->textBox1->TabIndex = 7;
			this->textBox1->Visible = false;
			// 
			// DijkstraVisualizationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1800, 959);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->showSolutionButton);
			this->Controls->Add(this->checkSolutionButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"DijkstraVisualizationForm";
			this->Text = L"ShortestPathForm";
			this->Shown += gcnew System::EventHandler(this, &DijkstraVisualizationForm::onShown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
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

		Void onShown(System::Object^ sender, System::EventArgs^ e);
		Void CheckSolution(System::Object^ sender, System::EventArgs^ e);
		Void ShowSolution(System::Object^ sender, System::EventArgs^ e);
		Void VisualizeGraph(array<Vertex^>^ vertices);
		Void VisualizeTables();

		void AddOffsetsBasedOnLevels(array<array<int>^>^ levels, array<Vertex^>^ vertices, int maxX, int amountOfLevels);
		void AddToLevel(int levelIndex, int vertexIndex, array<array<int>^>^ levels);
		void CalculatePositions(array<Vertex^>^ vertices);
		int NextNotMarked(int currentVertex, array<int>^ markedVertices, array<int>^ verticesOffsets);

		const int diameter = 30;
		array<int>^ correctMarkers;
		array<array<int>^>^ ways;
		array<array<int>^>^ matrix; // содержит матрицу смежности
		int size; // содержит количество вершин
	};
}
