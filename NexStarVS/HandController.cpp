
#include "pch.h"
#include "HandController.h"
#if 0
#include <iostream>
using namespace std;
#using <System.dll>

using namespace System;
using namespace System::IO::Ports;
using namespace System::Threading;
#endif

#if 0
bool startSerial()
{
	bool flagSerial = true;
	SerialPort^myPort = gcnew SerialPort("COM5");
	myPort->BaudRate = 9600;
//	myPort->StopBits(1);
	try
	{
		myPort->Open();
	}
	catch (...)
	{
		flagSerial = false;
	}
	return flagSerial;
}


#else
HandController::HandController(System::String ^port)
{
	flagSerial = false;
	myPort = gcnew SerialPort(port, 9600, Parity::None, 8, StopBits::One );

}

HandController::~HandController()
{
	if (flagSerial)
	{
		flagSerial = false;
		myPort->Close();
	}
}

void HandController::open()
{
	flagSerial = true;
	try
	{
		myPort->Open();
	}
	catch (...)
	{
		flagSerial = false;
	}

}

void HandController::close()
{
	if (flagSerial)
	{
		flagSerial = false;
		myPort->Close();
	}
}

void HandController::transmit(int length, cli::array<unsigned char> ^buffer)
{
	if (flagSerial)
	{
		myPort->Write(buffer, 0, length);
	}
}

int HandController::receive(unsigned char* buffer)
{
	int count = 0;
	myPort->ReadTimeout = 2000;
	do
	{
		try
		{
 		    int val = myPort->ReadByte();
		    if (-1 == val)
			    break;
		    buffer[count] = (unsigned char)(val&0xff);
		    ++count;
		}
		catch (...)
		{
			break;
		}
	} while (1);
	return count;
}


#endif

