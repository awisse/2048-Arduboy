#pragma once

#include <stdint.h>


// Mapped Arduboy functions
void DrawBitmap(const uint8_t* bitmap, int16_t x, int16_t y,  
                uint8_t w, uint8_t h, uint8_t color);
void DrawRect(int16_t x, int16_t y, uint8_t w, uint8_t h);
void FillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color);
void DrawLine(int16_t x0, int16_t y0, uint8_t x1, uint8_t y1); 
void DrawCircle(int16_t x0, int16_t y0, uint8_t r);
void FillCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color);
void FillScreen(uint8_t color);
void SetCursor(int16_t x, int16_t y);
void DrawString(const char* msg);
void DrawInt(int value);

// Game functions
void ClearScreen();
void EraseRect(int16_t x, int16_t y, uint8_t w, uint8_t h);
void DrawMap();
void DrawGrid();
void DrawGameState();
void DrawScore(int score);
uint8_t MsgBox(char* msg, uint8_t buttons);
void DrawGameOver();
void DrawStringAt(int16_t x, int16_t y, const char* msg);
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
