#include <Arduboy2.h>
#include "Controller.h"
#include "Game.h"
#include "Draw.h"

Arduboy2 arduboy;

void setup() {
  // put your setup code here, to run once:
  // initiate arduboy instance
  arduboy.begin();
  arduboy.setFrameRate(20);

  while (!arduboy.pressed(A_BUTTON)) {
    arduboy.idle();
  }
  
  // We need the delay before the first button press for a good seed
  arduboy.initRandomSeed();
  NewGame();
}

void loop() {
  // put your main code here, to run repeatedly:
  // pause render until it's time for the next frame
  if (arduboy.nextFrame()) {
    StepGame();
    arduboy.display();
  }
}

// From Controller.h
uint8_t _GetButtons() {
  return arduboy.buttonsState();
}

void Delay(uint16_t milliseconds) {
  arduboy.delayShort(milliseconds);
}

// From Draw.h
// Mapped Arduboy Functions
void DrawBitmap(const uint8_t* bitmap,  int16_t x, int16_t y, uint8_t w,
                uint8_t h, uint8_t color) {
  arduboy.drawBitmap(x, y, bitmap, w, h, WHITE);
}

void DrawRect(int16_t x, int16_t y, uint8_t w, uint8_t h) {
  arduboy.drawRect(x, y, w, h, WHITE);
}

void FillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color) {
  arduboy.fillRect(x, y, w, h, color);
}

void DrawLine(int16_t x0, int16_t y0, uint8_t x1, uint8_t y1) {
  arduboy.drawLine(x0, y0, x1, y1, WHITE);
}

void DrawCircle(int16_t x0, int16_t y0, uint8_t r) {
  arduboy.drawCircle(x0, y0, r);
}

void FillCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color) {
  arduboy.fillCircle(x0, y0, r, color);
}

void FillScreen(uint8_t color) {
  arduboy.fillScreen(color);
}

void SetCursor(int16_t x, int16_t y) {
  arduboy.setCursor(x, y);
}

void DrawString(const char* msg) {
  arduboy.print(msg);
}

void DrawInt(int value) {
  arduboy.print(value);
}

// From game.h
int Random(int min, int max) {
  return random(min, max);
}

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab
