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

	int secOfDay = (locTime->tm_hour * 3600) + (locTime->tm_min * 60) + locTime->tm_sec;

	printf( "Second #%d\n", secOfDay );

	return 0;
}
