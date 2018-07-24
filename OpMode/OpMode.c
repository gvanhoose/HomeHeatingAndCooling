#include <stdio.h>
#include "../ValuePoint/ValuePoint.h"
#include "../Standards.h"

double getOutsideAirTemp()
{
	char buff [16];
	readVPoint( "../VPoints/OutsideAirTemp.vpoint", buff, 16 );

	return fToK(sToD( buff ));
}

double getCoolEnableSetpoint()
{
	char buff [32];
	readVPoint( "../VPoints/CoolEnableSetpoint.vpoint", buff, 32 );

	return fToK(sToD( buff ));
}
double getHeatEnableSetpoint()
{
	char buff [32];
	readVPoint( "../VPoints/HeatEnableSetpoint.vpoint", buff, 32 );

	return fToK(sToD(buff));
}

int getCoolEna()
{
	char buff [4];
	readVPoint( "../VPoints/CoolEnable.vpoint", buff, 4 );

	return (int) (buff[0] & 0x1);
}
int getHeatEna()
{
	char buff [4];
	readVPoint( "../VPoints/HeatEnable.vpoint", buff, 4 );

	return (int) (buff[0] & 0x1);
}

int main( int argc, char** argv )
{
	double
		clgEnaSpt = getCoolEnableSetpoint(),
		heatEnaSpt = getHeatEnableSetpoint(),
		oaTemp = getOutsideAirTemp(),	// commented-out for testing only!
//		oaTemp = ((double)((argv[1][0] & 0x0F) * 10.0)) + ((double)(argv[1][1] & 0x0F)),
		sptIndiff = 1.0/1.8,
		loClgBound = clgEnaSpt - sptIndiff,
		hiClgBound = clgEnaSpt + sptIndiff,
		loHeatBound = heatEnaSpt - sptIndiff,
		hiHeatBound = heatEnaSpt + sptIndiff
		;

	oaTemp = fToK(oaTemp);

	int clgEna, heatEna,
		prevClgEna = getCoolEna(),
		prevHeatEna = getCoolEna()
		;

	if( oaTemp > loClgBound && oaTemp < hiClgBound )
	{
		clgEna = prevClgEna;
	}
	else if( oaTemp <= loClgBound )
	{
		clgEna = 0;
	}
	else if( oaTemp >= hiClgBound )
	{
		clgEna = 1;
	}

	if( oaTemp > loHeatBound && oaTemp < hiHeatBound )
	{
		heatEna = prevHeatEna;
	}
	else if( oaTemp <= loHeatBound )
	{
		heatEna = 1;
	}
	else if( oaTemp >= hiHeatBound )
	{
		heatEna = 0;
	}

	char enastr [] = {'0', '\0'};

	enastr[0] |= clgEna;
	writeToVPoint( "../VPoints/CoolEnable.vpoint", enastr );

	enastr[0] &= 0xfe;
	enastr[0] |= heatEna;
	writeToVPoint( "../VPoints/HeatEnable.vpoint", enastr );


//	printf( "Cool = %d\nHeat = %d\n", clgEna, heatEna );

	return 0;

}
