#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>
#include "block.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846
#define MAX_DIGITS 10

#define VYSKA_SVETA 28
#define DELKA_SVETA 88
#define SIRKA_SVETA 88



void objekty_svete(int world[VYSKA_SVETA][SIRKA_SVETA][DELKA_SVETA]);

#endif 