#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../FileIO.h"
#include "../Standards.h"

struct transition
{
	int day;
	int second;
	char mode;
	double setpoint;
	int zone;
};

void prTrans( struct transition* tr, int size )
{
	struct transition c;
	int i;
	for( i = 0; i < size; i++ )
	{
		c = tr[i];
		printf( "Transition %d\n", i );
		printf( "\t     day = %d\n", c.day );
		printf( "\t  second = %d\n", c.second );
		printf( "\t    mode = %c\n", c.mode );
		printf( "\tsetpoint = %lf\n", c.setpoint );
		printf( "\t    zone = %d\n\n", c.zone );
	}
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
	int curtran = 0, i, toklen = 0;
	for( i = 2; i < size; i++ )		// skip the first two chars, which is the weekday number and the first space
	{
		if( daySch[i] == ' ' )
		{
			curtran++;
			toklen = 0;
			continue;
		}
		trans[curtran][toklen++] = daySch[i];
	}
}


void tokenizeTransition( char* transition, struct transition* tran )
{
	char
		day = transition[0],
		time0 = transition[1],
		time1 = transition[2],
		time2 = transition[3],
		time3 = transition[4],
		md = transition[6],
		stpt0 = transition[8],	// \_ it's always gonna be two digits
		stpt1 = transition[9],	// /
		zone0 = transition[11],
		zone1 = transition[12],
		zone2 = transition[13]
		;

	int
		dy = (int) (day & 0x0F),
		hr = (int)( ((time0 & 0x0F)*10) + (time1 & 0x0F) ),
		mn = (int)( ((time2 & 0x0F)*10) + (time3 & 0x0F) ),
		sec = hr*3600 + mn*60,
		sp = (int)( ((stpt0 & 0x0F)*10) + (stpt1 & 0x0F) ),
		zn = (int)( ((zone0 & 0x0F)*100) + ((zone1 & 0x0F)*10) + (zone2 & 0x0f) )
		;

	tran->day = dy;
	tran->second = sec;
	tran->mode = md;
	tran->setpoint = (double)(sp);
	tran->zone = zn;
}

int convertSchedule( struct transition* theWeek, char* buffer, int ssize )
{
	int txtalloc = 1024;
	int dayOffsets [7];

	schByDays( buffer, ssize, dayOffsets );

	int tcounts [7];
	char* curDay;
	int i, curCount, o, outsize;
	for( i = 0; i < 7; i++ )
	{
		curDay = buffer + dayOffsets[i];
		curCount = countTransitions( curDay, strlen(curDay) );

		char* indivTrans [curCount];
		for( o = 0; o < curCount; o++ )
		{
			indivTrans[o] = malloc(32);
			memset( indivTrans[o], '\0', 32 );
		}
		isolTransitions( indivTrans, curCount, curDay, strlen(curDay) );

		for( o = 0; o < curCount; o++ )
		{
			tokenizeTransition( indivTrans[o], theWeek + outsize++ );//theWeek + outsize++ );
			free( indivTrans[o] );
		}
	}

	return outsize;

}
