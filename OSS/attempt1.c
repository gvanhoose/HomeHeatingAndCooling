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

int ossHeatLoop( struct loopdata* data, double sptHeat )
{
	double
		roomAirMass = data->roomAirMass,
		roomHeat = data->roomHeat,
		inletHeat = data->inletHeat,
		massFlow = data->massFlow,
		dH
		;

	int time = 0;

	while( roomHeat < SptHeat )
	{
		dH = inletHeat - (massFlow * roomHeat)/roomAirMass;
		roomHeat += dH;
		time++;
	}

	return time;
}
int ossCoolLoop( struct loopdata* data, double sptHeat )
{
	double
		roomAirMass = data->roomAirMass,
		roomHeat = data->roomHeat,
		inletHeat = data->inletHeat,
		massFlow = data->massFlow,
		dH
		;

	int time = 0;

	while( roomHeat > SptHeat )
	{
		dH = inletHeat - (massFlow * roomHeat)/roomAirMass;
		roomHeat += dH;
		time++;
	}

	return time;
}

int main()
{
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

	printf( "Elapsed time = %d seconds\n", elapsedSeconds );
	printf( "%d minutes, %d seconds\n", elapsedSeconds / 60, elapsedSeconds % 60 );


	return 0;
}
