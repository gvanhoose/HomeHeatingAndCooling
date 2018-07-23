#ifndef _STANDARDS_H_
#define _STANDARDS_H_

#include <stdio.h>
#include <string.h>

#define WORD_SIZE 32	// use with Raspberry Pi 2 and below
//#define WORD_SIZE 64	// use with Raspberry Pi 3 and above

//#define TIME_TO_TRANSITION "/home/pi/Desktop/HomeHeatingAndCooling/VPoints/TimeToTransition.vpoint"

void dbug();
double sToD( char* );

double fToK(double);
double kToF(double);
double cFToCM(double);
double cMToCF(double);
double cfmToCms(double);
double cmsTocfm(double);
double linearInterpolation( double, double, double, double, double );
double estimateSpHeat( double );


//#ifndef _GEOSTD_FUNCTIONS_
//#define _GEOSTD_FUNCTIONS_
//void dbug(){printf( "Reaching\n" );};
//#endif//_GEOSTD_FUNCTIONS_

#endif//_STANDARDS_H_
