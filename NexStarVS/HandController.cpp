
#include "pch.h"
#include "HandController.h"
#include <ctime>

HandController::HandController(System::String ^port):
	flagSerial(false)
{
	myPort = gcnew SerialPort(port, 9600, Parity::None, 8, StopBits::One );
	convNS = new ConvertNexStar();
	astroC = new AstroCalc();
	summerTime = false,
	diffUtm = 0;
}

HandController::~HandController()
{
	if (flagSerial)
	{
		flagSerial = false;
		myPort->Close();
	}
	delete convNS;
	delete astroC;
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
		cli::array<unsigned char>^ sb = gcnew cli::array<unsigned char>(8);
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
			case 't': strReturn = String::Format("Trackmode: {0}\r\n", convNS->trackMode);
				break;
			case 'h': strReturn = String::Format("HC DateTime: {0,4:0000}-{1,2:00}-{2,2:00} {3,2:00}:{4,2:00}:{5,2:00} GMT+{6} SummerTime:{7}\r\n",
				convNS->hcYear, convNS->hcMonth, convNS->hcDay, convNS->hcHour, convNS->hcMinutes, convNS->hcSeconds, convNS->hcOffsetGMT, convNS->hcSummerTime);
				break;
			case 'e': strReturn = String::Format("RA, DEC: {0,10:F4}, {1,10:F4}\r\n", convNS->raCurrent, convNS->decCurrent);
				break;
			case 'z': strReturn = String::Format("AZM, ALT: {0,10:F4}, {1,10:F4}\r\n", convNS->azmCurrent, convNS->altCurrent);
				break;
			case 'J': if (convNS->alignmentStatus)
			    {
				    strReturn = String::Format("Alignment: aligned\r\n");
			    }
				else
			    {
				    strReturn = String::Format("Alignment: not aligned\r\n");
			    }
				break;
			case 'w': String ^ strHem = gcnew String(convNS->hemisCurrent);
				String^ strEw = gcnew String(convNS->eastWestCurrent);
				strReturn = String::Format("Location Long: {0,12:F5} {1}      Lat: {2,12:F5} {3}\r\n", 
				convNS->longitudeCurrent, strHem, convNS->latitudeCurrent, strEw);
				break;
			}

		}
		else
		{
			strReturn = String::Format("Answer: {0} Bytes\r\n", length);
		}
		return strReturn;
	}

void  HandController::setTime(int ind, bool check)
{
	struct tm zeit;
	__time64_t sec;

	_time64(&sec);
	_localtime64_s(&zeit,&sec);

	cli::array<unsigned char>^ sb = gcnew cli::array<unsigned char>(32);
	sb[0] = 'H';
	sb[1] = (unsigned char)(zeit.tm_hour & 0xff);
	sb[2] = (unsigned char)(zeit.tm_min & 0xff);
	sb[3] = (unsigned char)(zeit.tm_sec & 0xff);
	sb[4] = (unsigned char)((zeit.tm_mon+1) & 0xff);
	sb[5] = (unsigned char)(zeit.tm_mday & 0xff);
	sb[6] = (unsigned char)((zeit.tm_year - 100) & 0xff);

	diffUtm = ind;
	int help = ind;
	if (ind < 0)
	{
		help = 256 + ind;
	}
	summerTime = check;
	sb[7] = (unsigned char)help;
	sb[8] = 0;
	if (summerTime)
	{
		sb[8] = 1;
	}

	transmit(9, sb);
	unsigned char eb[32];
	int length = receive(eb);
	
}

void HandController::splitAngle(double angle, int& grd, int& min, int& sec)
{
	grd = (int)angle;
	double h = angle - (double)grd;
	h *= 60.;
	min = (int)h;
	h = h - (double)min;
	h = h * 60. + 0.5;
	sec = (int)h;
}

void HandController::setLocation(String^ locTotal)
{
	cli::array<wchar_t>^ sep = { ' ',';' };
	cli::array<String^>^ subs = locTotal->Split(sep, StringSplitOptions::RemoveEmptyEntries);

	cli::array<unsigned char>^ sb = gcnew cli::array<unsigned char>(32);
	sb[0] = 'W';
	sb[4] = 0;
	sb[8] = 0;

	locLat = Convert::ToDouble(subs[2]);
	int grd, min, sec;
	splitAngle(locLat, grd, min, sec);
	sb[1] = (unsigned char)grd;
	sb[2] = (unsigned char)min;
	sb[3] = (unsigned char)sec;

	if (subs[3] == "S")
	{
		sb[4] = 1;
		locLat = -locLat;
	}

	locLong = Convert::ToDouble(subs[0]);
	splitAngle(locLong, grd, min, sec);
	sb[5] = (unsigned char)grd;
	sb[6] = (unsigned char)min;
	sb[7] = (unsigned char)sec;

	if (subs[0] == "W")
	{
		sb[8] = 1;
		locLong = -locLong;
	}
	transmit(9, sb);
	unsigned char eb[32];
	int length = receive(eb);
}

