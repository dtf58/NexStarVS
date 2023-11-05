#include <iostream>
#include <array>
using namespace std;
#using <System.dll>

using namespace System;
using namespace System::IO::Ports;
using namespace System::Threading;

#pragma once
#if 0
bool startSerial();


#else
ref class HandController
{
public:
	explicit HandController(System::String ^port);
	~HandController();
	void open();
	void close();
	void transmit(int length, cli::array<unsigned char> ^buffer);
	int receive(unsigned char * buffer);


	bool flagSerial;
	SerialPort^ myPort;
};
#endif
