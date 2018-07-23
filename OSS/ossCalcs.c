#include "ossCalcs.h"

void setRoomHeat( struct loopdata* ld, double roomAirMass, double roomSpHeat )
{
	ld->roomAirMass = roomAirMass;
	ld->roomHeat = roomAirMass * roomSpHeat;
}
void setInletHeat( struct loopdata* ld, double massFlow, double inletSpHeat )
{
	ld->massFlow = massFlow;
	ld->inletHeat = massFlow * inletSpHeat;
}

int ossHeatLoop( struct loopdata* data, double sptSpHeat )
{
	double
		roomAirMass = data->roomAirMass,
		roomHeat = data->roomHeat,
		inletHeat = data->inletHeat,
		massFlow = data->massFlow,
		dH,
		sptHeat = roomAirMass * sptSpHeat
		;

	int time = 0;

	while( roomHeat < sptHeat )
	{
		dH = inletHeat - (massFlow * roomHeat)/roomAirMass;
		roomHeat += dH;
		time++;
	}

	return time;
}
int ossCoolLoop( struct loopdata* data, double sptSpHeat )
{
	double
		roomAirMass = data->roomAirMass,
		roomHeat = data->roomHeat,
		inletHeat = data->inletHeat,
		massFlow = data->massFlow,
		dH,
		sptHeat = roomAirMass * sptSpHeat
		;

	int time = 0;

	while( roomHeat > sptHeat )
	{
		dH = inletHeat - (massFlow * roomHeat)/roomAirMass;
		roomHeat += dH;
		time++;
	}

	return time;
}
int needsHeat( struct loopdata* dt, double sptSpHeat )
{
	return sptSpHeat*dt->roomAirMass > dt->roomHeat;
}
int needsCool( struct loopdata* dt, double sptSpHeat )
{
	return sptSpHeat*dt->roomAirMass < dt->roomHeat;
}

//int main()
//{
//
//	struct loopdata ld;
//
//	double
//		rmAirMass = 1.5,
//		massFlow = 0.001,
//		testSptSpHeat = 290.16,
//		testRmSpHeat = 295.17,
//		testInSpHeat = 285.14
//		;
//
//
//	setRoomAirMass( &ld, rmAirMass );
//	setRoomHeat( &ld, rmAirMass, testRmSpHeat );
//	setInletHeat( &ld, massFlow, testInSpHeat );
//	setMassFlow( &ld, massFlow );
//
//	if( needsHeat( &ld, testSptSpHeat ) )
//	{
//		printf( "heat required\n" );
//		int t = ossHeatLoop( &ld, testSptSpHeat );
//		printf( "time to heat:  %d seconds\n", t );
//
//	}
//	if( needsCool( &ld, testSptSpHeat ) )
//	{
//		printf( "cool required\n" );
//		int t = ossCoolLoop( &ld, testSptSpHeat );
//		printf( "time to cool:  %d seconds\n", t );
//	}
//
//	return 0;
//}
