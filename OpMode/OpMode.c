#include <stdio.h>
#include "../ValuePoint/ValuePoint.h"

double getOutsideAirTemp()
{
	// in the near future, this will be rewritten such that it reads from a network device
	return 70.3;
}

double getCoolEnableSetpoint()
{
	char buff [32];
	readVPoint( "../VPoints/CoolEnableSetpoint.vpoint", buff );


int main()
{
	
