#include <raylib.h>
#include <stdbool.h>
#include "block.h"
#include <stdio.h>
#include <math.h>

#define vyska_sveta 20
#define delka_sveta 148
#define sirka_sveta 148
#define M_PI 3.14159265358979323846

#define velikost 0.1f //nemenit

void block(Model *model, Texture2D texture_top, Texture2D texture_site, Texture2D texture_bottom,
           Texture2D texture_site1, Texture2D texture_block_site2, Texture2D texture_block_site3, 
           float *pos, int world[vyska_sveta][delka_sveta][sirka_sveta], float sour_x[], float sour_y[], float sour_z[], Texture2D texture_dirt_dark, Texture2D texture_dirt_darker,
           Texture2D texture_cobblestone, Texture2D texture_cobblestone_dark, Texture2D texture_cobblestone_darker, Vector3 target, Vector3 position, Vector3 direction)
{
    // Mřížka s hodnotami (0 = vzduch, 1 = blok)
    int pole[3][3][3] = {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},  // horni prostredni dolni
        {{0, 0, 0}, {0, 1, 0}, {0, 1, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
    };
    float angle_rad = atan(direction.x);
    float angle_deg_x = angle_rad * (180.0f / M_PI);  

    float angle_rad_z = atan(direction.z);
    float angle_deg_z = angle_rad_z * (180.0f / M_PI); 

    Mesh rectangleMesh = GenMeshPlane(10, 10, 16, 16);
    Model rectangleModel = LoadModelFromMesh(rectangleMesh);

    Vector3 blockSize = (Vector3){velikost, velikost, velikost};

    //if(world[(int) position.y - 1][(int) position.x][(int) position.z] == 1 || world[(int) position.y - 1][(int) position.x][(int) position.z] == 2 || world[(int) position.y - 1][(int) position.x][(int) position.z] == 3){
    //}
    //optimalizace vykreslovani
    int pos_y_opti = 0;
    int pos_x_opti = 0;
    int pos_z_opti = 0;

    int pos_x_opti2 = sirka_sveta;
    int pos_z_opti2 = delka_sveta;
    if(target.y > 9){
        pos_y_opti = 3;
    }
    else{
        pos_y_opti = 0;
    }


    int i = 1;
    int e = 0;        
    int q = 0;
    int j = 1;        
        if (angle_deg_x>= 81.755013f && angle_deg_x <= 85.0f ){
            if(position.x > 0 && position.x <sirka_sveta){
                pos_x_opti = position.x;

            }
        }

        else if(angle_deg_x <= -81.908180f && angle_deg_x >= -85.0f ){
            if(position.x > 0 && position.x <sirka_sveta){
                pos_x_opti2 = position.x;

            }
        }
        else {
            pos_x_opti = 0;
            pos_x_opti2 = sirka_sveta;        
            pos_x_opti = 0;
            pos_z_opti2 = delka_sveta;

        }        
/*                
            
        if(angle_deg_x >= -81.755013f && angle_deg_x <= -85.0f){
            if(position.z > 0 && position.z <delka_sveta){
                pos_z_opti = position.z;
            }
        } 
        if(angle_deg_z <= -30.0f){
            if(position.z > 0 && position.z <delka_sveta){
                pos_z_opti2 = position.z;
            }
        } 

*/      
        if(pos_x_opti2 == sirka_sveta){
            i = 1;
        }
        else{
            i = -1;
        }

        if(pos_z_opti2 == delka_sveta){
            j = 1;
        }
        else{
            j = 0;
        }


        if(pos_x_opti == 0){
            q = 0;
        }
        else{
            q = 1;
        }
    
        if(pos_z_opti == 0){
            e = 0;
        }
        else{
            e = 1;
        }
        if(pos_x_opti == 0){
            if(position.x - 40 >= 0){
            pos_x_opti = position.x - 40;
            }
        }
        if(pos_z_opti == 0){
            if(position.z - 20 >= 0){
            pos_z_opti = position.z - 20;
            }
        }
        if(pos_x_opti2 == sirka_sveta){
            if(position.x + 40 <= sirka_sveta){
            pos_x_opti2 = position.x + 40;
            }
        }
        if(pos_z_opti2 == delka_sveta){
            if(position.z + 20 <= delka_sveta){
            pos_z_opti2 = position.z + 20;
            }
        }
    //-------

    for (int y = 0; y < vyska_sveta - 1; y++) {
        for (int z = pos_z_opti - e; z < pos_z_opti2 - j; z++) {
            for (int x = pos_x_opti - q; x < pos_x_opti2 - i; x++) {//vypis predstavy pole
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

                                        if(world[y + 2][z][x] == 1 || world[y + 2][z][x] == 2 || world[y + 2][z][x] == 3)
                                        {
                                            DrawModelEx(*model, position_top, (Vector3){0.0f, 0.0f, 0.0f}, rotationAngle, blockSize, DARKGRAY);
                                        }

                                        else{
                                            DrawModelEx(*model, position_top, (Vector3){0.0f, 0.0f, 0.0f}, rotationAngle, blockSize, WHITE);

                                        }
                                    }
                                    // Front site
                                    if (k == 1 && j == 2 && i == 1) {
                                        float rotationAngle = 90.0f;
                                        if(world[y][z][x] == 1){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_site;
                                        }
                                        else if(world[y][z][x] == 2){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_bottom;
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
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_bottom;
                                        }
                                        else if(world[y][z][x] == 3){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_cobblestone;
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
                                        DrawModelEx(*model, position_site4, (Vector3){0.0f, 0.0f, 1.0f}, rotationAngle, blockSize, (Color){ 188, 188, 188, 255});
                                    }
                                    // Bottom
                                    if (k == 2 && j == 1 && i == 1) {
                                        float rotationAngle = 180.0f;
                                        if(world[y][z][x] == 1 || world[y][z][x] == 2){
                                        model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_bottom;}

                                        else if(world[y][z][x] == 3){
                                            model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_cobblestone;
                                        }
                                        DrawModelEx(*model, position_bottom, (Vector3){0.0f, 0.0f, 90.0f}, rotationAngle, blockSize, DARKGRAY);
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
                                        DrawModelEx(*model, position_site3, rotationAxis1, rotationAngle1, blockSize, (Color){ 128, 128, 128, 255});
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
