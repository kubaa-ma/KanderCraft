#include <raylib.h>
#include "block.h"
#include <stdio.h>
#include "world.h"
#include <math.h>
#include <stdlib.h>
#define M_PI 3.14159265358979323846
#define MAX_DIGITS 10

#define vyska_sveta 20
#define delka_sveta 148
#define sirka_sveta 148

#define WIDTH 1748
#define HEIGHT 988

Vector3 NormalizeVector(Vector3 v)
{
    float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); //radial - > degree
    if (length == 0.0f) return (Vector3){ 0, 0, 0 };
    return (Vector3){ v.x / length, v.y / length, v.z / length };
}

void save_world(int world[vyska_sveta][delka_sveta][sirka_sveta]) {
    FILE *file = fopen("world.dat", "wb");
    if (!file) {
        printf("Chyba: Nepodařilo se otevřít soubor pro zápis!\n");
        return;
    }

    fwrite(world, sizeof(int), vyska_sveta * delka_sveta * sirka_sveta, file);
    fclose(file);
    printf("Svět uložen!\n");
}

void load_world(int world[vyska_sveta][delka_sveta][sirka_sveta]) {
    FILE *file = fopen("world.dat", "rb");
    if (!file) {
        printf("Chyba: Nepodařilo se otevřít soubor pro čtení!\n");
        return;
    }

    fread(world, sizeof(int), vyska_sveta * delka_sveta * sirka_sveta, file);
    fclose(file);
    printf("Svět načten!\n");
}


int main()
{   
    //---------------------------//
    float pos = 2; 
    int xPos;
    int yPos;
    int zPos;
    int b_pos = 3;
    int state = 0;
    int t = 1;
    int jump = 0;
    char souradnice[68];
    float camera_height = 5.75f; 
    int world[vyska_sveta][delka_sveta][sirka_sveta];            
    float sour_x[sirka_sveta];
    float sour_y[vyska_sveta];
    float sour_z[delka_sveta];
    char inputText[MAX_DIGITS + 1] = "";
    int letterCount = 0;
    int inputValue = 0;
    //-------------------------//

    for (int z = 0; z < delka_sveta - 1; z++) { //load coordiation
        for (int y = 0; y < vyska_sveta - 1; y++) {
            for (int x = 0; x < sirka_sveta - 1; x++) {
                sour_x[x] = x;
                sour_y[y] = y;
                sour_z[z] = z;
            }
        }
    }

    InitWindow(WIDTH, HEIGHT, "KanderCraft");
    //-------------------------------------------------------------//
    Texture2D texture_block_top = LoadTexture("textu/texture1.png");
    Texture2D texture_block_site = LoadTexture("textu/texture2.png");
    Texture2D texture_block_bottom = LoadTexture("textu/texture3.png");
    Texture2D texture_block_site1 = LoadTexture("textu/texture4.png");
    Texture2D texture_block_site2 = LoadTexture("textu/texture5.png");
    Texture2D texture_block_site3 = LoadTexture("textu/texture6.png");
    Texture2D texture_backgnound = LoadTexture("textu/background.png");
    Texture2D texture_dirt_dark = LoadTexture("textu/texture3_dark.png");
    Texture2D texture_dirt_darker = LoadTexture("textu/texture3_darker.png");   //texture load
    Texture2D texture_cobblestone = LoadTexture("textu/cobblestone1.png");
    Texture2D texture_cobblestone_dark = LoadTexture("textu/cobblestone2.png");
    Texture2D texture_cobblestone_darker = LoadTexture("textu/cobblestone.png");
    //-------------------------------------------------------------------------//

    //------------------------------------------------------//
    Mesh rectangleMesh = GenMeshPlane(10, 10, 16, 16);
    Model rectangleModel = LoadModelFromMesh(rectangleMesh);
    Font font_regular = LoadFont("textu/minecraft_font.ttf"); //creating mesh model
    //------------------------------------------------------//
    
    
    //------------------------------------------------------//
    Camera camera = { 0 };
    camera.position = (Vector3){ 5.0f, 14.75f, 5.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; 
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; 
    camera.fovy = 54.0f;//48.0f
    camera.projection = CAMERA_PERSPECTIVE;
    Vector2 screenCenter = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    Vector3 cameralast = camera.position;
    //------------------------------------------------------//

    int reserve = 800;
    char targetText[64];

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();
        if (mousePos.x < screenCenter.x - reserve) {
            SetMousePosition(screenCenter.x - reserve, mousePos.y);
        } else if (mousePos.x > screenCenter.x + reserve) {
            SetMousePosition(screenCenter.x + reserve, mousePos.y);
        }

        if (mousePos.y < screenCenter.y - reserve) {
            SetMousePosition(mousePos.x, screenCenter.y - reserve);
        } else if (mousePos.y > screenCenter.y + reserve) {
            SetMousePosition(mousePos.x, screenCenter.y + reserve);
        }
        if (mousePos.x <= screenCenter.x - reserve || mousePos.x >= screenCenter.x + reserve ||
            mousePos.y <= screenCenter.y - reserve || mousePos.y >= screenCenter.y + reserve) {
            SetMousePosition(screenCenter.x, screenCenter.y);
        }
        HideCursor();
       if(state == 0)
       {

            BeginDrawing();
            ClearBackground(WHITE);
            float i = 10;

            
            DrawTexture(texture_backgnound, 0, 0, WHITE);
            DrawTextPro(font_regular,"KanderCraft 0.4 - Minecraft Clone by Jakub Jansa (Kander_14) All Rights Reserved 2025 early acces", (Vector2){170, 947}, (Vector2){0,0}, 0, 28, 2.0f, WHITE);
            DrawTextPro(font_regular,"Have Fun!", (Vector2){1248, 58-10}, (Vector2){0,0}, i, 38, 2.0f, YELLOW);
            DrawTextPro(font_regular,"Play - [ENTER]\nWorld 148 x 148!\nRendering distance 40x20 blocks", (Vector2){WIDTH / 2 - 248, HEIGHT / 2}, (Vector2){10,0}, 0, 47, 2.0f, WHITE);

            if (IsKeyPressed(KEY_ENTER)){
                state = 2;
            }
        
            EndDrawing();
       }
       else if(state == 2){
        BeginDrawing();
        ClearBackground(WHITE);
        float i = 10;
        DrawTexture(texture_backgnound, 0, 0, WHITE);
        DrawTextPro(font_regular,"KanderCraft 0.4 - Minecraft Clone by Jakub Jansa (Kander_14) All Rights Reserved 2025 early acces", (Vector2){170, 947}, (Vector2){0,0}, 0, 28, 2.0f, WHITE);
        DrawTextPro(font_regular,"A. Generate New world\nB.Play Last world \n(To save the world save the file world.dat", (Vector2){WIDTH / 2 - 248, HEIGHT / 2}, (Vector2){10,0}, 0, 47, 2.0f, WHITE);
        if(IsKeyPressed(KEY_A)){
        state = 3;
        }
        if(IsKeyPressed(KEY_B)){
        load_world(world);
        state = 1;
        }
        EndDrawing();


       }
       else if(state == 3){
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(texture_backgnound, 0, 0, WHITE);
        DrawTextPro(font_regular,"KanderCraft 0.4 - Minecraft Clone by Jakub Jansa (Kander_14) All Rights Reserved 2025 early acces", (Vector2){170, 947}, (Vector2){0,0}, 0, 28, 2.0f, WHITE);
        DrawTextPro(font_regular,"Generating Seed: ", (Vector2){WIDTH / 2 - 248, HEIGHT / 2}, (Vector2){10,0}, 0, 47, 2.0f, WHITE);

        int key = GetCharPressed();

        while (key > 0) {
            if ((key >= '0' && key <= '9') && (letterCount < MAX_DIGITS-1)) {
                inputText[letterCount] = (char)key;
                letterCount++;
                inputText[letterCount] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (letterCount > 0) {
                letterCount--;
                inputText[letterCount] = '\0';
            }
        }

        inputValue = (letterCount > 0) ? atoi(inputText) : 0;

        DrawText(inputText, 50, 130, 20, BLACK);
        DrawRectangleLines(45, 125, 250, 30, BLACK);
        
        char outputText[50];
        sprintf(outputText, "\nValue: %d", inputValue);
        DrawTextPro(font_regular,outputText, (Vector2){WIDTH / 2 - 248, HEIGHT / 2}, (Vector2){10,0}, 0, 47, 2.0f, WHITE);
        EndDrawing();
        if(IsKeyPressed(KEY_ENTER)){
            if(inputValue != 69){
            world_generator_hi_hi(world, inputValue);
            state = 1;}

            else{
                state = 4;
            }
        }    
        }
        else if(state == 4){
            BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(texture_backgnound, 0, 0, WHITE);
            DrawTextPro(font_regular,"KanderCraft 0.4 - Minecraft Clone by Jakub Jansa (Kander_14) All Rights Reserved 2025 early acces", (Vector2){170, 947}, (Vector2){0,0}, 0, 28, 2.0f, WHITE);
            DrawTextPro(font_regular,"\nO_O", (Vector2){WIDTH / 2 - 188, HEIGHT / 2}, (Vector2){10,0}, 0, 47, 2.0f, WHITE);
            DrawTextPro(font_regular,"\n\n\n Press to continue [E]", (Vector2){WIDTH / 2 - 248, HEIGHT / 2}, (Vector2){10,0}, 0, 47, 2.0f, WHITE);

            if(IsKeyPressed(KEY_E)){
                world_generator_hi_hi(world, inputValue);
                state = 1;
            }
            EndDrawing();
        }
       
       else if(state == 1)
       {    
            Vector3 direction = (Vector3){ 
                camera.target.x - camera.position.x,
                camera.target.y - camera.position.y,
                camera.target.z - camera.position.z
            };    

            float angle_rad = atan(direction.x);
            float angle_deg_x = angle_rad * (180.0f / M_PI);  
            Vector3 normalizedDirection = NormalizeVector(direction);
            SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
            UpdateCamera(&camera, CAMERA_FIRST_PERSON);

            BeginDrawing();

            ClearBackground((Color){135, 208, 234, 100});

            BeginMode3D(camera);  
            block(&rectangleModel, texture_block_top, texture_block_site, texture_block_bottom, texture_block_site1,
            texture_block_site2, texture_block_site3, &pos, world, sour_x, sour_y, sour_z,texture_dirt_dark, texture_dirt_darker, 
            texture_cobblestone, texture_cobblestone_dark, texture_cobblestone_darker, camera.target, camera.position, direction);
            //DrawGrid(48, 1);        
            Vector3 camPos = camera.position;

            EndMode3D();

            xPos = (int)camPos.x;
            yPos = (int)camPos.y;
            zPos = (int)camPos.z;

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if(xPos>=sirka_sveta){
                    xPos = sirka_sveta;
                }
                if(zPos>=delka_sveta){
                    zPos = delka_sveta;
                }
                world[b_pos][zPos][xPos] = 0;
            }
            if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
                if(t == 1){
                world[b_pos][zPos][xPos] = 2;} //hlina
                else if(t == 2){
                world[b_pos][zPos][xPos] = 3;} //kameni
            }

            if(GetMouseWheelMove()){
                if(t == 1){
                    t = 2;
                }
                else if(t == 2){
                    t = 1;
                }
            }
            if(IsKeyPressed(KEY_U)){
                if(b_pos < vyska_sveta - 3){
                b_pos+=1;
            }
            }
            if(IsKeyPressed(KEY_L)){
                if(b_pos > 0){
                b_pos-=1;
                }
            }
            if(t == 1){
                DrawTextPro(font_regular,"\n\n\n\n\n\n\n\n\nBlock: Dirt", (Vector2){10, 10}, (Vector2){0,0}, 0, 28, 2.0f, YELLOW);
            }
            else if(t == 2){
            DrawTextPro(font_regular,"\n\n\n\n\n\n\n\n\nBlock: cobblestone", (Vector2){10, 10}, (Vector2){0,0}, 0, 28, 2.0f, YELLOW);

            }

            if(//Kolikze
                world[(int) camera.position.y - 2][(int) camera.position.z][(int) camera.position.x] == 1 ||
                world[(int) camera.position.y - 2][(int) camera.position.z][(int) camera.position.x] == 2 ||
                world[(int) camera.position.y - 2][(int) camera.position.z][(int) camera.position.x] == 3){


            }
            else{
                if(world[(int) camera.position.y - 2][(int) camera.position.z][(int) camera.position.x] != 1 ||
                world[(int) camera.position.y - 2][(int) camera.position.z][(int) camera.position.x] != 2 ||
                world[(int) camera.position.y - 2][(int) camera.position.z][(int) camera.position.x] != 3){
                camera.position.y-=0.1;}
            }
           
            if(IsKeyPressed(KEY_SPACE)){
                jump = 1;
            }
            if(jump > 0){
                if(jump <= 9){  
                    camera.position.y+=0.2;
                    jump++;
                }
                else{
                    jump = 0;
                }
            }
            

            if(//Kolikze
                world[(int) camera.position.y - 1][(int) camera.position.z][(int) camera.position.x + 1] == 1 ||
                world[(int) camera.position.y - 1][(int) camera.position.z][(int) camera.position.x + 1] == 2 ||
                world[(int) camera.position.y - 1][(int) camera.position.z][(int) camera.position.x + 1] == 3 || 
                world[(int) camera.position.y][(int) camera.position.z][(int) camera.position.x + 1] == 1 ||
                world[(int) camera.position.y][(int) camera.position.z][(int) camera.position.x + 1] == 2 ||
                world[(int) camera.position.y][(int) camera.position.z][(int) camera.position.x + 1] == 3){
                }


            DrawTextPro(font_regular,"KUBOSOFT 2025\nKanderCraft 0.4 Jakub Jansa\nMinecraft Clone\n\nLeft Button break a block\nRight button place block(mouse wheel to switch block)\n u/l set upper or lower y axis\nThe block is placed under the player\nBlock placing mechanism will be fix in newer version\n", (Vector2){10, 10}, (Vector2){0,0}, 0, 28, 2.0f, WHITE);
            sprintf(souradnice, "\n\n\n\n\n\n\n\n\n\nx.%f\tz.%f\ty.%f\nBLOCK PLACE HIGHT y.%d", camera.position.x, camera.position.z, camera.position.y, b_pos);
            DrawTextPro(font_regular,souradnice, (Vector2){10, 10}, (Vector2){0,0}, 0, 28, 2.0f, WHITE);

            EndDrawing();
        
        }

           
    }
    save_world(world);    
    UnloadModel(rectangleModel);
            UnloadTexture(texture_block_top);
            UnloadTexture(texture_block_site);
            UnloadTexture(texture_block_bottom);
            UnloadTexture(texture_backgnound);
            UnloadTexture(texture_dirt_dark);
            UnloadTexture(texture_dirt_darker);
            UnloadTexture(texture_cobblestone);
            UnloadTexture(texture_cobblestone_dark);
            UnloadTexture(texture_cobblestone_darker);

        CloseWindow();  

    return 0;
}
