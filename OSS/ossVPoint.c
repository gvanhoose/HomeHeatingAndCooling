#include "ossVPoint.h"

int transDeadline()
{
	char tttbuff [32];
	memset( tttbuff, '\0', 32 );

	int bufflen = readVPoint( /*TIME_TO_TRANSITION*/"../VPoints/TimeToTransition.vpoint", tttbuff, 32 );

	switch( bufflen )
	{
		case 0: return -1;
		case 1: return *tttbuff & 0x0f;
		case 2:	return (*tttbuff & 0x0f)*10 + *tttbuff & 0x0f;
	}

	int i, value = 0;
	for( i = 0; i < bufflen; i++ )
	{
		value *= 10;
		value += tttbuff[i] & 0x0f;
	}
	return value;
}
int heatEnabled()
{
	char ena [] = {'\0','\0'};

	readVPoint( "../VPoints/HeatEnable.vpoint", ena, 2 );

	return *ena & 0x1;
}
int coolEnabled()
{
	char ena [] = {'\0','\0'};

	readVPoint( "../VPoints/CoolEnable.vpoint", ena, 2 );

	return *ena & 0x1;
}
int econEnabled()
{
	char ena [] = {'\0','\0'};

	readVPoint( "../VPoints/EconEnable.vpoint", ena, 2 );

	return *ena & 0x1;
}

double nextSetpoint()
{
	char nxsptbuff [8];
	int i, bufflen = readVPoint( "../VPooints/NextSetpoint.vpoint", nxsptbuff, 4 );

	double nxspt = 0.0;
	for( i = 0; i < 8; i++ )
	{
		nxspt *= 10.0;
		nxspt += nxptbuff[i] & 0x0f;
	}
	return nxspt;
}

void coolStart()
{
	writeToVPoint( "../VPoints/FanCmd.vpoint",  "0" );
	writeToVPoint( "../VPoints/CoolCmd.vpoint", "1" );
	writeToVPoint( "../VPoints/HeatCmd.vpoint", "0" );
}
void heatStart()
{
	writeToVPoint( "../VPoints/FanCmd.vpoint",  "1" );
	writeToVPoint( "../VPoints/CoolCmd.vpoint", "0" );
	writeToVPoint( "../VPoints/HeatCmd.vpoint", "1" );
}
void econStart()
{
	writeToVPoint( "../VPoints/FanCmd.vpoint",  "1" );
	writeToVPoint( "../VPoints/CoolCmd.vpoint", "0" );
	writeToVpoint( "../VPoints/HeatCmd.vpoint", "0" );
}
//int main()
//{
//	int ttt = transDeadline();
//	printf( "Time to next transition:  %d seconds\n", ttt );
//
//	int
//		hena = heatEnabled(),
//		cena = coolEnabled(),
//		eena = econEnabled()
//		;
//
//	printf( "heat, cool, econ flags:  %d, %d, %d\n", hena, cena, eena );
//
//
//	return 0;
//}
