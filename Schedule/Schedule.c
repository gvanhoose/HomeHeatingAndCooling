#include "DayTime.h"
#include "SchMgr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../FileIO.h"
#include "../Standards.h"

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


	struct transition curDay [tranSize];
	int i, daySize;
	for( i = 0; i < tranSize; i++ )
	{
		if( allTrans[i].day == dayOfWeek )
		{
			curday[daySize++] = allTrans[i];
		}
	}

	struct transition nextTran;
	int smallestPosTime
	for( i = 0; i < daySize; i++ )
	{
		if( curDay//TODO I can't think anymore.  Time to relaaaaaxxxxxx










	return 0;
}
