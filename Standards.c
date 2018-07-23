#include "Standards.h"

void dbug()
{
	printf("Reaching");
}

double sToD( char* s )
{
	double out = 0.0, factor = 0.1, posneg = 1.0;
	int pointHit = 0, slen = strlen(s), i;
	for( i = 0; i < slen; i++ )
	{
		if( s[i] == '.' )
		{
			pointHit = 1;
			continue;
		}
		if( i == 0 && s[i] == '-' )
		{
			posneg = -1.0;
			continue;
		}
		if( s[i] < 0x30 || s[i] > 0x39 )
		{
			return out * posneg;
		}
		if( !pointHit )
		{
			out *= 10.0;
			out += s[i] & 0x0f;
		}
		if( pointHit )
		{
			out += (s[i] & 0x0f) * factor;
			factor /= 10.0;
		}
	}
	return out * posneg;
}

double fToK(double f)
{
	return (f + 459.67) * 5.0/9.0;
}
double kToF(double k)
{
	return (k * 9.0/5.0) - 459.67;
}
double cFToCM(double cf)
{
	return cf / 35.315;
}
double cMToCF(double cm)
{
	return cm * 35.315;
}
double cfmToCms(double cfm)
{
	return cFToCM(cfm) / 60.0;
}
double cmsToCfm(double cms)
{
	return cMToCF(cms) * 60.0;
}

double linearInterpolation( double yLo, double yHi, double xLo, double xHi, double xGv )
{
	double
		dy = yHi - yLo,
		dx = xHi - xLo,
		dydx = dy/dx,
		dX = xGv - xLo,
		dY = dX * dydx
		;
	return yLo + dY;
}
double estimateSpHeat( double temp )
{
	return linearInterpolation( 290.16, 320.29, 290.0, 320.0, temp );
}
