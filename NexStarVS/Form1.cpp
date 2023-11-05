#include "pch.h"
#include "Form1.h"

namespace CppCLRWinFormsProject {

	Form1::Form1(void)
	{
		InitializeComponent();
		//
		//TODO: Add the constructor code here
		//
		for each (String ^ s in SerialPort::GetPortNames())
		{
			listComPorts->Items->Add(s);
		}
	}

	Form1::~Form1()
	{
		if (components)
		{
			delete components;
		}
	}

    Void Form1::button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		String ^port = listComPorts->SelectedItem->ToString();
	    hc = gcnew HandController(port);
	    hc->open();
	    if (hc->flagSerial)
		    OutputBox->AppendText("Hallo Welt!\r\n");
	    else
		    OutputBox->AppendText("Scheisse\r\n");

     	cli::array<unsigned char>^ sb = gcnew cli::array<unsigned char>(32);
	    sb[0] = 'V';
	    hc->transmit(1, sb);
	    unsigned char eb[32];
	    int length = hc->receive(eb);

	    OutputBox->AppendText(String::Format("Length: {0}\r\n", length));
		String^ version = String::Format("Version: {0}.{1}\r\n", eb[0], eb[1]);
		OutputBox->AppendText(version);
    }

	Void Form1::OutputBox_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{

	}

    Void Form1::label1_Click(System::Object^ sender, System::EventArgs^ e) {
    }


}
