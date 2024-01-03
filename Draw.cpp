/* Helper functions to unclutter main file
 */
#include "Defines.h"
#include "Draw.h"
#include "Game.h"
#include "Tiles.h"

#define ERASE_BOARD() EraseRect(BOARD_X, BOARD_Y, TILE_SZ * DIM, TILE_SZ * DIM)

void ClearScreen() {
  FillScreen(_BLACK);
}
void EraseRect(int16_t x, int16_t y, uint8_t w, uint8_t h) {
  FillRect(x, y, w, h, 0);
}

void DrawMap() {
  int16_t i, value;
  // Draw 4x4 map of numbers in board.
  ERASE_BOARD();

  for (i = 0; i < PLACES; i++) {
    if ((value = board[i >> 2][i & 3])) {
      DrawBitmap(bmp_numbers[value], 32 + ((i << 2) & 0x30), (i << 4) & 0x30, 
                 16, 16, 1);
    }
  }
  // DrawGrid();
  GameState.modified = false;
}

void DrawGameState() {
    // For testing: Whether "running" is true
  if (GameState.running) {
    FillCircle(14, 30, 4, _WHITE);
  } else {
    FillCircle(14, 30, 4, _BLACK);
    DrawCircle(14, 30, 4);
  }
}

void DrawScore() {  
}

uint8_t MsgBox(char* msg, uint8_t buttons) {
  /* A modal message box 
   * 1. Centered in the screen. 
   * 2. Up to two lines.
   * 3. Computes its own dimension.
   * 4. Displays one or more buttons.
   * 5. Returns the button pressed.
   */

}

void DrawGameOver() {
  // EraseRect area
  EraseRect(30, 20, 69, 24);
  // Draw double border
  DrawRect(30, 20, 69, 24);
  DrawRect(29, 19, 71, 26);
  // Write "Game Over"
  DrawStringAt(36, 28, "GAME OVER");
}

void DrawStringAt(int16_t x, int16_t y, const char* msg) {
  SetCursor(x, y);
  DrawString(msg);
}

void DrawCoordinates(uint8_t x, uint8_t y) {
  EraseRect(98, 8, 29, 8);
  DrawStringAt(100, 8, "(");
  DrawInt(x);
  DrawString(",");
  DrawInt(y);
  DrawString(")");
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
