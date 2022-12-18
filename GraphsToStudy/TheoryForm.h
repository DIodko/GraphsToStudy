#pragma once

namespace GraphsToStudy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для TheoryForm
	/// </summary>
	public ref class TheoryForm : public System::Windows::Forms::Form
	{
	public:
		TheoryForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

		TheoryForm(String^ _taskName)
		{
			taskName = _taskName;
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~TheoryForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::ComboBox^ comboBox1;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());

			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(50, 70);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(600, 500);
			this->textBox1->TabIndex = 7;
			this->textBox1->ScrollBars = ScrollBars::Vertical;
			this->textBox1->Visible = true;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(700, 70);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(600, 500);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->SizeMode = PictureBoxSizeMode::AutoSize;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(520, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(332, 23);
			this->label1->TabIndex = 3;
			this->label1->Text = "Теория для задания";
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) {
				L"Поиск величины кратчайшего пути с помощью алгоритма Дейкстры",
					L"Определение уровней графа с помощью алгоритма Демукрона"
			});
			this->comboBox1->Location = System::Drawing::Point(720, 20);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(582, 31);
			this->comboBox1->DropDownStyle = ComboBoxStyle::DropDownList;
			this->comboBox1->TabIndex = 4;
			this->comboBox1->Text = taskName;
			this->comboBox1->SelectionChangeCommitted += gcnew System::EventHandler(this, &TheoryForm::onSelectionChanged);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(800, 600);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(150, 60);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Выход к главному меню";
			this->button1->BackColor = System::Drawing::Color::White;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &TheoryForm::onCloseButtonClick);
			//
			// form
			//
			this->BackColor = System::Drawing::Color::FromArgb(179, 229, 252);
			this->components = gcnew System::ComponentModel::Container();
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Size = System::Drawing::Size(1800, 750);
			this->Text = L"Теоретическая информация";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Shown += gcnew System::EventHandler(this, &TheoryForm::onShown);
		}
#pragma endregion
		Void onShown(System::Object^ sender, System::EventArgs^ e); // при вызове формы вызывает все остальные функции для вывода
		Void onCloseButtonClick(System::Object^ sender, System::EventArgs^ e);
		Void onSelectionChanged(System::Object^ sender, System::EventArgs^ e);

		String^ taskName;
	};
}
