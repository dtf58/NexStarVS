#include "pch.h"
#include "Form1.h"

namespace CppCLRWinFormsProject {

	Form1::Form1(void):
		hc(nullptr)
	{
		InitializeComponent();
		//
		//TODO: Add the constructor code here
		//
		for each (String ^ s in SerialPort::GetPortNames())
		{
			listComPorts->Items->Add(s);
		}
		listGetBox->Items->Add("e RA/DEC");
		listGetBox->Items->Add("z AZM-ALT");
		listGetBox->Items->Add("t Tracking Mode");
		listGetBox->Items->Add("w Location");
		listGetBox->Items->Add("h Time");
		listGetBox->Items->Add("V Version");

		buttonGet->Enabled = false;

	}

	Form1::~Form1()
	{
		if (components)
		{
			delete components;
		}
		if (nullptr != hc && hc->flagSerial)
		{
			hc->close();
		}
	}

    Void Form1::button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (nullptr == hc)
		{
			String^ port = listComPorts->SelectedItem->ToString();
			hc = gcnew HandController(port);
			hc->open();
			if (hc->flagSerial)
			{
				OutputBox->AppendText("Connection opened!\r\n");
				buttonGet->Enabled = true;
				button1->Text = "Disconnect";
			}
			else
			{
				OutputBox->AppendText("Connection error\r\n");
			}
		}
		else
		{
			hc->close();
			delete hc;
			hc = nullptr;
			button1->Text = "Connect";
			buttonGet->Enabled = false;
			OutputBox->AppendText("Connection closed!\r\n");
		}

    }

	Void Form1::OutputBox_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{

	}

    Void Form1::label1_Click(System::Object^ sender, System::EventArgs^ e) {
    }

	Void Form1::buttonGet_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (nullptr == hc)
		{
			OutputBox->AppendText("Connection is not established\r\n");
			return;
		}
		if (!hc->flagSerial)
		{
			OutputBox->AppendText("Connection is not established\r\n");
			return;
		}
		String^ command = listGetBox->SelectedItem->ToString();
		String^ receive = hc->sendAndReceive(command);
		OutputBox->AppendText(receive);

    }

}
