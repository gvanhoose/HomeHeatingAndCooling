#include <stdio.h>
#include "ossCalcs.h"
#include "ossVPoint.h"

int main()
{
	int tdeadline = transDeadline();
	double nxstpt = nextSetpoint();

	struct loopdata* ld;
	setRoomHeat(
