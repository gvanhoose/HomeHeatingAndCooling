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
	int i, bufflen = readVPoint( "../VPoints/NextSetpoint.vpoint", nxsptbuff, 8 );

	return sToD( nxsptbuff );
}

int nextRoom()
{
	char nxrmbuff [8];
	int i, bufflen = readVPoint( "../VPoints/NextRoom.vpoint", nxrmbuff, 8 );

	int nxtRoom = 0;
	for( i = 0; i < bufflen; i++ )
	{
		if( nxrmbuff[i] < 0x30 || nxrmbuff[i] > 0x39 )
		{
			continue;
		}
		nxtRoom *= 10;
		nxtRoom += nxrmbuff[i] & 0x0f;
	}
	return nxtRoom;
}



void getRoomData( struct loopdata* ld, char* roomNumber )
{
	char data [64];
	char* ram = data;
	char* mfr = data + 16;
	char* rsh = data + 32;
	char* ish = data + 48;

	char vpaddr [128];
	char* cvppos = vpaddr;

	cvppos += snprintf( vpaddr, 128, "../VPoints/Room%s", roomNumber );

	snprintf( cvppos, 64, "/RoomAirMass.vpoint" );
	readVPoint( vpaddr, ram, 15 );

	snprintf( cvppos, 64, "/MassFlowRate.vpoint" );
	readVPoint( vpaddr, mfr, 15 );

	snprintf( cvppos, 64, "/RoomSpecificHeat.vpoint" );
	readVPoint( vpaddr, rsh, 15 );

	snprintf( cvppos, 64, "/InletSpecificHeat.vpoint" );
	readVPoint( vpaddr, ish, 15 );

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

//int main()
//{
//	int
//		nxtrans = transDeadline(),
//		nxroom = nextRoom()
//		;
//
//	char nxRm [3] = {'0','0',(char) (nxroom + 0x30)};	// until we add more rooms to the house, this will suffice!
//
//	struct loopdata ld;
//	getRoomData( &ld, nxRm );
//
//	printf( "ram = %lf\n", ld.roomAirMass );
//	printf( "mfr = %lf\n", ld.massFlow );
//	printf( "isp = %lf\n", ld.inletHeat );
//	printf( "rht = %lf\n", ld.roomHeat );
//
////	int
////		nxtrans = transDeadline(),
////		nxroom = nextRoom()
////		;
////	double nxstpt = nextSetpoint();
//
//
//
//
//
//
//
//
//
////	int ttt = transDeadline();
////	printf( "Time to next transition:  %d seconds\n", ttt );
////
////	int
////		hena = heatEnabled(),
////		cena = coolEnabled(),
////		eena = econEnabled()
////		;
////
////	printf( "heat, cool, econ flags:  %d, %d, %d\n", hena, cena, eena );
////
////
//	return 0;
//}
