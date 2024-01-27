#include <Arduboy2.h>
#include <EEPROM.h>
#include "Controller.h"
#include "Game.h"
#include "Draw.h"
#include "Defines.h"
#include "Platform.h"

#ifdef DEBUG
#include "debug.h"
#endif

Arduboy2Base arduboy;
#ifdef DEBUG
static int i;
#endif

void setup() {
  // put your setup code here, to run once:
  // initiate arduboy instance
  arduboy.begin();
  arduboy.setFrameRate(20);

  while (!arduboy.pressed(A_BUTTON)) {
    arduboy.idle();
  }

  #ifdef DEBUG
  Serial.begin(9600);
  i = 0;
  #endif

  // We need the delay before the first button press for a good seed
  arduboy.initRandomSeed();
  InitGame();
}

void loop() {
  // put your main code here, to run repeatedly:
  // pause render until it's time for the next frame
  if (arduboy.nextFrame()) {
    arduboy.pollButtons();
    StepGame();
    arduboy.display();
  }
}

// From Controller.h
bool JustPressed(uint8_t button) {
  return arduboy.justPressed(button);
}

bool JustReleased(uint8_t button) {
  return arduboy.justReleased(button);
}

uint8_t ButtonState() {
  return arduboy.buttonsState();
}
// From Draw.h
// Mapped Arduboy Functions

void PutPixel(uint8_t x, uint8_t y, uint8_t colour)
{
  arduboy.drawPixel(x, y, colour);
}

void DrawBitmap(const uint8_t* bitmap,  int16_t x, int16_t y, uint8_t w,
                uint8_t h, uint8_t color) {
  arduboy.drawBitmap(x, y, bitmap, w, h, color);
}

void DrawRect(int16_t x, int16_t y, uint8_t w, uint8_t h) {
  arduboy.drawRect(x, y, w, h, WHITE);
}

void DrawFilledRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color) {
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

#ifdef DEBUG
void DebugPrint(uint16_t value) {
  Serial.print(value, HEX);
  Serial.print(":");
  if (++i % 4 == 0) {
    Serial.println(" =");
  }
}

void DebugPrint(char* text) {
  Serial.println(" =");
  Serial.println(text);
  i = 0;
}
#endif

// From game.h
int Random(int min, int max) {
  return random(min, max);
}
unsigned long Millis() {
  return millis();
}

#define EEP(x) EEPROM[EEPROM_STORAGE_SPACE_START + x]

uint8_t ToEEPROM(uint8_t *bytes, int offset, int length) {
  int i;
  if (offset < 0) {
    return WrongOffset;
  }
  if (EEPROM_STORAGE_SPACE_START + 4 + offset + length > EEPROM.length()) {
    return TooBig;
  }
  // Write Game to EEPROM
  // Write signature of game
  EEP(0) = '2';
  EEP(1) = '0';
  EEP(2) = '4';
  EEP(3) = '8';

  for (i = 0; i < length; i++) {
    EEP(i + 4 + offset) = bytes[i];
  }
  return Saved;
}

uint8_t FromEEPROM(uint8_t *bytes, int offset, int length) {
  // Get Game from EEPROM
  int i = EEPROM_STORAGE_SPACE_START;
  if (i + offset < 0) {
    return WrongOffset;
  }
  if (i + 4 + offset + length > EEPROM.length()) {
    return TooBig; // Can't read from here
  }
  // Read data from EEPROM. Return 1 if no game saved.
  if (EEPROM[i++] != '2') return NotSaved;
  if (EEPROM[i++] != '0') return NotSaved;
  if (EEPROM[i++] != '4') return NotSaved;
  if (EEPROM[i++] != '8') return NotSaved;

  for (i = 0; i < length; i++) {
    bytes[i] = EEP(i + 4 + offset);
  }
  return Saved;
}

// From Platform.h
static uint8_t* Platform::GetScreenBuffer() {
  return arduboy.getBuffer();
}

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab
