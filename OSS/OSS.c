#include <stdio.h>
#include "ossCalcs.h"
#include "ossVPoint.h"

int main()
{
	int tdeadline = transDeadline();
	int nxroom = nextRoom();
	double nxstpt = fToK( nextSetpoint() );
	double stptSpHeat = estimateSpHeat( nxstpt );

	char nxrm [4] = {'0', '0', ((char)(nxroom + 0x30)), '\0'};

	struct loopdata ld;
	getRoomData( &ld, nxrm );

	printf( "ram = %lf\n", ld.roomAirMass );
	printf( "mfr = %lf\n", ld.massFlow );
	printf( "isp = %lf\n", ld.inletHeat );
	printf( "rht = %lf\n\n", ld.roomHeat );

	printf( "Next zone is room %d\n", nxroom );
	printf( "  Next setpoint = %lf\n", nxstpt );
	printf( "               in %d seconds\n", tdeadline );
	printf( "  setpoint heat = %lf\n", stptSpHeat );

	int time = -1;
	char* horc;
	if( needsHeat( &ld, nxstpt ) )
	{
		horc = "heat";
		time = ossHeatLoop( &ld, stptSpHeat );
	}
	if( needsCool( &ld, nxstpt ) )
	{
		horc = "cool";
		time = ossCoolLoop( &ld, stptSpHeat );
	}

	printf( "It will take %d seconds to %s to this setpoint\n", time, horc );

	char str [32];
	snprintf( str, 32, "%d", time );
	writeToVPoint( "../VPoints/TimeToNextSetpoint.vpoint", str );

	return 0;
}
