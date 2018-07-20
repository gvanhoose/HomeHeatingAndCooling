#include "DayTime.h"

void printn( char* s, int i )
{
	printf( "\t%s = %d\n", s, i );
}
void printTime( struct tm* ltime )
{
	printf( "Local Time\n" );
	printn( "   year", ltime->tm_year );
	printn( "  month", ltime->tm_mon );
	printn( "    day", ltime->tm_mday );
	printn( "   hour", ltime->tm_hour );
	printn( "    min", ltime->tm_min );
	printn( "    sec", ltime->tm_sec );
	printn( "weedkay", ltime->tm_wday );
	printn( "    DST", ltime->tm_isdst );
	printf( "\n" );
}

time_t getETime()
{
	time_t etime;
	time( &etime );
	return etime;
}

struct tm* getDAT()
{
	time_t etime = getETime();

	return localtime( &etime );
}

void fixDAT( struct tm* ltime )
{
	if( ltime->tm_wday + 1 == 8 )
	{
		ltime->tm_wday = 1;
	}
	else
	{
		ltime->tm_wday += 1;
	}
	if( ltime->tm_mon + 1 == 13 )
	{
		ltime->tm_mon = 1;
		ltime->tm_year += 1901;
	}
	else
	{
		ltime->tm_mon += 1;
		ltime->tm_year += 1900;
	}
}

int secondOfTheDay( struct tm* ltime )
{
	int
		hour = ltime->tm_hour,
		min = ltime->tm_min,
		sec = ltime->tm_sec
	;

	return (hour * 3600) + (min * 60) + sec;
}
