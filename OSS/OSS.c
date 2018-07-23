#include <stdio.h>
#include "ossCalcs.h"
#include "ossVPoint.h"

int main()
{
	int tdeadline = transDeadline();
	printf( "Transition deadline:  %d seconds\n", tdeadline );

	int nxroom = nextRoom();
	printf( "          Next room: %d\n", nxroom );

	double nxstpt = nextSetpoint();
	printf( "      Next setpoint:  %lf degrees\n", nxstpt );

/*
	char nxrm [3] = {'0', '0', ((char)(nxroom + 0x30))};

	struct loopdata* ld;
	getRoomData( ld, nxrm );

	printf( "ram = %lf\n", ld->roomAirMass );
	printf( "mfr = %lf\n", ld->massFlow );
	printf( "isp = %lf\n", ld->inletHeat );
	printf( "rht = %lf\n", ld->roomHeat );
*/
	return 0;
}
