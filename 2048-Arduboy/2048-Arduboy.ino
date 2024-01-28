#include <Arduboy2.h>
#include <EEPROM.h>
#include "Controller.h"
#include "Game.h"
#include "Draw.h"
#include "Defines.h"
#include "Platform.h"
#include "Font.h"

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

void Platform::PutPixel(uint8_t x, uint8_t y, uint8_t colour)
{
  arduboy.drawPixel(x, y, colour);
}

void Platform::DrawBitmap(const uint8_t* bitmap,  int16_t x, int16_t y, uint8_t w,
                uint8_t h, uint8_t color) {
  arduboy.drawBitmap(x, y, bitmap, w, h, color);
}

void Platform::DrawRect(int16_t x, int16_t y, uint8_t w, uint8_t h) {
  arduboy.drawRect(x, y, w, h, WHITE);
}

void Platform::DrawFilledRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color) {
  arduboy.fillRect(x, y, w, h, color);
}

void Platform::DrawCircle(int16_t x0, int16_t y0, uint8_t r) {
  arduboy.drawCircle(x0, y0, r);
}

void Platform::FillCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color) {
  arduboy.fillCircle(x0, y0, r, color);
}

void Platform::FillScreen(uint8_t color) {
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

// From Game.h
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

// From Font.cpp
void Font::PrintString(const char* str, uint8_t line, uint8_t x, uint8_t colour)
{
	uint8_t* screenPtr = arduboy.getBuffer();
	uint8_t xorMask = colour == COLOUR_BLACK ? 0xFF : 0;
	screenPtr += DISPLAY_WIDTH * line + x;

	for (;;)
	{
		char c = *str++;
		if (!c)
			break;

		DrawChar(screenPtr, c, xorMask);
		screenPtr += glyphWidth;
	}
}

void Font::PrintInt(uint16_t val, uint8_t line, uint8_t x, uint8_t colour)
{
	uint8_t* screenPtr = arduboy.getBuffer();
	uint8_t xorMask = colour == COLOUR_BLACK ? 0xFF : 0;
	screenPtr += DISPLAY_WIDTH * line + x;

	if (val == 0)
	{
		DrawChar(screenPtr, '0', xorMask);
		return;
	}

	constexpr int maxDigits = 5;
	char buffer[maxDigits];
	int bufCount = 0;

	for (int n = 0; n < maxDigits && val != 0; n++)
	{
		unsigned char c = val % 10;
		buffer[bufCount++] = '0' + c;
		val = val / 10;
	}

	for (int n = bufCount - 1; n >= 0; n--)
	{
		DrawChar(screenPtr, buffer[n], xorMask);
    screenPtr += glyphWidth;
	}

}

void Font::DrawChar(uint8_t* screenPtr, char c, uint8_t xorMask)
{
  uint16_t idx = CharIdx(c);
	const uint8_t* fontPtr;

  fontPtr = font_images + idx;

	screenPtr[0] = xorMask ^ pgm_read_byte(&fontPtr[0]);
	screenPtr[1] = xorMask ^ pgm_read_byte(&fontPtr[1]);
	screenPtr[2] = xorMask ^ pgm_read_byte(&fontPtr[2]);
	screenPtr[3] = xorMask ^ pgm_read_byte(&fontPtr[3]);

}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab
