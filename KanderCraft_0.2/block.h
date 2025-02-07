// block.h
#ifndef BLOCK_H
#define BLOCK_H

#define vyska_sveta 10
#define delka_sveta 48
#define sirka_sveta 48

#include <raylib.h>

void block(Model *model, Texture2D texture_top, Texture2D texture_site, 
    Texture2D texture_bottom, Texture2D texture_site1,Texture2D texture_block_site2, 
    Texture2D texture_block_site3, float *pos, int world[vyska_sveta][delka_sveta][sirka_sveta], 
    float sour_x[], float sour_y[], float sour_z[], Texture2D texture_dirt_dark, Texture2D texture_dirt_darker,
    Texture2D texture_cobblestone, Texture2D texture_cobblestone_dark, Texture2D texture_cobblestone_darker);

#endif
