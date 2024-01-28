#pragma once

#include <stdint.h>
#include "Defines.h"

// Mapped Arduboy functions
void DrawString(const char* text, uint8_t x, uint8_t line, uint8_t colour);
void DrawString(const char* text, uint8_t x, uint8_t line);
void DrawInt(uint16_t value, uint8_t x, uint8_t line, uint8_t colour);
void DrawInt(uint16_t value, uint8_t x, uint8_t line);

// Game functions
void InitScreen();
void DrawLabels();
void EraseRect(int16_t x, int16_t y, uint8_t w, uint8_t h);
void DrawMap(uint16_t board[DIM][DIM]);
void Flash(uint16_t board[DIM][DIM]);
void DrawGameState(bool running);
void DrawScore(unsigned int score, unsigned int highscore, unsigned int biggest);
uint8_t MsgBox(char* msg, uint8_t buttons);
void DrawGameOver();
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
