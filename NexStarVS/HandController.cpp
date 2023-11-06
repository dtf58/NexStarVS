
#include "pch.h"
#include "HandController.h"

HandController::HandController(System::String ^port):
	flagSerial(false)
{
	myPort = gcnew SerialPort(port, 9600, Parity::None, 8, StopBits::One );
	convNS = new ConvertNexStar();
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

String^ HandController::sendAndReceive(String^ command)
{
		cli::array<unsigned char>^ sb = gcnew cli::array<unsigned char>(32);
		sb[0] = (unsigned char)command[0];
		transmit(1, sb);
		unsigned char eb[32];
		int length = receive(eb);

		String^ strReturn = gcnew String("");

		if (convNS->convertReceive(sb[0], eb))
		{
			switch (sb[0])
			{
			case 'V': strReturn = String::Format("Version: {0}.{1}\r\n", convNS->firstVersion, convNS->secondVersion);
				break;
			case 'h': strReturn = String::Format("HC DateTime: {0,4:0000}-{1,2:00}-{2,2:00} {3,2:00}:{4,2:00}:{5,2:00} GMT+{6} SummerTime:{7}\r\n",
				convNS->hcYear, convNS->hcMonth, convNS->hcDay, convNS->hcHour, convNS->hcMinutes, convNS->hcSeconds, convNS->hcOffsetGMT, convNS->hcSummerTime);
				break;
			}

		}
		else
		{
			strReturn = String::Format("Answer: {0} Bytes\r\n", length);
		}
		return strReturn;
	}