void HandController::setTracking(bool onOff)
{
	cli::array<unsigned char>^ sb = gcnew cli::array<unsigned char>(8);
	sb[0] = 'T';
	sb[1] = 0;
	if (onOff)
	{
		sb[1] = 1;
	}
	transmit(2, sb);
	unsigned char eb[32];
	int length = receive(eb);

}

String^ HandController::outSplitAngleHour(double angleHour, double factor, bool degFlag)
{
	double haf = angleHour * factor;
	int sign = 1;
	if (haf < 0)
	{
		haf = -haf;
		sign = -1;
	}
	int ha, min, sec;
	splitAngle(haf, ha, min, sec);
	char c = 'h';
	if (degFlag)
	{
		c = 'd';
	}
	char buffer[64];
	sprintf_s(buffer, sizeof(buffer), "%4d%c%02dm%02ds", ha * sign, c, min, sec);

	return gcnew String(buffer);
}

String^ HandController::setLmAlign(String^ lmAlign)
{
	cli::array<wchar_t>^ sep = { ' ',';' };
	cli::array<String^>^ subs = lmAlign->Split(sep, StringSplitOptions::RemoveEmptyEntries);

	double azimuth = Convert::ToDouble(subs[0]);
	double altitude = Convert::ToDouble(subs[1]);

	double ra;
	double de;
	double tau;
	double sidloc;

	astroC->azAlt2RaDec(azimuth, altitude, locLong, locLat, diffUtm, summerTime, ra, de, sidloc, tau);

	String^ strReturn = gcnew String("");

	strReturn = String::Format("RA: {0}   DE: {1}\r\nTau: {2}  LocSidTime: {3}\r\n",
		outSplitAngleHour(ra, 12. / 180., false), outSplitAngleHour(de, 1., true), outSplitAngleHour(tau, 12. / PI, false), outSplitAngleHour(sidloc, 12. / PI, false));

	if (de < 0.)
	{
		de += 360;
	}

	unsigned long raL =(unsigned long) (ra / 360. * 4294967296. + 0.5);
	unsigned long deL =(unsigned long) (de / 360. * 4294967296. + 0.5);

	char helpBuf[32];
	sprintf_s(helpBuf, sizeof(helpBuf), "s%08x,%08x", raL, deL);

	cli::array<unsigned char>^ sb = gcnew cli::array<unsigned char>(32);
	int num = 0;
	for (;;)
	{
		if (helpBuf[num] == 0)
			break;
		sb[num] = helpBuf[num];
		++num;
	}

	transmit(num, sb);
	unsigned char eb[32];
	int length = receive(eb);

	return strReturn;
}

void HandController::saveDeTau(String^ name)
{
	double latitude = 50.8887;

	double azimuth = 0.;
	double altitude = 1.;
	double de, de2, tau, tau0, tau1, tau2;

	StreamWriter^ sw = gcnew StreamWriter(name);

	for (int i = 0; i < 36; ++i)
	{
		altitude = 1.;
		for (int j = 0; j < 9; ++j)
		{
			astroC->azAlt2DeTau(azimuth * DEG2RAD, altitude * DEG2RAD, latitude * DEG2RAD, de, tau);
			astroC->azAlt2DeTau(azimuth * DEG2RAD, altitude * DEG2RAD, latitude * DEG2RAD, de2, tau0, tau1, tau2);

			char buffer[256];

			sprintf_s(buffer, sizeof(buffer),  "%8.1f; %8.1f; %12.5f; %12.5f; %12.5f; %12.5f; %12.5f; %12.5f\n",
				azimuth, altitude, de * RAD2DEG, tau / PI * 12., de2 * RAD2DEG, tau0 / PI * 12., tau1 / PI * 12., tau2 / PI * 12.);

			String^ outStr = gcnew String(buffer);

			sw->Write(outStr);
			altitude += 10.;

		}
		azimuth += 10.;
	}

	sw->Write(name);

	sw->Close();

}

String^ HandController::calcRaDe(String^ timeStamp, String^ direction)
{
	double ra;
	double de;
	double tau;
	double sidloc;
	char timeStampS[32];
	char directionS[64];

	int length = timeStamp->Length;
	if (length > 31)
		length = 31;
	int i;
	for (i = 0; i < length; ++i)
	{
		timeStampS[i] = (char)timeStamp[i];
	}
	timeStampS[i] = 0;
	length = direction->Length;
	if (length > 63)
		length = 63;
	for (i = 0; i < length; ++i)
	{
		directionS[i] = (char)direction[i];
	}
	directionS[i] = 0;


	astroC->calcRaDec(timeStampS, directionS, locLong, locLat, diffUtm, summerTime, ra, de, sidloc, tau);

	String^ strReturn = gcnew String("");

	strReturn = String::Format("RA: {0}   DE: {1}\r\nTau: {2}  LocSidTime: {3}\r\n",
		outSplitAngleHour(ra, 12. / 180., false), outSplitAngleHour(de, 1., true), outSplitAngleHour(tau, 12. / PI, false), outSplitAngleHour(sidloc, 12. / PI, false));

	return strReturn;
}

