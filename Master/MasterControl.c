#include <stdio.h>
#include "../ValuePoint/ValuePoint.h"
#include "../Standards.h"

void FanCommand( int cmd )
{
	printf( "  Fan Command = %d\n", cmd );
}
void HeatCommand( int cmd )
{
	printf( "Heat Commmand = %d\n", cmd );
	FanCommand( cmd );
}
void CoolCommand( int cmd )
{
	printf( " Cool Command = %d\n", cmd );
	FanCommand( cmd );
}

char getCharVPoint( char* vp )
{
	char cv [2];
	readVPoint( vp, cv, 2 );

	return *cv;
}
int getIntVPoint( char* vp )
{
	char cv [32];
	int i, val = 0, cvlen = readVPoint( vp, cv, 32 ), posneg = (cv[0] == '-')? -1 : 1;

	char c;
	for( i = 0; i < cvlen; i++ )
	{
		c = cv[i];
		if( c < 0x30 || c > 0x39 )
		{
			continue;
		}
		val *= 10;
		val += c & 0x0f;
	}
	return val * posneg;
]
double getDoubleVPoint( char* vp )
{
	char cv [32];
	readVPoint( vp, cv, 32 );

	return sToD(cv);
}

int main()
{
	double
		nxSpt = getDoubleVPoint( "../VPoints/NextSetpoint.vpoint" ),
		clgEnaSpt = getDoubleVPoint( "../VPoints/CoolEnableSetpoint.vpoint" ),
		htgEnaSpt = getDoubleVPoint( "../VPoints/HeatEnableSetpoint.vpoint" ),
		oaTemp = getDoubleVPoint( "../VPoints/OutsideAirTemp.vpoint" )
		;
	int
		clgEna = getIntVPoint( "../VPoints/CoolEnable.vpoint" ),
		htgEna = getIntVPoint( "../VPoints/HeatEnable.vpoint" ),
		nxRm = getIntVPoint( "../VPoints/NextRoom.vpoint" ),
		ttNxSpt = getIntVPoint( "../VPoints/TimeToNextSetpoint.vpoint" ),
		ttTrans = getIntVPoint( "../VPoints/TimeToTranstion.vpoint" )
		;
	char curMode = getCharVPoint( "../VPoints/CurrentMode.vpoint" );

	printf( "Next setpoint = %lf\n", nxSpt );
	printf( "Cool enable setpoint = %lf\n"
