/* Helper functions to unclutter main file
 */
#include "Draw.h"
#include "Defines.h"

const uint8_t bmp_numbers[16][32] PROGMEM = 
{
#include "Numbers.h"
};

void EraseRect(int16_t x, int16_t y, uint8_t w, uint8_t h) {
  FillRect(x, y, w, h, 0);
}

void DrawMap() {
  int16_t i, value;
  // Draw 4x4 map of numbers in board.
  EraseRect(32, 0, 64, 64);

  for (i = 0; i < PLACES; i++) {
    if ((value = board[i >> 2][i & 3])) {
      DrawBitmap(bmp_numbers[value], 32 + ((i << 2) & 0x30), (i << 4) & 0x30, 
                 16, 16, 1);
    }
  }
  GameState.new_piece = 0;
}

void DrawGrid() {
  // Draw the 4 x 4 grid in the middle of the screen
  int i;
  DrawLine(32, 0, 32, 63);
  DrawLine(96, 0, 96, 63);
  for (i = 16; i < 64; i += 16) {
    DrawLine(32, i, 96, i);
    DrawLine(32 + i, 0, 32 + i, 63);
  }
}

void DrawScore() {
  
}

void DrawGameOver() {
  // EraseRect area
  EraseRect(30, 20, 69, 24);
  // Draw double border
  DrawRect(30, 20, 69, 24);
  DrawRect(29, 19, 71, 26);
  // Write "Game Over"
  SetCursor(36, 28);
  DrawString("GAME OVER");
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
