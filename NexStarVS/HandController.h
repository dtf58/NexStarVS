#include <iostream>
#include <array>
#include "ConvertNexStar.h"
using namespace std;
#using <System.dll>

using namespace System;
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
	void setTime(int diffUtm, bool summerTime);
	void setLocation(String^ locTotal);
	void splitAngle(double angle, int& grd, int& min, int& sec);
	void setTracking(bool onOff);


	bool flagSerial;
	SerialPort^ myPort;

	ConvertNexStar* convNS;
};
