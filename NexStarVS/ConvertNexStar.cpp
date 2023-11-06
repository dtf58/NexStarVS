#include "pch.h"
#include "ConvertNexStar.h"

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
	case 'h': hcHour = (unsigned int)recBuffer[0];
		      hcMinutes = (unsigned int)recBuffer[1];
		      hcSeconds = (unsigned int)recBuffer[2];
		      hcMonth = (unsigned int)recBuffer[3];
		      hcDay = (unsigned int)recBuffer[4];
		      hcYear = (unsigned int)recBuffer[5]+2000;
		      hcOffsetGMT = (unsigned int)recBuffer[6];
		      hcSummerTime = (unsigned int)recBuffer[7];
			  retVal = true;
			  break;

	};


	return retVal;
}
