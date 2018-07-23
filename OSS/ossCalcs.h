#ifndef _OSSCALCS_H_
#define _OSSCALCS_H_

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
int needsHeat( struct loopdata*, double );
int needsCool( struct loopdata*, double );

#endif//_OSSCALCS_H_
