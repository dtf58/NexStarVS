#include "pch.h"
#include "ConvertNexStar.h"
#include <stdio.h>
#include <math.h>

ConvertNexStar::ConvertNexStar()
{
}

ConvertNexStar::~ConvertNexStar()
{

}

bool ConvertNexStar::convertReceive(unsigned char c, unsigned char * recBuffer)
{
	bool retVal = false;
	switch (c)
	{
	case 'V': firstVersion = (unsigned int)recBuffer[0];
		secondVersion = (unsigned  int)recBuffer[1];
		retVal = true;
		break;
	case 't': trackMode = (unsigned int)recBuffer[0];
		retVal = true;
		break;
	case 'h': hcHour = (unsigned int)recBuffer[0];
		hcMinutes = (unsigned int)recBuffer[1];
		hcSeconds = (unsigned int)recBuffer[2];
		hcMonth = (unsigned int)recBuffer[3];
		hcDay = (unsigned int)recBuffer[4];
		hcYear = (unsigned int)recBuffer[5] + 2000;
		hcOffsetGMT = (unsigned int)recBuffer[6];
		hcSummerTime = (unsigned int)recBuffer[7];
		retVal = true;
		break;
	case 'w': latitudeCurrent = (double)recBuffer[0] + (double)recBuffer[1]/60. + (double)recBuffer[2]/3600.;
		hemisCurrent[0] = 'N';
		hemisCurrent[1] = 0;
		if (recBuffer[3] == 1)
			hemisCurrent[0] = 'S';
		longitudeCurrent = (double)recBuffer[4] + (double)recBuffer[5] / 60. + (double)recBuffer[6] / 3600.;
		eastWestCurrent[0] = 'E';
		eastWestCurrent[1] = 0;
		if (recBuffer[7] == 1)
			eastWestCurrent[0] = 'W';
		retVal = true;
		break;
	case 'e': raCurrent = transAngle(&recBuffer[0]);
		decCurrent = transAngle(&recBuffer[9]);
		if (decCurrent > 180)
		{
			decCurrent -= 360.;
		}
		retVal = true;
		break;
	case 'z': azmCurrent = transAngle(&recBuffer[0]);
		altCurrent = transAngle(&recBuffer[9]);
		if (altCurrent > 180)
		{
			altCurrent -= 360.;
		}
		retVal = true;
		break;
	case 'J': alignmentStatus = false;
		if (recBuffer[0] == 1)
		{
			alignmentStatus = true;
		}
		retVal = true;
		break;
	};


	return retVal;
}

double ConvertNexStar::transAngle(unsigned char* raw)
{
	char buf[16];
	for (int i = 0; i < 8; ++i)
	{
		buf[i] = raw[i];
	}
	buf[8] = 0;
	unsigned int val=0;
	sscanf_s(buf, "%x", &val);

	return (double)val / 4294967296. * 360.;

}