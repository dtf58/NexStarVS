#pragma once

class ConvertNexStar
{
public:
	ConvertNexStar();
	~ConvertNexStar();

	bool convertReceive(unsigned char c, unsigned char * recBuffer);
	double transAngle(unsigned char* raw);

	unsigned int firstVersion;
	unsigned int secondVersion;
	unsigned int trackMode;

	unsigned int hcHour;
	unsigned int hcMinutes;
	unsigned int hcSeconds;
	unsigned int hcMonth;
	unsigned int hcDay;
	unsigned int hcYear;
	unsigned int hcOffsetGMT;
	unsigned int hcSummerTime;

	double raCurrent;
	double decCurrent;

	double azmCurrent;
	double altCurrent;

	double latitudeCurrent;
	char hemisCurrent[2];
	double longitudeCurrent;
	char eastWestCurrent[2];

	bool alignmentStatus;

};

