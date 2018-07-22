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

void setRoomAirMass( struct loopdata*, double );
void setRoomHeat( struct loopdata*, double, double );
void setInletHeat( struct loopdata*, double, double );
void setMassFlow( struct loopdata*, double );
int ossHeatLoop( struct loopdata*, double );
int ossCoolLoop( struct loopdata*, double );
static int needsHeat( struct loopdata*, double );
static int needsCool( struct loopdata*, double );
