
#ifndef _OSSVPOINT_H_
#define _OSSVPOINT_H_

#include <stdio.h>
#include "../ValuePoint/ValuePoint.h"
#include "../Standards.h"
#include "ossCalcs.h"

int transDeadline();
int heatEnabled();
int coolEnabled();
int econEnabled();
double nextSetpoint();
void coolStart();
void heatStart();
void econStart();

#endif//_OSSVPOINT_H_
