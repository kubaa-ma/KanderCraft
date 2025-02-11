#include <raylib.h>
#include <stdbool.h>
#include "block.h"
#include <stdio.h>
#include <stdlib.h>

#include "stb_perlin.h"
#define STB_PERLIN_IMPLEMENTATION

#define vyska_sveta 20
#define delka_sveta 148
#define sirka_sveta 148



float perlin_noise(float x, float z, int inputValue) {
    return stb_perlin_noise3((x + inputValue) * 0.074f, (z + inputValue) * 0.07f, 0.0f, 0, 0, 0) * 0.5f + 0.5f;

}
void world_generator_hi_hi(int world[vyska_sveta][delka_sveta][sirka_sveta], int inputValue) {





    for (int x = 0; x < sirka_sveta-1; x++) {
        for (int z = 0; z < delka_sveta-1; z++) {
            int terrainHeight = (int)(perlin_noise(x, z, inputValue) * (vyska_sveta - 4)) + 4;

            for (int y = 0; y < vyska_sveta-1; y++) {
                if (y > terrainHeight) {
                    world[y][x][z] = 0; // Vzduch
                } else if (y == terrainHeight) {
                    world[y][x][z] = 1; // Tráva
                } else if (y > terrainHeight - 3) {
                    world[y][x][z] = 2; // Hlína
                } else {
                    world[y][x][z] = 3; // Kámen
                }
            }
            world[0][x][z] = 0;

        }
    }
}

