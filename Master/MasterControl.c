#include <stdio.h>
#include "../ValuePoint/ValuePoint.h"
#include "../Standards.h"


void FanCommand( int cmd )
{
	char s [2];
	s[0] = '0' + cmd;
	s[1] = '\0';

	writeToVPoint( "../VPoints/FanCommand.vpoint", s );
	printf( "  Fan Command = %d\n", cmd );
}
void HeatCommand( int cmd )
{
	char s [2];
	s[0] = '0' + cmd;
	s[1] = '\0';

	writeToVPoint( "../VPoints/HeatCommand.vpoint", s );
	printf( "Heat Commmand = %d\n", cmd );
	FanCommand( cmd );
}
void CoolCommand( int cmd )
{
	char s [2];
	s[0] = '0' + cmd;
	s[1] = '\0';

	writeToVPoint( "../VPoints/CoolCommand.vpoint", s );
	printf( " Cool Command = %d\n", cmd );
	FanCommand( cmd );
}

char getCharVPoint( char* vp )
{
	char cv [2];
	readVPoint( vp, cv, 2 );

	return *cv;
}
int getIntVPoint( char* vp )
{
	char cv [32];
	int i, val = 0, cvlen = readVPoint( vp, cv, 32 ), posneg = (cv[0] == '-')? -1 : 1;

	char c;
	for( i = 0; i < cvlen; i++ )
	{
		c = cv[i];
		if( c < 0x30 || c > 0x39 )
		{
			continue;
		}
		val *= 10;
		val += c & 0x0f;
	}
	return val * posneg;
}
double getDoubleVPoint( char* vp )
{
	char cv [32];
	readVPoint( vp, cv, 32 );

	return sToD(cv);
}

