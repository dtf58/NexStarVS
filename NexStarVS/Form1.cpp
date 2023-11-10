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
		listGetBox->Items->Add("J Alignment");
		listGetBox->Items->Add("V Version");

		buttonGet->Enabled = false;
		SetTime->Enabled = false;
		setLoc->Enabled = false;
		setTracking->Enabled = false;
		trackOn = true;
		UtmDistance->SelectedIndex = 13;
		listLocation->SelectedIndex = 0;

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
				SetTime->Enabled = true;
				setLoc->Enabled = true;
				setTracking->Enabled = true;
				setTracking->Text = "Tracking On";
				trackOn = true;
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
			SetTime->Enabled = false;
			setLoc->Enabled = false;
			setTracking->Enabled = false;
			trackOn = false;

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
	Void Form1::SetTime_Click(System::Object^ sender, System::EventArgs^ e)
	{
		int ind = UtmDistance->SelectedIndex -12;
		if (ind < 0)
		{
			ind = 256 - ind;
		}
		bool check = checkSummer->Checked;
		hc->setTime(ind, check);
	}
	Void Form1::setLoc_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ locTotal = listLocation->Text;
		hc->setLocation(locTotal);
	}

	Void Form1::setTracking_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (trackOn)
		{
			hc->setTracking(trackOn);
			setTracking->Text = "Tracking Off";
			trackOn = false;

		}
		else
		{
			hc->setTracking(trackOn);
			setTracking->Text = "Tracking On";
			trackOn = true;
		}
	}


    Void Form1::openXml_Click(System::Object^ sender, System::EventArgs^ e) 
	{

		OpenFileDialog^ ofd = gcnew OpenFileDialog();

		ofd->Filter = "All Files (*.*)|*.*| xml files (*.xml)|*.xml";
		ofd->FilterIndex = 2;

		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ Filename = ofd->FileName;
			XmlDocument^ xmlDoc = gcnew XmlDocument();
			try
			{
				xmlDoc->Load(Filename);
				XmlNodeList^ items = xmlDoc->GetElementsByTagName("Location");
				long num = items->Count;
				XmlNode^ item = items->Item(0);
				double longitude = Convert::ToDouble(item->Attributes->GetNamedItem("longitude")->Value);
				char side = Convert::ToChar(item->Attributes->GetNamedItem("side")->Value);
				double latitude = Convert::ToDouble(item->Attributes->GetNamedItem("latitude")->Value);
				char hemis = Convert::ToChar(item->Attributes->GetNamedItem("hemis")->Value);
			}
			catch (...)
			{

			}
		}
    }

}
