#include <raylib.h>
#include <stdbool.h>
#include "block.h"
#include <stdio.h>
#include <stdlib.h>

#define vyska_sveta 10
#define delka_sveta 48
#define sirka_sveta 48


void world_generator_hi_hi(int world[vyska_sveta][delka_sveta][sirka_sveta]){

    for(int y = 0; y < vyska_sveta - 1; y++){
        for(int x = 0; x < sirka_sveta - 1; x++){
            for(int z = 0; z < delka_sveta - 1; z++){

                world[y][x][z] = 2;
                world[vyska_sveta - 7][x][z] = 1;

                world[vyska_sveta - 1][x][z] = 0;
                world[vyska_sveta - 2][x][z] = 0;
                world[vyska_sveta - 3][x][z] = 0;
                world[vyska_sveta - 4][x][z] = 0;
                world[vyska_sveta - 5][x][z] = 0;
                world[vyska_sveta - 6][x][z] = 0;


                world[0][x][z] = 0;
                world[1][x][z] = 3;

            }
        }
    }
}