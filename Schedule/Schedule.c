#include "DayTime.h"
#include "SchMgr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../FileIO.h"
#include "../Standards.h"

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

int isNextTransition( int trday, int curday, int trsec, int cursec, int smallestPosWaitSoFar )
{
	return trday == curday && trsec - cursec < smallestPosWaitSoFar && trsec - cursec >= 0;
}

int findNextTransition( struct transition* trs, int size, int day, int second )
{
	int i, sposwtIndex = 0, smallestPositiveWait = (-1 >> 1);
	for( i = 0; i < size; i++ )
	{
		if( isNextTransition( trs[i].day, day, trs[i].second, second, smallestPositiveWait ) )
		{
			sposwtIndex = i;
			smallestPositiveWait = trs[i].second - second;
		}
//		if( trs[i].day == dat->tm_wday )
//		{
//			if( trs[i].second - second < smallestPositiveWait && trs[i].second - second >= 0 )
//			{
//				sposwtIndex = i;
//				smallestPosWait = trs[i].second - second;
//			}
//		}
	}
	if( sposwtIndex > 0 )
	{
		return sposwtIndex;
	}

	return findNextTransition( trs, size, (day + 1 == 8)? 1 : day + 1, second );

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
printf( "\ti = %d\n", i );

		tar[tIndex++] = src[i];

		i = (i + 1 == size)? 0 : i + 1;

	} while( i != startPos );


}

int main()
{
	struct tm* locTime = getDAT();
	fixDAT( locTime );

	int
		secOfDay = (locTime->tm_hour * 3600) + (locTime->tm_min * 60) + locTime->tm_sec,
		dayOfWeek = locTime->tm_wday
		;

//	printf( "Second #%d\n", secOfDay );
//	printf( "   Day #%d\n", dayOfWeek );

	char txtSched [1024];
	int
		txtSchSize = getSchedule( txtSched, 1024 ),
		ntrans = countTransitions( txtSched, txtSchSize )
		;

	struct transition* allTrans;
	allTrans = (struct transition*) malloc( ntrans * sizeof( struct transition ) );

	int tranSize = convertSchedule( allTrans, txtSched, txtSchSize );

//	prTrans( allTrans, tranSize );

	struct transition* reorgs;
	reorgs = (struct transition*) malloc( ntrans * sizeof( struct transition ) );

dbug();
	reorgTrans( reorgs, allTrans, tranSize, dayOfWeek, secOfDay );


	printf( "\nReorganizd\n" );

	prTrans( reorgs, tranSize );







	return 0;
}
