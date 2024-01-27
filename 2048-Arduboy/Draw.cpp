/* Helper functions to unclutter main file
 */
#include "Draw.h"
#include "HexDigits.h"
#include "Font.h"

#define ERASE_BOARD() EraseRect(BOARD_X, BOARD_Y, TILE_SZ * DIM, TILE_SZ * DIM)

Font font;

void DrawString(const char* text, uint8_t x, uint8_t line, uint8_t colour) {
  font.PrintString(text, line, x, colour);  
}

void DrawString(const char* text, uint8_t x, uint8_t line) {
  DrawString(text, x, line, COLOUR_WHITE);
}

void DrawInt(uint16_t value, uint8_t x, uint8_t line, uint8_t colour) {
  font.PrintInt(value, line, x, colour);
}

void DrawInt(uint16_t value, uint8_t x, uint8_t line) {
  DrawInt(value, x, line, COLOUR_WHITE);
}

void InitScreen() {

  FillScreen(COLOUR_BLACK);

  DrawString("Score", SCORE_X, SCORE_LINE);
  DrawString("HiScore", SCORE_X, HIGHSCORE_LINE);
  DrawString("Max", SCORE_X, MAX_LINE);
}

void EraseRect(int16_t x, int16_t y, uint8_t w, uint8_t h) {
  DrawFilledRect(x, y, w, h, COLOUR_BLACK);
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
                 16, 16, COLOUR_WHITE);
    }
  }
}

void Flash(uint16_t board[DIM][DIM]) {
  // Flash Squares with highest bit set
  uint16_t value;
  int i;
  for (i = 0; i < PLACES; i++) {
    value = board[i >> 2][i & 3];
    if (value & 0x8000 ) {
      //*value &= 0x7FFF;
      DrawBitmap(white_square, 32 + ((i << 2) & 0x30), (i << 4) & 0x30,
                 16, 16, COLOUR_INVERT);
    }
  }
}

void DrawGameState(bool running) {
    // For testing: Whether "running" is true
  if (running) {
    FillCircle(14, 30, 4, COLOUR_WHITE);
  } else {
    FillCircle(14, 30, 4, COLOUR_BLACK);
    DrawCircle(14, 30, 4);
  }
}

void DrawScore(unsigned int score, unsigned int highscore, unsigned int biggest) {
  EraseRect(SCORE_X, (SCORE_LINE + 1) * FONT_STEP, DISPLAY_WIDTH - SCORE_X, FONT_STEP);
  DrawInt(score, SCORE_X, SCORE_LINE + 1);

  EraseRect(SCORE_X, (HIGHSCORE_LINE + 1) * FONT_STEP, DISPLAY_WIDTH - SCORE_X, FONT_STEP);
  DrawInt(highscore, SCORE_X, HIGHSCORE_LINE + 1);

  EraseRect(SCORE_X, (MAX_LINE + 1) * FONT_STEP, DISPLAY_WIDTH - SCORE_X, FONT_STEP);
  DrawInt(biggest, SCORE_X, MAX_LINE + 1);

}

void DrawGameOver() {
  // EraseRect area
  EraseRect(29, 8 * OVER_LINE - 4, 69, 15);
  // Draw double border
  DrawRect(29, 8 * OVER_LINE - 4, 69, 15);
  DrawRect(28, 8 * OVER_LINE - 5, 71, 17);
  // Write "Game Over"
  DrawString("GAME OVER", (DISPLAY_WIDTH - 9 * 4) / 2, OVER_LINE);
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
