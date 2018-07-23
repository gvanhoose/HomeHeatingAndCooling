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
	int i, bufflen = readVPoint( "../VPoints/NextSetpoint.vpoint", nxsptbuff, 4 );

	double nxspt = 0.0;
	for( i = 0; i < 8; i++ )
	{
		nxspt *= 10.0;
		nxspt += nxsptbuff[i] & 0x0f;
	}
	return nxspt;
}

double sToD( char* s )
{
	double out = 0.0, factor = 0.1;
	int pointHit = 0, slen = strlen(s), i;
	for( i = 0; i < slen; i++ )
	{
		if( s[i] == '.' )
		{
			pointHit = 1;
			continue;
		}
		if( !pointHit )
		{
			out *= 10.0;
			out += s[i] & 0x0f;
		}
		if( pointHit )
		{
			out += (s[i] & 0x0f) * factor;
			factor /= 10.0;
		}
	}
	return out;
}

void getRoomData( struct loopdata* ld )
{
	char data [64];
	char* ram = data;
	char* mfr = data + 16;
	char* rsh = data + 32;
	char* ish = data + 48;

	memset( data, '\0', 64 );

	readVPoint( "../VPoints/RoomAirMass.vpoint", ram, 15 );
	readVPoint( "../VPoints/MassFlowRate.vpoint", mfr, 15 );
	readVPoint( "../VPoints/RoomSpecificHeat.vpoint", rsh, 15 );
	readVPoint( "../VPoints/InletSpecificHeat.vpoint", ish, 15 );

	int i;
	for( i = 0; i < 64; i++ )
	{
		data[i] = (data[i] < 0x2e )? '\0' : data[i];
	}

	double
		rmAirMass = sToD( ram ),
		massFlowRate = sToD( mfr ),
		rmSpecHeat = sToD( rsh ),
		inflowSpecHeat = sToD( ish )
		;

	setRoomHeat( ld, rmAirMass, rmSpecHeat );
	setInletHeat( ld, massFlowRate, inflowSpecHeat );

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
	writeToVPoint( "../VPoints/HeatCmd.vpoint", "0" );
}

int main()
{
	struct loopdata ld;
	getRoomData( &ld );

	printf( "ram = %lf\n", ld.roomAirMass );
	printf( "mfr = %lf\n", ld.massFlow );
	printf( "isp = %lf\n", ld.inletHeat );
	printf( "rht = %lf\n", ld.roomHeat );
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
	return 0;
}
