#pragma once

namespace GraphsToStudy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ ShortestPathForm
	/// </summary>
	public ref class ShortestPathForm : public System::Windows::Forms::Form
	{
	public:
		ShortestPathForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		ShortestPathForm(String^ t, array<array<int>^>^ m, int s)
		{
			type = t;
			matrix = m;
			size = s;
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~ShortestPathForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;



	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1200, 700);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(1229, 12);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 50;
			this->dataGridView1->Size = System::Drawing::Size(240, 150);
			this->dataGridView1->TabIndex = 1;
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->ScrollBars = ScrollBars::None;
			this->dataGridView1->AllowUserToResizeColumns = false;
			this->dataGridView1->ReadOnly = true;
			// 
			// ShortestPathForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1800, 800);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"ShortestPathForm";
			this->Text = L"ShortestPathForm";
			this->Shown += gcnew System::EventHandler(this, &ShortestPathForm::onShown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		Void onShown(System::Object^ sender, System::EventArgs^ e);
		Void VisualizeGraph();
		Void VisualizeTables();

		int CalculateLevels();
		void AddToLevel(int levelIndex, int vertexIndex);
		bool IsInLevels(int vertexIndex, int curAmountOfLevels);
		void CalculatePositions(int amountOfLevels);

		ref struct Vertex
		{
			String^ Name;
			int X;
			int Y;
		};

		const int diameter = 30;
		array<array<int>^>^ levels; // содержит вершины каждого уровн€
		String^ type; // содержит тип задани€
		array<array<int>^>^ matrix; // содержит матрицу смежности
		int size; // содержит количество вершин
		array<Vertex^>^ vertices; // содержит координаты уже отрисованных вершин 
};
}
