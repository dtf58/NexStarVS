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
	private: System::Windows::Forms::ListBox^ listGetBox;
	private: System::Windows::Forms::Button^ buttonGet;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::CheckBox^ checkSummer;
	private: System::Windows::Forms::ComboBox^ UtmDistance;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ SetTime;
	private: System::Windows::Forms::TextBox^ longitude;
	private: System::Windows::Forms::RadioButton^ longEast;
	private: System::Windows::Forms::RadioButton^ longWest;
	private: System::Windows::Forms::GroupBox^ EastWest;

	private: System::Windows::Forms::TextBox^ latitude;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::GroupBox^ Hemis;
	private: System::Windows::Forms::RadioButton^ latSouth;
	private: System::Windows::Forms::RadioButton^ latNorth;
	private: System::Windows::Forms::Button^ setLoc;





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
			this->listGetBox = (gcnew System::Windows::Forms::ListBox());
			this->buttonGet = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->checkSummer = (gcnew System::Windows::Forms::CheckBox());
			this->UtmDistance = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SetTime = (gcnew System::Windows::Forms::Button());
			this->longitude = (gcnew System::Windows::Forms::TextBox());
			this->longEast = (gcnew System::Windows::Forms::RadioButton());
			this->longWest = (gcnew System::Windows::Forms::RadioButton());
			this->EastWest = (gcnew System::Windows::Forms::GroupBox());
			this->latitude = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->Hemis = (gcnew System::Windows::Forms::GroupBox());
			this->latSouth = (gcnew System::Windows::Forms::RadioButton());
			this->latNorth = (gcnew System::Windows::Forms::RadioButton());
			this->setLoc = (gcnew System::Windows::Forms::Button());
			this->EastWest->SuspendLayout();
			this->Hemis->SuspendLayout();
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
			this->OutputBox->Location = System::Drawing::Point(65, 457);
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
			this->Output->Location = System::Drawing::Point(65, 438);
			this->Output->Name = L"Output";
			this->Output->Size = System::Drawing::Size(45, 16);
			this->Output->TabIndex = 4;
			this->Output->Text = L"Output";
			// 
			// listGetBox
			// 
			this->listGetBox->FormattingEnabled = true;
			this->listGetBox->ItemHeight = 16;
			this->listGetBox->Location = System::Drawing::Point(68, 131);
			this->listGetBox->Name = L"listGetBox";
			this->listGetBox->ScrollAlwaysVisible = true;
			this->listGetBox->Size = System::Drawing::Size(189, 84);
			this->listGetBox->TabIndex = 5;
			// 
			// buttonGet
			// 
			this->buttonGet->Location = System::Drawing::Point(294, 131);
			this->buttonGet->Name = L"buttonGet";
			this->buttonGet->Size = System::Drawing::Size(82, 23);
			this->buttonGet->TabIndex = 6;
			this->buttonGet->Text = L"Get";
			this->buttonGet->UseVisualStyleBackColor = true;
			this->buttonGet->Click += gcnew System::EventHandler(this, &Form1::buttonGet_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(68, 114);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(96, 16);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Get Information";
			// 
			// checkSummer
			// 
			this->checkSummer->AutoSize = true;
			this->checkSummer->Location = System::Drawing::Point(161, 245);
			this->checkSummer->Name = L"checkSummer";
			this->checkSummer->Size = System::Drawing::Size(105, 20);
			this->checkSummer->TabIndex = 8;
			this->checkSummer->Text = L"Sommertime";
			this->checkSummer->UseVisualStyleBackColor = true;
			// 
			// UtmDistance
			// 
			this->UtmDistance->FormattingEnabled = true;
			this->UtmDistance->Items->AddRange(gcnew cli::array< System::Object^  >(25) {
				L"-12", L"-11", L"-10", L"-9", L"-8", L"-7",
					L"-6", L"-5", L"-4", L"-3", L"-2", L"-1", L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10", L"11", L"12"
			});
			this->UtmDistance->Location = System::Drawing::Point(65, 245);
			this->UtmDistance->Name = L"UtmDistance";
			this->UtmDistance->Size = System::Drawing::Size(90, 24);
			this->UtmDistance->TabIndex = 9;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(65, 231);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(78, 16);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Zone UTM+";
			// 
			// SetTime
			// 
			this->SetTime->Location = System::Drawing::Point(294, 245);
			this->SetTime->Name = L"SetTime";
			this->SetTime->Size = System::Drawing::Size(96, 23);
			this->SetTime->TabIndex = 11;
			this->SetTime->Text = L"Set Time";
			this->SetTime->UseVisualStyleBackColor = true;
			this->SetTime->Click += gcnew System::EventHandler(this, &Form1::SetTime_Click);
			// 
			// longitude
			// 
			this->longitude->Location = System::Drawing::Point(65, 304);
			this->longitude->Name = L"longitude";
			this->longitude->Size = System::Drawing::Size(100, 22);
			this->longitude->TabIndex = 12;
			// 
			// longEast
			// 
			this->longEast->AutoSize = true;
			this->longEast->Location = System::Drawing::Point(12, 14);
			this->longEast->Name = L"longEast";
			this->longEast->Size = System::Drawing::Size(55, 20);
			this->longEast->TabIndex = 13;
			this->longEast->TabStop = true;
			this->longEast->Text = L"East";
			this->longEast->UseVisualStyleBackColor = true;
			// 
			// longWest
			// 
			this->longWest->AutoSize = true;
			this->longWest->Location = System::Drawing::Point(8, 40);
			this->longWest->Name = L"longWest";
			this->longWest->Size = System::Drawing::Size(59, 20);
			this->longWest->TabIndex = 14;
			this->longWest->TabStop = true;
			this->longWest->Text = L"West";
			this->longWest->UseVisualStyleBackColor = true;
			// 
			// EastWest
			// 
			this->EastWest->Controls->Add(this->longEast);
			this->EastWest->Controls->Add(this->longWest);
			this->EastWest->Location = System::Drawing::Point(190, 292);
			this->EastWest->Name = L"EastWest";
			this->EastWest->Size = System::Drawing::Size(94, 76);
			this->EastWest->TabIndex = 15;
			this->EastWest->TabStop = false;
			this->EastWest->Text = L" ";
			// 
			// latitude
			// 
			this->latitude->Location = System::Drawing::Point(306, 304);
			this->latitude->Name = L"latitude";
			this->latitude->Size = System::Drawing::Size(100, 22);
			this->latitude->TabIndex = 16;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(65, 282);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(66, 16);
			this->label4->TabIndex = 17;
			this->label4->Text = L"Longitude";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(306, 282);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(54, 16);
			this->label5->TabIndex = 18;
			this->label5->Text = L"Latitude";
			// 
			// Hemis
			// 
			this->Hemis->Controls->Add(this->latSouth);
			this->Hemis->Controls->Add(this->latNorth);
			this->Hemis->Location = System::Drawing::Point(413, 292);
			this->Hemis->Name = L"Hemis";
			this->Hemis->Size = System::Drawing::Size(92, 60);
			this->Hemis->TabIndex = 19;
			this->Hemis->TabStop = false;
			this->Hemis->Text = L" ";
			// 
			// latSouth
			// 
			this->latSouth->AutoSize = true;
			this->latSouth->Location = System::Drawing::Point(18, 40);
			this->latSouth->Name = L"latSouth";
			this->latSouth->Size = System::Drawing::Size(62, 20);
			this->latSouth->TabIndex = 1;
			this->latSouth->TabStop = true;
			this->latSouth->Text = L"South";
			this->latSouth->UseVisualStyleBackColor = true;
			// 
			// latNorth
			// 
			this->latNorth->AutoSize = true;
			this->latNorth->Location = System::Drawing::Point(18, 13);
			this->latNorth->Name = L"latNorth";
			this->latNorth->Size = System::Drawing::Size(60, 20);
			this->latNorth->TabIndex = 0;
			this->latNorth->TabStop = true;
			this->latNorth->Text = L"North";
			this->latNorth->UseVisualStyleBackColor = true;
			// 
			// setLoc
			// 
			this->setLoc->Location = System::Drawing::Point(557, 304);
			this->setLoc->Name = L"setLoc";
			this->setLoc->Size = System::Drawing::Size(151, 23);
			this->setLoc->TabIndex = 20;
			this->setLoc->Text = L"Set Location";
			this->setLoc->UseVisualStyleBackColor = true;
			this->setLoc->Click += gcnew System::EventHandler(this, &Form1::setLoc_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1003, 777);
			this->Controls->Add(this->setLoc);
			this->Controls->Add(this->Hemis);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->latitude);
			this->Controls->Add(this->EastWest);
			this->Controls->Add(this->longitude);
			this->Controls->Add(this->SetTime);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->UtmDistance);
			this->Controls->Add(this->checkSummer);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->buttonGet);
			this->Controls->Add(this->listGetBox);
			this->Controls->Add(this->Output);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->listComPorts);
			this->Controls->Add(this->OutputBox);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"NexStar SLT Tool";
			this->EastWest->ResumeLayout(false);
			this->EastWest->PerformLayout();
			this->Hemis->ResumeLayout(false);
			this->Hemis->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void OutputBox_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonGet_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void SetTime_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void setLoc_Click(System::Object^ sender, System::EventArgs^ e);
};
}
