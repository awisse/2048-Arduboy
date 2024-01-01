#pragma once

#include <stdint.h>
#include "Game.h"


// Arduboy functions
void DrawBitmap(const uint8_t* bitmap, int16_t x, int16_t y,  
                uint8_t w, uint8_t h, uint8_t color);
void DrawRect(int16_t x, int16_t y, uint8_t w, uint8_t h);
void FillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color);
void DrawLine(int16_t x0, int16_t y0, uint8_t x1, uint8_t y1); 
void SetCursor(int16_t x, int16_t y);
void DrawString(char* msg);

// Game functions
void EraseRect(int16_t x, int16_t y, uint8_t w, uint8_t h);
void DrawMap();
void DrawGrid();
void DrawScore();
void DrawGameOver();
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
