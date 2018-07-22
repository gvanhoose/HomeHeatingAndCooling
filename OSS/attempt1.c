#include <stdio.h>

struct loopdata
{
	double
		roomAirMass,
		roomHeat,
		inletHeat,
		massFlow
	;
};

void setRoomAirMass( struct loopdata* ld, double roomAirMass )
{
	ld->roomAirMass = roomAirMass;
}
void setRoomHeat( struct loopdata* ld, double roomAirMass, double roomSpHeat )
{
	ld->roomHeat = roomAirMass * roomSpHeat;
}
void setInletHeat( struct loopdata* ld, double massFlow, double inletSpHeat )
{
	ld->inletHeat = massFlow * inletSpHeat;
}
void setMassFlow( struct loopdata* ld, double massFlow )
{
	ld->massFlow = massFlow;
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
static int needsHeat( struct loopdata* dt, double sptSpHeat )
{
	return sptSpHeat*dt->roomAirMass > dt->roomHeat;
}
static int needsCool( struct loopdata* dt, double sptSpHeat )
{
	return sptSpHeat*dt->roomAirMass < dt->roomHeat;
}

int main()
{

	struct loopdata ld;

	double
		rmAirMass = 1.5,
		massFlow = 0.001,
		testSptSpHeat = 290.16,
		testRmSpHeat = 295.17,
		testInSpHeat = 285.14
		;


	setRoomAirMass( &ld, rmAirMass );
	setRoomHeat( &ld, rmAirMass, testRmSpHeat );
	setInletHeat( &ld, massFlow, testInSpHeat );
	setMassFlow( &ld, massFlow );

	if( needsHeat( &ld, testSptSpHeat ) )
	{
		printf( "heat required\n" );
		int t = ossHeatLoop( &ld, testSptSpHeat );
		printf( "time to heat:  %d seconds\n", t );

	}
	if( needsCool( &ld, testSptSpHeat ) )
	{
		printf( "cool required\n" );
		int t = ossCoolLoop( &ld, testSptSpHeat );
		printf( "time to cool:  %d seconds\n", t );
	}




//	double
//		roomAirMass = 1.5,
//		roomSpHeat = 298.18,
//		roomHeat = roomAirMass * roomSpHeat,
//		massFlow = 0.0001,
//		inletSpHeat = 285.14,
//		inletHeat = massFlow * inletSpHeat,
//		outletHeat,
//		SptSpHeat = 290.16,
//		SptHeat = SptSpHeat * roomAirMass,
//		dH
//		;
//
//	int i, elapsedSeconds = 0;
////	while( roomHeat < SptHeat )	// heating loop
//	while( roomHeat > SptHeat )
//	{
//		dH = inletHeat - (outletHeat = (massFlow * roomHeat)/roomAirMass);
////		printf( "%lf = %lf - (%lf = (%lf * %lf)/%lf)\n", dH, inletHeat, outletHeat, massFlow, roomHeat, roomAirMass );
//		roomHeat += dH;
////		printf( "%lf += %lf\n", roomHeat, dH );
//
//		elapsedSeconds++;
//	}
//
//	printf( "Elapsed time = %d seconds\n", elapsedSeconds );
//	printf( "%d minutes, %d seconds\n", elapsedSeconds / 60, elapsedSeconds % 60 );


	return 0;
}