void maintainSetpoint( double loSpt, double hiSpt, double rmTemp, char phase, int clgEna, int htgEna )
{
	int prevCmd;
	if( phase == 'c' && clgEna )
	{
		printf( "\t\tCool Mode\n" );
		prevCmd = getIntVPoint( "../VPoints/CoolCommand.vpoint" );
		if( loSpt <= rmTemp && rmTemp <= hiSpt )
		{

			printf( "\t\t%lfl <= %lfr <= %lfh\n", loSpt, rmTemp, hiSpt );
			CoolCommand( prevCmd );
			return;
		}
		if( rmTemp < loSpt )
		{
			printf( "\t\t%lfr < %lfl\n", rmTemp, loSpt );
			CoolCommand(0);
			return;
		}
		if( rmTemp > hiSpt )
		{
			printf( "\t\t%lfr > %lfh\n", rmTemp, hiSpt );
			CoolCommand(1);
			return;
		}
	}
	if( phase == 'h' && htgEna )
	{
		printf( "\t\tHeat Mode\n" );
		prevCmd = getIntVPoint( "../VPoints/HeatCommand.vpoint" );
		if( loSpt <= rmTemp && rmTemp <= hiSpt )
		{

			printf( "\t\t%lfl <= %lfr <= %lfh\n", loSpt, rmTemp, hiSpt );
			HeatCommand( prevCmd );
			return;
		}
		if( rmTemp < loSpt )
		{
			printf( "\t\t%lfr < %lfl\n", rmTemp, loSpt );
			HeatCommand(1);
			return;
		}
		if( rmTemp > hiSpt )
		{
			printf( "\t\t%lfr > %lfh\n", rmTemp, hiSpt );
			HeatCommand(0);
			return;
		}
	}

	int prevHCmd, prevCCmd;
	if( phase == 'm' )
	{
		printf( "\tMaintain Mode\n" );
		prevHCmd = getIntVPoint( "../VPoints/HeatCommand.vpoint" );
		prevCCmd = getIntVPoint( "../VPoints/CoolCommand.vpoint" );
		if( loSpt <= rmTemp && rmTemp <= hiSpt )
		{

			printf( "\t\t%lfl <= %lfr <= %lfh\n", loSpt, rmTemp, hiSpt );
			HeatCommand( prevHCmd & htgEna );
			CoolCommand( prevCCmd & clgEna );
			return;
		}
		if( rmTemp < loSpt )
		{
			printf( "\t\t%lfr < %lfl\n", rmTemp, loSpt );
			HeatCommand(htgEna);
			CoolCommand(0);
			return;
		}
		if( rmTemp > hiSpt )
		{
			printf( "\t\t%lfr > %lfh\n", rmTemp, hiSpt );
			HeatCommand(0);
			CoolCommand(clgEna);
			return;
		}
	}
}
int main()
{
	double
		nxSpt = getDoubleVPoint( "../VPoints/NextSetpoint.vpoint" ),
		clgEnaSpt = getDoubleVPoint( "../VPoints/CoolEnableSetpoint.vpoint" ),
		htgEnaSpt = getDoubleVPoint( "../VPoints/HeatEnableSetpoint.vpoint" ),
		oaTemp = getDoubleVPoint( "../VPoints/OutsideAirTemp.vpoint" ),
		targRmTemp
		;
	int
		clgEna = getIntVPoint( "../VPoints/CoolEnable.vpoint" ),
		htgEna = getIntVPoint( "../VPoints/HeatEnable.vpoint" ),
		nxRm = getIntVPoint( "../VPoints/NextRoom.vpoint" ),
		ttNxSpt = getIntVPoint( "../VPoints/TimeToNextSetpoint.vpoint" ),
		ttTrans = getIntVPoint( "../VPoints/TimeToTransition.vpoint" )
		;
	char
		curMode = getCharVPoint( "../VPoints/CurrentMode.vpoint" ),
		heatPhase = getCharVPoint( "../VPoints/HeatPhase.vpoint" )
		;

	char targRmAddr [64];
	int traLen = snprintf( targRmAddr, 64, "../VPoints/Room00%d/RoomTemp.vpoint", nxRm );

	targRmTemp = getDoubleVPoint( targRmAddr );


	printf( "Value Point Data:\n" );
	printf( "\t              Next setpoint = %lf\n", nxSpt );
	printf( "\t       Cool enable setpoint = %lf\n", clgEnaSpt );
	printf( "\t       Heat enable setpoint = %lf\n", htgEnaSpt );
	printf( "\t           Outside air temp = %lf\n", oaTemp );
	printf( "\t                Cool enable = %d\n", clgEna );
	printf( "\t                Heat enable = %d\n", htgEna );
	printf( "\t                  Next room = %d\n", nxRm );
	printf( "\tTime to reach next setpoint = %d\n", ttNxSpt );
	printf( "\t         Time to transition = %d\n", ttTrans );
	printf( "\t   Current operational mode = %c\n", curMode );
	printf( "\t                 Heat phase = %c\n", heatPhase );
	printf( "\t           Target room temp = %lf\n", targRmTemp );
	printf( "End Value Point Data\n\n" );

	nxSpt = fToK(nxSpt);
	clgEnaSpt = fToK(clgEnaSpt);
	htgEnaSpt = fToK(htgEnaSpt);
	oaTemp = fToK(oaTemp);
	targRmTemp = fToK(targRmTemp);

	double
		loNxSpt = nxSpt - (5.0/9.0),
		hiNxSpt = nxSpt + (5.0/9.0)
		;

	int timeToHeatUp = ttTrans - ttNxSpt;
	if( timeToHeatUp == 0 )
	{
		printf( "refocus on room %d\n", nxRm );

		if( targRmTemp < nxSpt )
		{
			writeToVPoint( "../VPoints/HeatPhase.vpoint", "h" );
			return 0;
		}
		if( targRmTemp > nxSpt )
		{
			writeToVPoint( "../VPoints/HeatPhase.vpoint", "c" );
			return 0;
		}
	}
	if( ttTrans == 0 )
	{
		printf( "Transition reached\n" );
		writeToVPoint( "../VPoints/HeatPhase.vpoint", "m" );
		return 0;
	}

	if( heatPhase == 'm' )
	{
		printf( "Readjusting variables for maint mode\n" );
		int curRoom = getIntVPoint( "../VPoints/CurrentRoom.vpoint" );

		char curRoomTemp [32];
		snprintf( curRoomTemp, 32, "../VPoints/Room00%d/RoomTemp.vpoint", curRoom );

		targRmTemp = fToK( getDoubleVPoint( curRoomTemp ) );

		nxSpt = fToK( getDoubleVPoint( "../VPoints/CurrentSetpoint.vpoint" ) );
		loNxSpt = nxSpt - (5.0/9.0);
		hiNxSpt = nxSpt + (5.0/9.0);
	}

	maintainSetpoint( loNxSpt, hiNxSpt, targRmTemp, heatPhase, clgEna, htgEna );

	return 0;
}
