/* Helper functions to unclutter main file
 */
#pragma once
#include <stdint.h>
#include "game.h"


// Arduboy functions
void drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap,  
                uint8_t w, uint8_t h, uint8_t color);
void drawRect(int16_t x, int16_t y, uint8_t w, uint8_t h);
void fillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color);
void drawLine(int16_t x0, int16_t y0, uint8_t x1, uint8_t y1); 
void setCursor(int16_t x, int16_t y);
void DrawString(char* msg);

// Game functions
void erase(int16_t x, int16_t y, uint8_t w, uint8_t h);
void drawMap();
void drawGrid();
void drawScore();
void drawGameOver();
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
