#ifndef _DAYTIME_H_
#define _DAYTIME_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include "../FileIO.h"
//#include "../Standards.h"

#define BASE_YEAR 1900
#define MONTH_OFFSET 1

void printn( char*, int );
void printTime( struct tm* );
time_t getETime();
struct tm* getDAT();
void fixDAT( struct tm* );
int secondOfTheDay( struct tm* );

#endif//_DAYTIME_H_
