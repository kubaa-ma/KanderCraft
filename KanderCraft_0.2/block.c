#include <raylib.h>
#include <stdbool.h>
#include "block.h"
#include <stdio.h>

#define vyska_sveta 10
#define delka_sveta 48
#define sirka_sveta 48

#define velikost 0.1f //nemenit

void block(Model *model, Texture2D texture_top, Texture2D texture_site, Texture2D texture_bottom,
           Texture2D texture_site1, Texture2D texture_block_site2, Texture2D texture_block_site3, 
           float *pos, int world[vyska_sveta][delka_sveta][sirka_sveta], float sour_x[], float sour_y[], float sour_z[], Texture2D texture_dirt_dark, Texture2D texture_dirt_darker,
           Texture2D texture_cobblestone, Texture2D texture_cobblestone_dark, Texture2D texture_cobblestone_darker)
{
    // Mřížka s hodnotami (0 = vzduch, 1 = blok)
    int pole[3][3][3] = {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},  // horni prostredni dolni
        {{0, 0, 0}, {0, 1, 0}, {0, 1, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    };

    Mesh rectangleMesh = GenMeshPlane(10, 10, 16, 16);
    Model rectangleModel = LoadModelFromMesh(rectangleMesh);

    Vector3 blockSize = (Vector3){velikost, velikost, velikost};

    for (int y = 0; y < vyska_sveta - 1; y++) {
        for (int z = 0; z < delka_sveta - 1; z++) {
            for (int x = 0; x < sirka_sveta - 1; x++) {//vypis predstavy pole
                if (world[y][z][x] != 0) {//pokud dana souradnice obsahuje block pokracuj

                        for (int z = 0; z < 3; z++) {
                            for (int y = 0; y < 3; y++) {
                                for (int x = 0; x < 3; x++) {
                                    pole[z][y][x] = 0;
                                }
                            }
                        }

                    if(world[y+1][z][x] == 1 || world[y+1][z][x] == 2 || world[y+1][z][x] == 3){// 1 horni
                        pole[1][0][1] = 1; //x, y, z
                    }
                    else if(world[y+1][z][x] == 0){
                        pole[1][0][1] = 0;
                    }
                    
                    if(world[y - 1][z][x] == 1 || world[y - 1][z][x] == 2 || world[y - 1][z][x] == 3){//2 spodni
                        pole[1][2][1] = 1;
                    }
                    
                     else if(world[y - 1][z][x] == 0){
                        pole[1][2][1] = 0;
                    }

                    if(world[y][z + 1][x] == 1 || world[y][z + 1][x] == 2 || world[y][z + 1][x] == 3){//3 predni
                        pole[2][1][1] = 1;
                    }
                    
                     else if(world[y][z + 1][x] == 0){
                        pole[2][1][1] = 0;
                    }

                    if(world[y][z + 1][x] == 1 || world[y][z + 1][x] == 2 || world[y][z + 1][x] == 3){//3 predni
                        pole[2][1][1] = 1;
                    }
                     else if(world[y][z + 1][x] == 0){
                        pole[2][1][1] = 0;
                    }

                    if(world[y][z - 1][x] == 1 || world[y][z - 1][x] == 2 || world[y][z - 1][x] == 3){//4 zadni
                        pole[0][1][1] = 1;
                    }
                     else if(world[y][z - 1][x] == 0){
                        pole[0][1][1] = 0;
                    }

                    if(world[y][z][x + 1] == 1 || world[y][z][x + 1] == 2 || world[y][z][x + 1] == 3){//5 pravy
                        pole[1][1][2] = 1;
                    }
                     else if(world[y][x + 1][x] == 0){
                        pole[1][1][2] = 0;
                    }

                    if(world[y][z][x - 1] == 1|| world[y][z][x - 1] == 2 || world[y][z][x - 1] == 3){//6 levy
                        pole[1][1][0] = 1;
                    }
                     else if(world[y][z][x -1] == 0){
                        pole[1][1][0] = 0;
                    }
                


                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            for (int k = 0; k < 3; k++) {
                                if (pole[j][k][i] != 1) {
                                    Vector3 position_top = (Vector3){sour_x[x] + 0.5f, sour_y[y] + 1.0f, sour_z[z] + 0.5f};
                                    Vector3 position_site1 = (Vector3){sour_x[x] + 0.5f, sour_y[y] + 0.5f, sour_z[z] + 1.0f};
                                    Vector3 position_site2 = (Vector3){sour_x[x] + 0.0f, sour_y[y] + 0.5f, sour_z[z] + 0.5f};
                                    Vector3 position_bottom = (Vector3){sour_x[x] + 0.5f, sour_y[y] + 0.0f, sour_z[z] + 0.5f};
                                    Vector3 position_site3 = (Vector3){sour_x[x] + 0.5f, sour_y[y] + 0.5f, sour_z[z] + 0.0f};
                                    Vector3 position_site4 = (Vector3){sour_x[x] + 1.0f, sour_y[y] + 0.5f, sour_z[z] + 0.5f};

                                    // Top
                                    if (k == 0 && j == 1 && i == 1) {//k == 1 && j == 0 && i == 1
                                        float rotationAngle = 0.0f;
                                        if(world[y][z][x] == 1){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_top;
                                        }
                                        else if(world[y][z][x] == 2){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_bottom;
                                        }
                                        else if(world[y][z][x] == 3){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_cobblestone;
                                        }
                                        DrawModelEx(*model, position_top, (Vector3){0.0f, 0.0f, 0.0f}, rotationAngle, blockSize, WHITE);
                                    }
                                    // Front site
                                    if (k == 1 && j == 2 && i == 1) {
                                        float rotationAngle = 90.0f;
                                        if(world[y][z][x] == 1){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_site;
                                        }
                                        else if(world[y][z][x] == 2){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_dirt_dark;
                                        }
                                        else if(world[y][z][x] == 3){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_cobblestone;
                                        }
                                        DrawModelEx(*model, position_site1, (Vector3){90.0f, 0.0f, 0.0f}, rotationAngle, blockSize, WHITE);
                                    }
                                    // Left site
                                    if (k == 1 && j == 1 && i == 0) {
                                        float rotationAngle = 90.0f;
                                        if(world[y][z][x] == 1){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_site1;
                                        }
                                        else if(world[y][z][x] == 2){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_dirt_darker;
                                        }
                                        else if(world[y][z][x] == 3){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_cobblestone_darker;
                                        }
                                        DrawModelEx(*model, position_site2, (Vector3){0.0f, 0.0f, 1.0f}, rotationAngle, blockSize, WHITE);
                                    }
                                    // Right site
                                    if (k == 1 && j == 1 && i == 2) {
                                        float rotationAngle = -90.0f;
                                        if(world[y][z][x] == 1){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_block_site2;
                                        }
                                        else if(world[y][z][x] == 2){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_bottom;
                                        }
                                        else if(world[y][z][x] == 3){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_cobblestone;
                                        }
                                        DrawModelEx(*model, position_site4, (Vector3){0.0f, 0.0f, 1.0f}, rotationAngle, blockSize, WHITE);
                                    }
                                    // Bottom
                                    if (k == 2 && j == 1 && i == 1) {
                                        float rotationAngle = 180.0f;
                                        if(world[y][z][x] == 1 || world[y][z][x] == 2){
                                        model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_bottom;}

                                        else if(world[y][z][x] == 3){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_cobblestone_darker;
                                        }
                                        DrawModelEx(*model, position_bottom, (Vector3){0.0f, 0.0f, 90.0f}, rotationAngle, blockSize, WHITE);
                                    }
                                    // Back site
                                    if (k == 1 && j == 0 && i == 1) {//k == 0 && j == 1 && i == 1
                                        Vector3 rotationAxis1 = (Vector3){1.0f, 0.0f, 0.0f};
                                        float rotationAngle1 = 270.0f;
                                        if(world[y][z][x] == 1){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_block_site3;
                                        }
                                        else if(world[y][z][x] == 2){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_bottom;
                                        }
                                        else if(world[y][z][x] == 3){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_cobblestone;
                                        }
                                        DrawModelEx(*model, position_site3, rotationAxis1, rotationAngle1, blockSize, WHITE);
                                    }
                                }
                            }
                        }
                    }
                }
                else{
                    for (int z = 0; z < 3; z++) {
                        for (int y = 0; y < 3; y++) {
                            for (int x = 0; x < 3; x++) {
                                pole[z][y][x] = 0;
                            }
                        }

                        pole[1][1][1] = 1;
                    }
                }
            }
        }
    }
}
