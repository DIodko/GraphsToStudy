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

	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1000, 500);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// ShortestPathForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1193, 815);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"ShortestPathForm";
			this->Text = L"ShortestPathForm";
			this->Shown += gcnew System::EventHandler(this, &ShortestPathForm::onShown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		private:
			Void onShown(System::Object^ sender, System::EventArgs^ e);
			Void VisualizeGraph(System::Object^ sender);

			int CalculateLevels();
			void AddToLevel(int levelIndex, int rootIndex);
			bool IsInLevels(int rootIndex, int curAmountOfLevels);
			void CalculatePositions(int amountOfLevels);

			ref struct Vertex
			{
				int X;
				int Y;
			};
			const int diameter = 50;
			array<array<int>^>^ levels; // содержит вершины каждого уровн€
			String^ type; // содержит тип задани€
			array<array<int>^>^ matrix; // содержит матрицу смежности
			int size; // содержит количество вершин
			array<Vertex^>^ vertices; // содержит координаты уже отрисованных вершин 
			Graphics^ graph; // сюда рисуетс€ граф
			Drawing::Font^ font;
			Pen^ pen;
			Brush^ brush;
	};
}
