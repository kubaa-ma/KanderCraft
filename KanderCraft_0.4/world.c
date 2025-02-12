#include <raylib.h>
#include <stdbool.h>
#include "block.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "stb_perlin.h"
#define STB_PERLIN_IMPLEMENTATION

#define vyska_sveta 28
#define delka_sveta 88
#define sirka_sveta 88

int random_g_x(){
    return rand() % (sirka_sveta - 8) + 8;
}

int random_g_z(){
    return rand() % (delka_sveta - 8) + 8;
}

float perlin_noise(float x, float z, int inputValue) {
    return stb_perlin_noise3((x + inputValue) * 0.074f, (z + inputValue) * 0.07f, 0.0f, 0, 0, 0) * 0.5f + 0.5f;

}
void world_generator_hi_hi(int world[vyska_sveta][delka_sveta][sirka_sveta], int inputValue) {
    int hight = 0;
    int set_place_tree_x = random_g_x();
    int set_place_tree_z = random_g_z();
    int tree_counter = 5; // pocet stromku
    srand(time(NULL));


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



    for(int j = 0; j < 47; j++){
        hight = 0;
        set_place_tree_x = random_g_x();
        set_place_tree_z = random_g_z();
        
        while(world[hight][set_place_tree_x][set_place_tree_z] != 1){
            hight+=1;

            if(hight > vyska_sveta - 8){
                break;
            }
        }

        if(hight <= vyska_sveta - 8 && 
            world[hight + 2][set_place_tree_x][set_place_tree_z] != 5
        && world[hight + 2][set_place_tree_x + 1][set_place_tree_z] != 5
        && world[hight + 2][set_place_tree_x - 1][set_place_tree_z] != 5
        && world[hight + 1][set_place_tree_x][set_place_tree_z + 1] != 5
        && world[hight + 1][set_place_tree_x][set_place_tree_z - 1] != 5
        && world[hight + 1][set_place_tree_x + 1][set_place_tree_z + 1] != 5
        && world[hight + 1][set_place_tree_x + 1][set_place_tree_z - 1] != 5
        && world[hight + 1][set_place_tree_x - 1][set_place_tree_z + 1] != 5
        && world[hight + 1][set_place_tree_x - 1][set_place_tree_z - 1] != 5        
        
        && world[hight + 3][set_place_tree_x + 2][set_place_tree_z] != 5
        && world[hight + 3][set_place_tree_x - 2][set_place_tree_z] != 5
        && world[hight + 3][set_place_tree_x][set_place_tree_z + 2] != 5
        && world[hight + 2][set_place_tree_x][set_place_tree_z - 2] != 5
        && world[hight + 2][set_place_tree_x + 2][set_place_tree_z + 2] != 5
        && world[hight + 2][set_place_tree_x + 2][set_place_tree_z - 2] != 5
        && world[hight + 2][set_place_tree_x - 2][set_place_tree_z + 2] != 5
        && world[hight + 2][set_place_tree_x - 2][set_place_tree_z - 2] != 5)
        {
            for(int i = 0; i < 6; i++){
            world[hight + i][set_place_tree_x][set_place_tree_z] = 5;}



            world[hight + 5][set_place_tree_x][set_place_tree_z] = 4; 
            world[hight + 5][set_place_tree_x + 1][set_place_tree_z] = 4;
            world[hight + 5][set_place_tree_x - 1][set_place_tree_z] = 4;
            world[hight + 5][set_place_tree_x][set_place_tree_z + 1] = 4;
            world[hight + 5][set_place_tree_x][set_place_tree_z - 1] = 4;
            world[hight + 5][set_place_tree_x + 1][set_place_tree_z - 1] = 4;

            world[hight + 4][set_place_tree_x][set_place_tree_z] = 4; 
            world[hight + 4][set_place_tree_x + 1][set_place_tree_z] = 4;
            world[hight + 4][set_place_tree_x - 1][set_place_tree_z] = 4;
            world[hight + 4][set_place_tree_x][set_place_tree_z + 1] = 4;
            world[hight + 4][set_place_tree_x][set_place_tree_z - 1] = 4;
            world[hight + 4][set_place_tree_x + 1][set_place_tree_z - 1] = 4;
            world[hight + 4][set_place_tree_x - 1][set_place_tree_z + 1] = 4;
            world[hight + 4][set_place_tree_x - 1][set_place_tree_z - 1] = 4;
            world[hight + 4][set_place_tree_x + 1][set_place_tree_z + 1] = 4;

            world[hight + 3][set_place_tree_x][set_place_tree_z] = 4; 
            world[hight + 3][set_place_tree_x + 1][set_place_tree_z] = 4;
            world[hight + 3][set_place_tree_x - 1][set_place_tree_z] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z + 1] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z - 1] = 4;
            world[hight + 3][set_place_tree_x + 1][set_place_tree_z - 1] = 4;
            world[hight + 3][set_place_tree_x - 1][set_place_tree_z + 1] = 4;
            world[hight + 3][set_place_tree_x - 1][set_place_tree_z - 1] = 4;
            world[hight + 3][set_place_tree_x + 1][set_place_tree_z + 1] = 4;

            world[hight + 3][set_place_tree_x][set_place_tree_z] = 4; 
            world[hight + 3][set_place_tree_x + 2][set_place_tree_z] = 4;
            world[hight + 3][set_place_tree_x - 2][set_place_tree_z] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z + 2] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z - 2] = 4;

            world[hight + 3][set_place_tree_x][set_place_tree_z] = 4; 
            world[hight + 3][set_place_tree_x + 2][set_place_tree_z] = 4;
            world[hight + 3][set_place_tree_x - 2][set_place_tree_z] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z + 2] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z - 2] = 4;
            world[hight + 3][set_place_tree_x + 1][set_place_tree_z - 2] = 4;
            world[hight + 3][set_place_tree_x - 1][set_place_tree_z + 2] = 4;
            world[hight + 3][set_place_tree_x - 1][set_place_tree_z - 2] = 4;
            world[hight + 3][set_place_tree_x + 1][set_place_tree_z + 2] = 4;

            world[hight + 3][set_place_tree_x][set_place_tree_z] = 4; 
            world[hight + 3][set_place_tree_x + 2][set_place_tree_z] = 4;
            world[hight + 3][set_place_tree_x - 2][set_place_tree_z] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z + 2] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z - 2] = 4;
            world[hight + 3][set_place_tree_x + 2][set_place_tree_z - 1] = 4;
            world[hight + 3][set_place_tree_x - 2][set_place_tree_z + 1] = 4;
            world[hight + 3][set_place_tree_x - 2][set_place_tree_z - 1] = 4;
            world[hight + 3][set_place_tree_x + 2][set_place_tree_z + 1] = 4;

            world[hight + 3][set_place_tree_x][set_place_tree_z] = 4; 
            world[hight + 3][set_place_tree_x + 1][set_place_tree_z] = 4;
            world[hight + 3][set_place_tree_x - 1][set_place_tree_z] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z + 1] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z - 1] = 4;
            world[hight + 3][set_place_tree_x + 1][set_place_tree_z - 1] = 4;
            world[hight + 3][set_place_tree_x - 1][set_place_tree_z + 1] = 4;
            world[hight + 3][set_place_tree_x - 1][set_place_tree_z - 1] = 4;
            world[hight + 3][set_place_tree_x + 1][set_place_tree_z + 1] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z] = 4; 
            world[hight + 3][set_place_tree_x + 1][set_place_tree_z] = 4;
            world[hight + 3][set_place_tree_x - 1][set_place_tree_z] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z + 1] = 4;
            world[hight + 3][set_place_tree_x][set_place_tree_z - 1] = 4;
            world[hight + 3][set_place_tree_x + 1][set_place_tree_z - 1] = 4;
            world[hight + 3][set_place_tree_x - 1][set_place_tree_z + 1] = 4;
            world[hight + 3][set_place_tree_x - 1][set_place_tree_z - 1] = 4;
            world[hight + 3][set_place_tree_x + 1][set_place_tree_z + 1] = 4;
            world[hight + 2][set_place_tree_x][set_place_tree_z] = 4; 
            world[hight + 2][set_place_tree_x + 2][set_place_tree_z] = 4;
            world[hight + 2][set_place_tree_x - 2][set_place_tree_z] = 4;
            world[hight + 2][set_place_tree_x][set_place_tree_z + 2] = 4;
            world[hight + 2][set_place_tree_x][set_place_tree_z - 2] = 4;

            world[hight + 2][set_place_tree_x][set_place_tree_z] = 4; 
            world[hight + 2][set_place_tree_x + 2][set_place_tree_z] = 4;
            world[hight + 2][set_place_tree_x - 2][set_place_tree_z] = 4;
            world[hight + 2][set_place_tree_x][set_place_tree_z + 2] = 4;
            world[hight + 2][set_place_tree_x][set_place_tree_z - 2] = 4;
            world[hight + 2][set_place_tree_x + 1][set_place_tree_z - 2] = 4;
            world[hight + 2][set_place_tree_x - 1][set_place_tree_z + 2] = 4;
            world[hight + 2][set_place_tree_x - 1][set_place_tree_z - 2] = 4;
            world[hight + 2][set_place_tree_x + 1][set_place_tree_z + 2] = 4;

            world[hight + 2][set_place_tree_x][set_place_tree_z] = 4; 
            world[hight + 2][set_place_tree_x + 2][set_place_tree_z] = 4;
            world[hight + 2][set_place_tree_x - 2][set_place_tree_z] = 4;
            world[hight + 2][set_place_tree_x][set_place_tree_z + 2] = 4;
            world[hight + 2][set_place_tree_x][set_place_tree_z - 2] = 4;
            world[hight + 2][set_place_tree_x + 2][set_place_tree_z - 1] = 4;
            world[hight + 2][set_place_tree_x - 2][set_place_tree_z + 1] = 4;
            world[hight + 2][set_place_tree_x - 2][set_place_tree_z - 1] = 4;
            world[hight + 2][set_place_tree_x + 2][set_place_tree_z + 1] = 4;
            world[hight + 2][set_place_tree_x][set_place_tree_z] = 4; 
            world[hight + 2][set_place_tree_x + 1][set_place_tree_z] = 4;
            world[hight + 2][set_place_tree_x - 1][set_place_tree_z] = 4;
            world[hight + 2][set_place_tree_x][set_place_tree_z + 1] = 4;
            world[hight + 2][set_place_tree_x][set_place_tree_z - 1] = 4;
            world[hight + 2][set_place_tree_x + 1][set_place_tree_z - 1] = 4;
            world[hight + 2][set_place_tree_x - 1][set_place_tree_z + 1] = 4;
            world[hight + 2][set_place_tree_x - 1][set_place_tree_z - 1] = 4;
            world[hight + 2][set_place_tree_x + 1][set_place_tree_z + 1] = 4;
        }
        else{
            j--;
        }
            
        
    }

}

