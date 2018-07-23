#include "Standards.h"

void dbug()
{
	printf("Reaching");
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
