#include <raylib.h>
#include "block.h"
#include <stdio.h>
#include "world.h"


#define vyska_sveta 10
#define delka_sveta 48
#define sirka_sveta 48

#define WIDTH 1748
#define HEIGHT 988


int main()
{
    float pos = 2;
    int xPos;
    int yPos;
    int zPos;
    int b_pos = 3;
    int state = 0;
    int world[vyska_sveta][delka_sveta][sirka_sveta];
    world_generator_hi_hi(world);
    float sour_x[sirka_sveta];
    float sour_y[vyska_sveta];
    float sour_z[delka_sveta];

    for (int z = 0; z < delka_sveta - 1; z++) {
        for (int y = 0; y < vyska_sveta - 1; y++) {
            for (int x = 0; x < sirka_sveta - 1; x++) {
                sour_x[x] = x;
                sour_y[y] = y;
                sour_z[z] = z;
            }
        }
    }

    InitWindow(WIDTH, HEIGHT, "KanderCraft");

    Texture2D texture_block_top = LoadTexture("textu/texture1.png");
    Texture2D texture_block_site = LoadTexture("textu/texture2.png");
    Texture2D texture_block_bottom = LoadTexture("textu/texture3.png");
    Texture2D texture_block_site1 = LoadTexture("textu/texture4.png");
    Texture2D texture_block_site2 = LoadTexture("textu/texture5.png");
    Texture2D texture_block_site3 = LoadTexture("textu/texture6.png");
    Texture2D texture_backgnound = LoadTexture("textu/background.png");
    Mesh rectangleMesh = GenMeshPlane(10, 10, 16, 16);
    Model rectangleModel = LoadModelFromMesh(rectangleMesh); // Vytvoření modelu z mesh
    Font font_regular = LoadFont("textu/minecraft_font.ttf");

    Camera camera = { 0 };
    camera.position = (Vector3){ 5.0f, 5.0f, 5.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; 
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; 
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
       if(state == 0)
       {
            BeginDrawing();
            ClearBackground(WHITE);
            float i = 10;

            
            DrawTexture(texture_backgnound, 0, 0, WHITE);
            DrawTextPro(font_regular,"KanderCraft 0.1 - Minecraft Clone by Jakub Jansa (Kander_14) All Rights Reserved 2025 early acces", (Vector2){170, 947}, (Vector2){0,0}, 0, 28, 2.0f, WHITE);
            DrawTextPro(font_regular,"Have Fun!", (Vector2){1248, 58-10}, (Vector2){0,0}, i, 38, 2.0f, YELLOW);
            DrawTextPro(font_regular,"Play - [ENTER]", (Vector2){WIDTH / 2 - 248, HEIGHT / 2}, (Vector2){10,0}, 0, 47, 2.0f, WHITE);

            if (IsKeyPressed(KEY_ENTER)){
                state = 1;
            }
        
            EndDrawing();
       }
       else if(state == 1)
       {
            UpdateCamera(&camera, CAMERA_FREE);

            BeginDrawing();

            ClearBackground((Color){135, 208, 234, 100});

            BeginMode3D(camera);  
            block(&rectangleModel, texture_block_top, texture_block_site, texture_block_bottom, texture_block_site1,
            texture_block_site2, texture_block_site3, &pos, world, sour_x, sour_y, sour_z);
            //DrawGrid(48, 1);        

            EndMode3D();
            Vector3 camPos = camera.position;

            xPos = (int)camPos.x;
            yPos = (int)camPos.y;
            zPos = (int)camPos.z;

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if(xPos>=48){
                    xPos = 48;
                }
                if(zPos>=48){
                    zPos = 48;
                }
                world[b_pos][zPos][xPos] = 0;
            }
            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                world[b_pos][zPos][xPos] = 2;
            }
            if(IsKeyPressed(KEY_U)){
                b_pos+=1;
            }
            if(IsKeyPressed(KEY_L)){
                b_pos-=1;
            }
            DrawTextPro(font_regular,"KanderCraft 0.1 Jakub Jansa\nMinecraft Clone\n\nLeft Button break a block\nRight button place block\n u/l set upper or lower y axis but in hight 10 you will be off the array and game crash\nThe block is placed under the player\nBlock placing mechanism will be fix in new version\nYou can look inside the block and see the optimalisation :)", (Vector2){10, 10}, (Vector2){0,0}, 0, 28, 2.0f, WHITE);

            EndDrawing();
        
        }

           
    }    
    UnloadModel(rectangleModel);
            UnloadTexture(texture_block_top);
            UnloadTexture(texture_block_site);
            UnloadTexture(texture_block_bottom);
            UnloadTexture(texture_backgnound);
        CloseWindow();  

    return 0;
}
