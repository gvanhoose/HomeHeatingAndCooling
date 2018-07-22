#include <stdio.h>

int main()
{
	double
		roomAirMass = 1.5,
		roomSpHeat = 290.0,
		roomHeat = roomAirMass * roomSpHeat,
		massFlow = 0.0001,
		inletSpHeat = 320.29,
		inletHeat = massFlow * inletSpHeat,
		outletSpHeat,
		outletHeat,
		SptSpHeat = 298.18,
		SptHeat = SptSpHeat * roomAirMass,
		dH
		;

	int i;
	while( roomHeat < SptHeat )
	{
		roomHeat = 
		dH = inletHeat - (outletHeat = massFlow * roomHeat
