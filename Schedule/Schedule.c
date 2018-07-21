#include "DayTime.h"
#include "SchMgr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../FileIO.h"
#include "../Standards.h"
#include "../ValuePoint/ValuePoint.h"

int findDay( struct transition* tar, struct transition* src, int size, int day )
{
	int i, outsize = 0;
	for( i = 0; i < size; i++ )
	{
		if( src[i].day == day )
		{
			tar[ outsize++ ] = src[i];
		}
	}
	return outsize;
}

int findNextTransition( struct transition* trs, int size, int day, int second )
{
	int i, sposwtIndex = 0, smallestPositiveWait = (-1 >> 1);
	for( i = 0; i < size; i++ )
	{
		int
			ctDay = trs[i].day,
			ctSec = trs[i].second
			;

		if( day == ctDay )
		{
			if( second <= ctSec )
			{
				return i;
			}
		}
	}
	return findNextTransition( trs, size, (day + 1 == 8)? 1 : day + 1, 0 );
}
void reorgTrans( struct transition* tar, struct transition* src, int size, int day, int second )
{
	int
		startPos = findNextTransition( src, size, day, second ),
		i = startPos,
		tIndex = 0
		;

	do
	{
		tar[tIndex++] = src[i];

		i = (i + 1 == size)? 0 : i + 1;

	} while( i != startPos );


}

int timeToTransition( struct transition* nt, int day, int sec )
{
	if( nt->day == day )	// the "easy" case...
	{
		return nt->second - sec;
	}

	int
		tday = (nt->day >= day)? nt->day : nt->day + 7,
		ndays = tday - day,
		dayseconds = 24 * 3600,
		daysInSeconds = (ndays - 1)*dayseconds + nt->second + (dayseconds - sec)
		;

	return ((ndays - 1) * dayseconds) + nt->second + (dayseconds - sec);
}

int main()
{
	struct tm* locTime = getDAT();
	fixDAT( locTime );

	int
		secOfDay = (locTime->tm_hour * 3600) + (locTime->tm_min * 60) + locTime->tm_sec,
		dayOfWeek = locTime->tm_wday
		;

	char txtSched [1024];
	int
		txtSchSize = getSchedule( txtSched, 1024 ),
		ntrans = countTransitions( txtSched, txtSchSize )
		;

	struct transition* allTrans;
	allTrans = (struct transition*) malloc( ntrans * sizeof( struct transition ) );

	int tranSize = convertSchedule( allTrans, txtSched, txtSchSize );

	struct transition* reorgs;
	reorgs = (struct transition*) malloc( ntrans * sizeof( struct transition ) );

	reorgTrans( reorgs, allTrans, tranSize, dayOfWeek, secOfDay );


//	printf( "\nReorganizd\n" );
//	prTrans( reorgs, tranSize );


	struct transition currentMode = reorgs[ tranSize - 1 ];
	struct transition nextMode = reorgs[0];

//	printf( "currentMode:\n" );
//	pTr( &currentMode );
//
//	printf( "nextMode:\n" );
//	pTr( &nextMode );


	int
		tttSec = timeToTransition( &nextMode, dayOfWeek, secOfDay )//,
//		daysRem = tttSec / (24 * 3600),
//		hoursRem = (tttSec % (24 * 3600)) / 3600,
//		minsRem = ((tttSec % (24 * 3600)) % 3600) / 60,
//		secsRem = ((tttSec % (24 * 3600)) % 3600) % 60
		;

//	printf( "Time to transition = %d\n", tttSec );
//	printf( "                 D = %d\n", daysRem );
//	printf( "                 H = %d\n", hoursRem );
//	printf( "                 M = %d\n", minsRem );
//	printf( "                 S = %d\n", secsRem );


	char tttVPoint [16];
	memset( tttVPoint, '\0', 16 );
	int valueLen = snprintf( tttVPoint, 16, "%d", tttSec );

	writeToVPoint( "../VPoints/TimeToTransition.vpoint", tttVPoint );

	writeToVPoint( "../VPoints/CurrentMode.vpoint", &currentMode.mode );

	return 0;
}
