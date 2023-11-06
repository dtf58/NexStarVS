#pragma once

class ConvertNexStar
{
public:
	ConvertNexStar();
	~ConvertNexStar();

	bool convertReceive(unsigned char c, unsigned char * recBuffer);

	unsigned int firstVersion;
	unsigned int secondVersion;

	unsigned int hcHour;
	unsigned int hcMinutes;
	unsigned int hcSeconds;
	unsigned int hcMonth;
	unsigned int hcDay;
	unsigned int hcYear;
	unsigned int hcOffsetGMT;
	unsigned int hcSummerTime;
};

