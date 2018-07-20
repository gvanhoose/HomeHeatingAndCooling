#ifndef _SCHMGR_H_
#define _SCHMGR_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include "../FileIO.h"
//#include "../Standards.h"

struct transition
{
	int day;
	int second;
	char mode;
	double setpoint;
	int zone;
};

void prTrans( struct transition*, int );
int getSchedule( char*, int );
void schByDays( char*, int, int* );
int countTransitions( char*, int );
void isolTransitions( char**, int, char*, int );
void tokenizeTransition( char*, struct transition* );
int convertSchedule( struct transition*, char*, int );

#endif//_SCHMGR_H_
