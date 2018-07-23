#include <stdio.h>
#include "../ValuePoint/ValuePoint.h"
#include "../Standards.h"

double getOutsideAirTemp()
{
	// in the near future, this will be rewritten such that it reads from a network device
	return fToK(68.9);
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

int thermostat( double spt, double indiff, double temp, int prevOut, int reverse )
{
printf( "Thermostat:\n" );
printf( "spt = %lf\n" );
printf( "indiff = %lf\n" );
printf( "temp = %lf\n" );
printf( "prevOut = %lf\n" );

	if( temp > spt - indiff || temp < spt + indiff )
	{
printf("\tthermostat no change\n");
		return prevOut;
	}
printf("\tthermostat change\n");
	if( temp <= spt - indiff )
	{
		return reverse? 1 : 0;
	}
	if( temp >= spt + indiff )
	{
		return reverse? 0 : 1;
	}
	return -1;	// this should never execute
}

int main()
{
	double
		clgEnaSpt = getCoolEnableSetpoint(),
		heatEnaSpt = getHeatEnableSetpoint(),
		oaTemp = getOutsideAirTemp(),
		sptIndiff = 1.8
		;

	printf( "clgEnaSpt = %lf\n", clgEnaSpt );
	printf( "   oaTemp = %lf\n", oaTemp );
	printf( "sptIndiff = %lf\n", sptIndiff );

	int clgEna = thermostat( clgEnaSpt, sptIndiff, oaTemp, getCoolEna(), 0 );
	int heatEna = thermostat( heatEnaSpt, sptIndiff, oaTemp, getHeatEna(), 0 );

	char enastr [] = {'0', '\0'};

	enastr[0] |= clgEna;
	writeToVPoint( "../VPoints/CoolEnable.vpoint", enastr );

	enastr[0] &= 0xfe;
	enastr[0] |= heatEna;
	writeToVPoint( "../VPoints/HeatEnable.vpoint", enastr );


	printf( "Cool = %d\nHeat = %d\n", clgEna, heatEna );

	return 0;

}
