#include <stdio.h>
#include "ossCalcs.h"
#include "ossVPoint.h"

int main()
{
	int tdeadline = transDeadline();
	int nxroom = nextRoom();
	double nxstpt = nextSetpoint();

	char nxrm [4] = {'0', '0', ((char)(nxroom + 0x30)), '\0'};

	struct loopdata ld;

	getRoomData( &ld, nxrm );

	printf( "ram = %lf\n", ld.roomAirMass );
	printf( "mfr = %lf\n", ld.massFlow );
	printf( "isp = %lf\n", ld.inletHeat );
	printf( "rht = %lf\n", ld.roomHeat );

	double time;
	if( needsHeat( &ld, nxstpt ) )
	{
		printf( "Needs Heating\n" );
	}
	if( needsCool( &ld, nxstpt ) )
	{
		printf( "Needs Cooling\n" );
	}



	return 0;
}
