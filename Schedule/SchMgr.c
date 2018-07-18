#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BASE_YEAR 1900
#define MONTH_OFFSET 1

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
/*	struct tm ltime = *localtime( &etime );

	if( ltime.tm_mon + 1 == 13 )
	{
		ltime.tm_mon = 0;
		ltime.tm_year += 1901;
	}
	else
	{
		ltime.tm_mon += 1;
		ltime.tm_year += 1900;
	}

	return &ltime;
*/
}

void fixDAT( struct tm* ltime )
{
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

int main()
{
//	time_t etime = getETime();
//	printf( "etime = %d\n", etime );
//
//	struct tm* ltime = localtime( &etime );

	struct tm* ltime = getDAT();

	fixDAT( ltime );

	printTime( ltime );



	return 0;
}
