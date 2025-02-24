#include <iostream>
#include <array>
#include "ConvertNexStar.h"
#include "AstroCalc.h"
using namespace std;
#using <System.dll>

using namespace System;
using namespace System::IO;
using namespace System::IO::Ports;
using namespace System::Threading;

#pragma once
ref class HandController
{
public:
	explicit HandController(System::String ^port);
	~HandController();
	void open();
	void close();
	void transmit(int length, cli::array<unsigned char> ^buffer);
	int receive(unsigned char * buffer);
	String^ sendAndReceive(String^ command);
	void setTime(int ind, bool check);
	void setLocation(String^ locTotal);
	void gotoAziAlt(double& azimuth, double& altitude, bool checkRaDec);
	void setAziAlt(String^ aziAlt, bool checkRaDec);
	void setRaDec(String^ raDec);
	void stepAziAlt(String^ step, int direction, bool trackCtrl);
	String^ setLmAlign(String^ lmAlign, bool refractionFlag);
	String^ calcRaDe(String^ timeStamp, String^ direction);
	String^ calcRefraction(String^ direction);
	void splitAngle(double angle, int& grd, int& min, int& sec);
	String^ outSplitAngleHour(double angleHour, double factor, bool degFlag);
	void setTracking(bool onOff);
	void setSlew(char dir, char dir2, char size);
	void saveDeTau(String^ name);
	void string2char(String^ strIn, char* buffer, int len);
	void sendSync(double& ra, double& de);


	bool flagSerial;
	SerialPort^ myPort;

	bool summerTime;
	int diffUtm;
	double locLong;
	double locLat;
	char lastDir;

	ConvertNexStar* convNS;
	AstroCalc* astroC;
};
