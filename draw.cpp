/* Helper functions to unclutter main file
 */
#include "draw.h"
#include "sprites.h"

void erase(int16_t x, int16_t y, uint8_t w, uint8_t h) {
  fillRect(x, y, w, h, 0);
}

void drawMap() {
  int16_t i, value;
  // Draw 4x4 map of numbers in board.
  erase(32, 0, 64, 64);

  for (i = 0; i < PLACES; i++) {
    if ((value = board[i >> 2][i & 3])) {
      drawBitmap(32 + ((i << 2) & 0x30), (i << 4) & 0x30, numbers[value], 
                 16, 16, 1);
    }
  }
  new_piece = 0;
}

void drawGrid() {
  // Draw the 4 x 4 grid in the middle of the screen
  int i;
  drawLine(32, 0, 32, 63);
  drawLine(96, 0, 96, 63);
  for (i = 16; i < 64; i += 16) {
    drawLine(32, i, 96, i);
    drawLine(32 + i, 0, 32 + i, 63);
  }
}

void drawScore() {
  
}

void drawGameOver() {
  // Erase area
  erase(30, 20, 69, 24);
  // Draw double border
  drawRect(30, 20, 69, 24);
  drawRect(29, 19, 71, 26);
  // Write "Game Over"
  setCursor(36, 28);
  drawString("GAME OVER");
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
