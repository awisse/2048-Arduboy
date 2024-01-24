/* Helper functions to unclutter main file
 */
#include "Draw.h"
#include "HexDigits.h"

#define ERASE_BOARD() EraseRect(BOARD_X, BOARD_Y, TILE_SZ * DIM, TILE_SZ * DIM)

void ClearScreen() {
  FillScreen(_BLACK);
}

void EraseRect(int16_t x, int16_t y, uint8_t w, uint8_t h) {
  FillRect(x, y, w, h, _BLACK);
}

void DrawMap(uint16_t board[DIM][DIM]) {
  int16_t i, value;
  uint8_t color; // For flashing
  // Draw 4x4 map of numbers in board.
  ERASE_BOARD();

  for (i = 0; i < PLACES; i++) {
    if ((value = board[i >> 2][i & 3])) {
      value &= 0x7FFF;
      DrawBitmap(hex_digits[value], 32 + ((i << 2) & 0x30), (i << 4) & 0x30,
                 16, 16, _WHITE);
    }
  }
}

void Flash(uint16_t board[DIM][DIM]) {
  // Flash Squares with highest bit set
  uint16_t value;
  int i;
  for (i = 0; i < PLACES; i++) {
    value = board[i >> 2][i & 3];
#ifdef DEBUG
    DebugPrint(value);
#endif
    if (value & 0x8000 ) {
      //*value &= 0x7FFF;
      DrawBitmap(white_square, 32 + ((i << 2) & 0x30), (i << 4) & 0x30,
                 16, 16, _INVERT);
    }
  }
}

void DrawGameState(bool running) {
    // For testing: Whether "running" is true
  if (running) {
    FillCircle(14, 30, 4, _WHITE);
  } else {
    FillCircle(14, 30, 4, _BLACK);
    DrawCircle(14, 30, 4);
  }
}

void DrawScore(int score, int biggest) {
  EraseRect(100, 8, 27, 8);
  SetCursor(100, 8);
  DrawInt(score);
  EraseRect(100, 32, 27, 8);
  SetCursor(100, 32);
  DrawInt(biggest);

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

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
