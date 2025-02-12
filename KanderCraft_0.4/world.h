#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <raylib.h>
#include <stdbool.h>
#include "block.h"
#include <stdio.h>

#define VYSKA_SVETA 28
#define DELKA_SVETA 88
#define SIRKA_SVETA 88

void world_generator_hi_hi(int world[VYSKA_SVETA][DELKA_SVETA][SIRKA_SVETA], int inputValue);

#endif
