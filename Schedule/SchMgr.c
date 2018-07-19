#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../FileIO.h"
#include "../Standards.h"

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

int secondOfTheDay( struct tm* ltime )
{
	int
		hour = ltime->tm_hour,
		min = ltime->tm_min,
		sec = ltime->tm_sec
	;

	return (hour * 3600) + (min * 60) + sec;
}

int getSchedule( char* buffer, int alloc )
{
	int size = readFile( "schedule.sch", buffer, alloc );

	if( size < 0 )
	{
		printf( "there was an error.  Could not read schedule\n" );
		size = -1;
	}

	return size;
}

void schByDays( char* sched, int ssize, int* indices )
{
	indices[0] = 0;

	char c;

	int i, dayIndex = 1;
	for( i = 0; i < ssize; i++ )
	{

		if( sched[i] == '\n' )
		{
			sched[i] = '\0';
			if( dayIndex == 7 )
			{
				break;
			}
			indices[dayIndex++] = i + 1;
		}
	}
}

int countTransitions( char* daySch, int size )
{
	int t = 0,i;
	for( i = 0; i < size; i++ )
	{
		t += (daySch[i] == ' ')? 1 : 0;
	}
	return t;
}

void isolTransitions( char** trans, int ntrans, char* daySch, int size )
{
//	printf( "Entering isolTransitions(...)\n" );
//	printf( "\tntrans = %d\n", ntrans );
//	printf( "\t  size = %d\n", size );

	int curtran = 0, i, toklen = 0;
	for( i = 2; i < size; i++ )		// skip the first two chars, which is the weekday number and the first space
	{
//		printf( "i = %d ", i );
		if( daySch[i] == ' ' )
		{
			curtran++;
			toklen = 0;
			continue;
		}
		trans[curtran][toklen++] = daySch[i];

//		printf( "\ttrans[%d][%d] = %c\n", curtran, toklen - 1, trans[curtran][toklen - 1] );
	}
//	printf( "Exiting isolTransitions(...)\n" );
}

struct transition
{
	int second;
	char mode;
	double setpoint;
	int zone;
};
void printTrans( struct transition* tr, int day, int tnum )
{
	printf( "Day %d\n", day );
	printf( "Transition #%d\n", tnum );

	printf( "\t  second = %d\n", tr->second );
	printf( "\t    mode = %c\n", tr->mode );
	printf( "\tsetpoint = %lf\n", tr->setpoint );
	printf( "\t    zone = %d\n", tr->zone );

	printf( "\n" );
}


void tokenizeTransition( char* transition, struct transition* tran )
{
	char
		time0 = transition[0],
		time1 = transition[1],
		time2 = transition[2],
		time3 = transition[3],
		md = transition[5],
		stpt0 = transition[7],	// \_ it's always gonna be two digits
		stpt1 = transition[8],	// /
		zone0 = transition[10],
		zone1 = transition[11],
		zone2 = transition[12]
		;

	int
		hr = (int)( ((time0 & 0x0F)*10) + (time1 & 0x0F) ),
		mn = (int)( ((time2 & 0x0F)*10) + (time3 & 0x0F) ),
		sec = hr*3600 + mn*60,
		sp = (int)( ((stpt0 & 0x0F)*10) + (stpt1 & 0x0F) ),
		zn = (int)( ((zone0 & 0x0F)*100) + ((zone1 & 0x0F)*10) + (zone2 & 0x0f) )
		;

	tran->second = sec;
	tran->mode = md;
	tran->setpoint = (double)(sp);
	tran->zone = zn;
}

void convertSchedule()
{
	int txtalloc = 1024;
	char buffer [txtalloc];
	int ssize = getSchedule( buffer, txtalloc );//TODO:  left off here, quite abruptly


int main()
{
	struct tm* ltime = getDAT();

	fixDAT( ltime );

//	printTime( ltime );


	int schalloc = 1024;
	char schbuff [schalloc];

	int schsize = getSchedule( schbuff, schalloc );

//	printf( "schsize = %d\n", schsize );
//	printf( "\nschedule:\n<\n%s>\n\n", schbuff );

	int dayOffsets [7];

	schByDays( schbuff, schsize, dayOffsets );

//	char* sun = schbuff + dayOffsets[0];
//	char* mon = schbuff + dayOffsets[1];
//	char* tue = schbuff + dayOffsets[2];
//	char* wed = schbuff + dayOffsets[3];
//	char* thu = schbuff + dayOffsets[4];
//	char* fri = schbuff + dayOffsets[5];
//	char* sat = schbuff + dayOffsets[6];
//
//	printf( "\t   Sunday = \"%s\"\n", sun );
//	printf( "\t   Monday = \"%s\"\n", mon );
//	printf( "\t  Tuesday = \"%s\"\n", tue );
//	printf( "\tWednesday = \"%s\"\n", wed );
//	printf( "\t Thursday = \"%s\"\n", thu );
//	printf( "\t   Friday = \"%s\"\n", fri );
//	printf( "\t Saturday = \"%s\"\n", sat );

	struct transition* allTranTokens [7];
	int tcounts [7];
	char* curDay;
	int i, curCount, o;
	for( i = 0; i < 7; i++ )
	{
// segfault after this line at i = 0

		curDay = schbuff + dayOffsets[i];
		curCount = tcounts[i] = countTransitions( curDay, strlen(curDay) );

		char* indivTrans [curCount];

		for( o = 0; o < curCount; o++ )
		{
			indivTrans[o] = malloc(32);
			memset( indivTrans[o], '\0', 32 );

//			printf( "\tAllocated memory at 0x%x\n", indivTrans + o );

		}

//		printf( "curCount = %d\n", curCount );
//		printf( "  curDay = %d\"%s\"\n", strlen(curDay), curDay );

// segfault after this line
		isolTransitions( indivTrans, curCount, curDay, strlen(curDay) );
// segfault before this line

		allTranTokens[i] = (struct transition*) malloc( WORD_SIZE * curCount );

// segfault before this line
		for( o = 0; o < curCount; o++ )
		{
			struct transition ctran;
			tokenizeTransition( indivTrans[o], &ctran );

			*(allTranTokens[i] + o) = ctran;

			printTrans( allTranTokens[i] + o, i, o );


			free( indivTrans[o] );
		}

	}

	for( i = 0; i < 7; i++ )
	{
		free( allTranTokens[i] );
	}
//	int mtranct = countTransitions( mon, strlen(mon) );
//	printf( "monday transitions:  %d\n", mtranct );
//
//	char* mtrans [mtranct];
//	int i;
//	for( i = 0; i < mtranct; i++ )
//	{
//		mtrans[i] = malloc(32);
//	}
//
//	isolTransitions( mtrans, mtranct, mon, strlen(mon) );
//
//	printf( "m0 = \"%s\"\n", mtrans[0] );
//	printf( "m1 = \"%s\"\n", mtrans[1] );
//	printf( "m2 = \"%s\"\n", mtrans[2] );
//
//
//	struct transition mtr;
//
//	tokenizeTransition( mtrans[0], &mtr );
//
//	printTrans( &mtr, 2, 0 );
//
//	for( i = 0; i < mtranct; i++ )
//	{
//		free( mtrans[i] );
//	}

	return 0;
}
