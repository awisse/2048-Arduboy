#pragma once

#include <stdint.h>

class Platform
{
public:
	static uint8_t ButtonState();
	/* static void SetLED(uint8_t r, uint8_t g, uint8_t b); */
	static uint8_t* GetScreenBuffer();
  static void PutPixel(uint8_t x, uint8_t y, uint8_t colour);
  static void DrawBitmap(const uint8_t* bitmap, int16_t x, int16_t y,
                  uint8_t w, uint8_t h, uint8_t colour);
  static void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t colour);
  static void DrawRect(int16_t x, int16_t y, uint8_t w, uint8_t h);
  static void DrawFilledRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t colour);
  static void DrawCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t colour);
  static void FillCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t colour);
  static void FillScreen(uint8_t colour);
  static void Clear();

  static uint8_t ToEEPROM(uint8_t *bytes, int offset, int length);
  static uint8_t FromEEPROM(uint8_t *bytes, int offset, int length);
	/* static void PlaySound(const uint16_t* audioPattern); */
	/* static bool IsAudioEnabled(); */
	/* static void SetAudioEnabled(bool isEnabled); */

	/* static void ExpectLoadDelay(); */
	
	/* static void FillScreen(uint8_t col); */
	/* static void PutPixel(uint8_t x, uint8_t y, uint8_t colour); */
	/* static void DrawBitmap(int16_t x, int16_t y, const uint8_t *bitmap); */
	/* static void DrawSolidBitmap(int16_t x, int16_t y, const uint8_t *bitmap); */
	/* static void DrawSprite(int16_t x, int16_t y, const uint8_t *bitmap, const uint8_t *mask, uint8_t frame, uint8_t mask_frame); */
	/* static void DrawSprite(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame); */	

	/* static void DrawVLine(uint8_t x, int8_t y1, int8_t y2, uint8_t pattern); */
	/* static void DrawBackground(); */
};
// vim:ft=cpp
