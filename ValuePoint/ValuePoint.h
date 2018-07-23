#ifndef _VALUEPOINT_H_
#define _VALUEPOINT_H_

#include <stdio.h>
#include <string.h>

int writeToVPoint( char* vName, char* value );
int readVPoint( char* vName, char* target, int tarSize );

#endif//_VALUEPOINT_H_
