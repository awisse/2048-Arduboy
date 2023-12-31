#include <Arduboy2.h>
#include "game.h"
#include "draw.h"

Arduboy2 arduboy;

void setup() {
  // put your setup code here, to run once:
  // initiate arduboy instance
  arduboy.begin();
  arduboy.setFrameRate(20);

  while (!arduboy.pressed(A_BUTTON)) {
    arduboy.idle();
  }
  
  arduboy.clear();
  
  // We need the delay before the first button press for a good seed
  arduboy.initRandomSeed();
  newGame();
}

void loop() {
  // put your main code here, to run repeatedly:
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;
  
  // For testing: Whether "running" is true
  if (running) {
    arduboy.fillCircle(14, 30, 4);
    if (new_piece) drawMap();
  } else {
    arduboy.fillCircle(14, 30, 4, BLACK);
    arduboy.drawCircle(14, 30, 4);
  }
  if (arduboy.pressed(A_BUTTON)) {
    newPiece();
    // Unbounce the button
    delay(100);
  }

  arduboy.display();
  arduboy.idle();
}

void drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap,  uint8_t w,
                uint8_t h, uint8_t color) {
  arduboy.drawBitmap(x, y, w, bitmap, h, WHITE);
}

void drawRect(int16_t x, int16_t y, uint8_t w, uint8_t h) {
  arduboy.drawRect(x, y, w, h, WHITE);
}

void fillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color) {
  arduboy.fillRect(x, y, w, h, color);
}

void drawLine(int16_t x0, int16_t y0, uint8_t x1, uint8_t y1) {
  arduboy.drawLine(x0, y0, x1, y1, WHITE);
}

void setCursor(int16_t x, int16_t y) {
  arduboy.setCursor(x, y);
}

void drawString(char* msg) {
  arduboy.print(msg);
}


// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab
