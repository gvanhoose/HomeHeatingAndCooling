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

void setRoomHeat( struct loopdata*, double, double );
void setInletHeat( struct loopdata*, double, double );
int ossHeatLoop( struct loopdata*, double );
int ossCoolLoop( struct loopdata*, double );
static int needsHeat( struct loopdata*, double );
static int needsCool( struct loopdata*, double );
