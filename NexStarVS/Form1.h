#pragma once
#include "HandController.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;
	using namespace System::Threading;


	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1();

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ OutputBox;

	private: HandController^ hc;
	private: System::Windows::Forms::ListBox^ listComPorts;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ Output;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->OutputBox = (gcnew System::Windows::Forms::TextBox());
			this->listComPorts = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Output = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(294, 32);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(96, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Connect";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// OutputBox
			// 
			this->OutputBox->Location = System::Drawing::Point(65, 148);
			this->OutputBox->Multiline = true;
			this->OutputBox->Name = L"OutputBox";
			this->OutputBox->Size = System::Drawing::Size(468, 212);
			this->OutputBox->TabIndex = 1;
			this->OutputBox->TextChanged += gcnew System::EventHandler(this, &Form1::OutputBox_TextChanged);
			// 
			// listComPorts
			// 
			this->listComPorts->FormattingEnabled = true;
			this->listComPorts->ItemHeight = 16;
			this->listComPorts->Location = System::Drawing::Point(65, 32);
			this->listComPorts->Name = L"listComPorts";
			this->listComPorts->ScrollAlwaysVisible = true;
			this->listComPorts->Size = System::Drawing::Size(192, 52);
			this->listComPorts->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(65, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(105, 16);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Select COM Port";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// Output
			// 
			this->Output->AutoSize = true;
			this->Output->Location = System::Drawing::Point(65, 126);
			this->Output->Name = L"Output";
			this->Output->Size = System::Drawing::Size(45, 16);
			this->Output->TabIndex = 4;
			this->Output->Text = L"Output";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(630, 406);
			this->Controls->Add(this->Output);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->listComPorts);
			this->Controls->Add(this->OutputBox);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"NexStar SLT Tool";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void OutputBox_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
