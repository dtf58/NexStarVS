#pragma once
#include "HandController.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::IO::Ports;
	using namespace System::Threading;
	using namespace System::Xml;


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
	private: bool trackOn;
	private: bool locOk;
	private: bool timeOk;
	private: HandController^ hc;
	private: StreamWriter^ outLog;
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






	private: System::Windows::Forms::Label^ label4;




	private: System::Windows::Forms::Button^ setLoc;
	private: System::Windows::Forms::ComboBox^ listLocation;
	private: System::Windows::Forms::Button^ setTracking;
	private: System::Windows::Forms::Button^ openXml;
	private: System::Windows::Forms::ComboBox^ listLandmarkAligns;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ setLmAlign;
	private: System::Windows::Forms::Button^ SaveDeTau;
	private: System::Windows::Forms::TextBox^ testTimeStamp;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::ComboBox^ testDirections;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Button^ calcRaDe;
	private: System::Windows::Forms::Button^ calcRefr;
	private: System::Windows::Forms::CheckBox^ checkRefraction;
	private: System::Windows::Forms::TextBox^ aziAlt;
	private: System::Windows::Forms::Button^ setAziAlt;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ shiftStep;
	private: System::Windows::Forms::Button^ stepLeft;
	private: System::Windows::Forms::Button^ stepRight;
	private: System::Windows::Forms::Button^ stepUp;
	private: System::Windows::Forms::Button^ stepDown;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Button^ stepStop;
	private: System::Windows::Forms::TextBox^ RaDecAlign;
	private: System::Windows::Forms::Button^ alignRaDec;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::CheckBox^ raDecGoto;
	private: System::Windows::Forms::CheckBox^ TrackOffOn;



















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
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->setLoc = (gcnew System::Windows::Forms::Button());
			this->listLocation = (gcnew System::Windows::Forms::ComboBox());
			this->setTracking = (gcnew System::Windows::Forms::Button());
			this->openXml = (gcnew System::Windows::Forms::Button());
			this->listLandmarkAligns = (gcnew System::Windows::Forms::ComboBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->setLmAlign = (gcnew System::Windows::Forms::Button());
			this->SaveDeTau = (gcnew System::Windows::Forms::Button());
			this->testTimeStamp = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->testDirections = (gcnew System::Windows::Forms::ComboBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->calcRaDe = (gcnew System::Windows::Forms::Button());
			this->calcRefr = (gcnew System::Windows::Forms::Button());
			this->checkRefraction = (gcnew System::Windows::Forms::CheckBox());
			this->aziAlt = (gcnew System::Windows::Forms::TextBox());
			this->setAziAlt = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->shiftStep = (gcnew System::Windows::Forms::TextBox());
			this->stepLeft = (gcnew System::Windows::Forms::Button());
			this->stepRight = (gcnew System::Windows::Forms::Button());
			this->stepUp = (gcnew System::Windows::Forms::Button());
			this->stepDown = (gcnew System::Windows::Forms::Button());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->stepStop = (gcnew System::Windows::Forms::Button());
			this->RaDecAlign = (gcnew System::Windows::Forms::TextBox());
			this->alignRaDec = (gcnew System::Windows::Forms::Button());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->raDecGoto = (gcnew System::Windows::Forms::CheckBox());
			this->TrackOffOn = (gcnew System::Windows::Forms::CheckBox());
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
			this->OutputBox->Location = System::Drawing::Point(65, 984);
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
			this->Output->Location = System::Drawing::Point(65, 965);
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
			this->checkSummer->Size = System::Drawing::Size(104, 20);
			this->checkSummer->TabIndex = 8;
			this->checkSummer->Text = L"Summertime";
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
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(65, 282);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(233, 16);
			this->label4->TabIndex = 17;
			this->label4->Text = L"Location (Longitude E/W Latitude N/S)";
			// 
			// setLoc
			// 
			this->setLoc->Location = System::Drawing::Point(464, 303);
			this->setLoc->Name = L"setLoc";
			this->setLoc->Size = System::Drawing::Size(151, 23);
			this->setLoc->TabIndex = 20;
			this->setLoc->Text = L"Set Location";
			this->setLoc->UseVisualStyleBackColor = true;
			this->setLoc->Click += gcnew System::EventHandler(this, &Form1::setLoc_Click);
			// 
			// listLocation
			// 
			this->listLocation->FormattingEnabled = true;
			this->listLocation->Location = System::Drawing::Point(65, 303);
			this->listLocation->Name = L"listLocation";
			this->listLocation->Size = System::Drawing::Size(319, 24);
			this->listLocation->TabIndex = 21;
			// 
			// setTracking
			// 
			this->setTracking->Location = System::Drawing::Point(464, 354);
			this->setTracking->Name = L"setTracking";
			this->setTracking->Size = System::Drawing::Size(151, 23);
			this->setTracking->TabIndex = 22;
			this->setTracking->Text = L"Tracking On";
			this->setTracking->UseVisualStyleBackColor = true;
			this->setTracking->Click += gcnew System::EventHandler(this, &Form1::setTracking_Click);
			// 
			// openXml
			// 
			this->openXml->Location = System::Drawing::Point(493, 32);
			this->openXml->Name = L"openXml";
			this->openXml->Size = System::Drawing::Size(122, 23);
			this->openXml->TabIndex = 23;
			this->openXml->Text = L"Open XML";
			this->openXml->UseVisualStyleBackColor = true;
			this->openXml->Click += gcnew System::EventHandler(this, &Form1::openXml_Click);
			// 
			// listLandmarkAligns
			// 
			this->listLandmarkAligns->FormattingEnabled = true;
			this->listLandmarkAligns->Location = System::Drawing::Point(65, 404);
			this->listLandmarkAligns->Name = L"listLandmarkAligns";
			this->listLandmarkAligns->Size = System::Drawing::Size(319, 24);
			this->listLandmarkAligns->TabIndex = 24;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(71, 382);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(174, 16);
			this->label5->TabIndex = 25;
			this->label5->Text = L"Landmark Aligns (AZM ALT)";
			// 
			// setLmAlign
			// 
			this->setLmAlign->Location = System::Drawing::Point(464, 405);
			this->setLmAlign->Name = L"setLmAlign";
			this->setLmAlign->Size = System::Drawing::Size(151, 23);
			this->setLmAlign->TabIndex = 26;
			this->setLmAlign->Text = L"Set Align";
			this->setLmAlign->UseVisualStyleBackColor = true;
			this->setLmAlign->Click += gcnew System::EventHandler(this, &Form1::setLmAlign_Click);
			// 
			// SaveDeTau
			// 
			this->SaveDeTau->Location = System::Drawing::Point(732, 974);
			this->SaveDeTau->Name = L"SaveDeTau";
			this->SaveDeTau->Size = System::Drawing::Size(132, 23);
			this->SaveDeTau->TabIndex = 27;
			this->SaveDeTau->Text = L"Save Output";
			this->SaveDeTau->UseVisualStyleBackColor = true;
			this->SaveDeTau->Click += gcnew System::EventHandler(this, &Form1::SaveDeTau_Click);
			// 
			// testTimeStamp
			// 
			this->testTimeStamp->Location = System::Drawing::Point(68, 831);
			this->testTimeStamp->Name = L"testTimeStamp";
			this->testTimeStamp->Size = System::Drawing::Size(198, 22);
			this->testTimeStamp->TabIndex = 28;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(65, 809);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(110, 16);
			this->label6->TabIndex = 29;
			this->label6->Text = L"Test Time Stamp";
			// 
			// testDirections
			// 
			this->testDirections->FormattingEnabled = true;
			this->testDirections->Location = System::Drawing::Point(65, 897);
			this->testDirections->Name = L"testDirections";
			this->testDirections->Size = System::Drawing::Size(316, 24);
			this->testDirections->TabIndex = 30;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(65, 869);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(97, 16);
			this->label7->TabIndex = 31;
			this->label7->Text = L"Test Directions";
			// 
			// calcRaDe
			// 
			this->calcRaDe->Location = System::Drawing::Point(464, 897);
			this->calcRaDe->Name = L"calcRaDe";
			this->calcRaDe->Size = System::Drawing::Size(113, 23);
			this->calcRaDe->TabIndex = 32;
			this->calcRaDe->Text = L"Calc RA DE";
			this->calcRaDe->UseVisualStyleBackColor = true;
			this->calcRaDe->Click += gcnew System::EventHandler(this, &Form1::calcRaDe_Click);
			// 
			// calcRefr
			// 
			this->calcRefr->Location = System::Drawing::Point(464, 927);
			this->calcRefr->Name = L"calcRefr";
			this->calcRefr->Size = System::Drawing::Size(151, 23);
			this->calcRefr->TabIndex = 33;
			this->calcRefr->Text = L"Calc Refraction";
			this->calcRefr->UseVisualStyleBackColor = true;
			this->calcRefr->Click += gcnew System::EventHandler(this, &Form1::calcRefr_Click);
			// 
			// checkRefraction
			// 
			this->checkRefraction->AutoSize = true;
			this->checkRefraction->Location = System::Drawing::Point(74, 435);
			this->checkRefraction->Name = L"checkRefraction";
			this->checkRefraction->Size = System::Drawing::Size(118, 20);
			this->checkRefraction->TabIndex = 34;
			this->checkRefraction->Text = L"Use Refraction";
			this->checkRefraction->UseVisualStyleBackColor = true;
			// 
			// aziAlt
			// 
			this->aziAlt->Location = System::Drawing::Point(65, 587);
			this->aziAlt->Name = L"aziAlt";
			this->aziAlt->Size = System::Drawing::Size(319, 22);
			this->aziAlt->TabIndex = 35;
			// 
			// setAziAlt
			// 
			this->setAziAlt->Location = System::Drawing::Point(464, 586);
			this->setAziAlt->Name = L"setAziAlt";
			this->setAziAlt->Size = System::Drawing::Size(151, 23);
			this->setAziAlt->TabIndex = 36;
			this->setAziAlt->Text = L"Goto";
			this->setAziAlt->UseVisualStyleBackColor = true;
			this->setAziAlt->Click += gcnew System::EventHandler(this, &Form1::setAziAlt_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(72, 567);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(220, 16);
			this->label8->TabIndex = 37;
			this->label8->Text = L"Goto Azi Alt or RA DEC (d/hms dms)";
			// 
			// shiftStep
			// 
			this->shiftStep->Location = System::Drawing::Point(68, 714);
			this->shiftStep->Name = L"shiftStep";
			this->shiftStep->Size = System::Drawing::Size(100, 22);
			this->shiftStep->TabIndex = 38;
			// 
			// stepLeft
			// 
			this->stepLeft->Location = System::Drawing::Point(335, 712);
			this->stepLeft->Name = L"stepLeft";
			this->stepLeft->Size = System::Drawing::Size(75, 23);
			this->stepLeft->TabIndex = 39;
			this->stepLeft->Text = L"Left";
			this->stepLeft->UseVisualStyleBackColor = true;
			this->stepLeft->Click += gcnew System::EventHandler(this, &Form1::stepLeft_Click);
			// 
			// stepRight
			// 
			this->stepRight->Location = System::Drawing::Point(500, 714);
			this->stepRight->Name = L"stepRight";
			this->stepRight->Size = System::Drawing::Size(75, 23);
			this->stepRight->TabIndex = 40;
			this->stepRight->Text = L"Right";
			this->stepRight->UseVisualStyleBackColor = true;
			this->stepRight->Click += gcnew System::EventHandler(this, &Form1::stepRight_Click);
			// 
			// stepUp
			// 
			this->stepUp->Location = System::Drawing::Point(419, 672);
			this->stepUp->Name = L"stepUp";
			this->stepUp->Size = System::Drawing::Size(75, 23);
			this->stepUp->TabIndex = 41;
			this->stepUp->Text = L"Up";
			this->stepUp->UseVisualStyleBackColor = true;
			this->stepUp->Click += gcnew System::EventHandler(this, &Form1::stepUp_Click);
			// 
			// stepDown
			// 
			this->stepDown->Location = System::Drawing::Point(419, 746);
			this->stepDown->Name = L"stepDown";
			this->stepDown->Size = System::Drawing::Size(75, 23);
			this->stepDown->TabIndex = 42;
			this->stepDown->Text = L"Down";
			this->stepDown->UseVisualStyleBackColor = true;
			this->stepDown->Click += gcnew System::EventHandler(this, &Form1::stepDown_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(71, 678);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(175, 16);
			this->label9->TabIndex = 43;
			this->label9->Text = L"Teleskop Slew with Rate 1-9";
			// 
			// stepStop
			// 
			this->stepStop->Location = System::Drawing::Point(419, 713);
			this->stepStop->Name = L"stepStop";
			this->stepStop->Size = System::Drawing::Size(75, 23);
			this->stepStop->TabIndex = 44;
			this->stepStop->Text = L"Stop";
			this->stepStop->UseVisualStyleBackColor = true;
			this->stepStop->Click += gcnew System::EventHandler(this, &Form1::stepStop_Click);
			// 
			// RaDecAlign
			// 
			this->RaDecAlign->Location = System::Drawing::Point(65, 511);
			this->RaDecAlign->Name = L"RaDecAlign";
			this->RaDecAlign->Size = System::Drawing::Size(316, 22);
			this->RaDecAlign->TabIndex = 45;
			// 
			// alignRaDec
			// 
			this->alignRaDec->Location = System::Drawing::Point(464, 509);
			this->alignRaDec->Name = L"alignRaDec";
			this->alignRaDec->Size = System::Drawing::Size(151, 23);
			this->alignRaDec->TabIndex = 46;
			this->alignRaDec->Text = L"Set Ra/Dec Align";
			this->alignRaDec->UseVisualStyleBackColor = true;
			this->alignRaDec->Click += gcnew System::EventHandler(this, &Form1::alignRaDec_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(65, 489);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(183, 16);
			this->label10->TabIndex = 47;
			this->label10->Text = L"Ra/Dec 2000 Align (hms dms)";
			// 
			// raDecGoto
			// 
			this->raDecGoto->AutoSize = true;
			this->raDecGoto->Location = System::Drawing::Point(68, 627);
			this->raDecGoto->Name = L"raDecGoto";
			this->raDecGoto->Size = System::Drawing::Size(75, 20);
			this->raDecGoto->TabIndex = 48;
			this->raDecGoto->Text = L"Ra Dec";
			this->raDecGoto->UseVisualStyleBackColor = true;
			// 
			// TrackOffOn
			// 
			this->TrackOffOn->AutoSize = true;
			this->TrackOffOn->Location = System::Drawing::Point(68, 749);
			this->TrackOffOn->Name = L"TrackOffOn";
			this->TrackOffOn->Size = System::Drawing::Size(128, 20);
			this->TrackOffOn->TabIndex = 49;
			this->TrackOffOn->Text = L"Tracking Off - On";
			this->TrackOffOn->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1003, 1259);
			this->Controls->Add(this->TrackOffOn);
			this->Controls->Add(this->raDecGoto);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->alignRaDec);
			this->Controls->Add(this->RaDecAlign);
			this->Controls->Add(this->stepStop);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->stepDown);
			this->Controls->Add(this->stepUp);
			this->Controls->Add(this->stepRight);
			this->Controls->Add(this->stepLeft);
			this->Controls->Add(this->shiftStep);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->setAziAlt);
			this->Controls->Add(this->aziAlt);
			this->Controls->Add(this->checkRefraction);
			this->Controls->Add(this->calcRefr);
			this->Controls->Add(this->calcRaDe);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->testDirections);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->testTimeStamp);
			this->Controls->Add(this->SaveDeTau);
			this->Controls->Add(this->setLmAlign);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->listLandmarkAligns);
			this->Controls->Add(this->openXml);
			this->Controls->Add(this->setTracking);
			this->Controls->Add(this->listLocation);
			this->Controls->Add(this->setLoc);
			this->Controls->Add(this->label4);
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
    private: System::Void setTracking_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void openXml_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void setLmAlign_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void SaveDeTau_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void calcRaDe_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void calcRefr_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void setAziAlt_Click(System::Object^ sender, System::EventArgs^ e); 
    private: System::Void stepUp_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void stepLeft_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void stepRight_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void stepDown_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void stepStop_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void alignRaDec_Click(System::Object^ sender, System::EventArgs^ e);
};
}
