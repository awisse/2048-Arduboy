#include <avr/pgmspace.h>
#include "Defines.h"
/* #include for PROGMEM
 * Sixteen 16x16 bitmaps: 0,1,...,E,F */
const uint8_t hex_digits[MAX_VALUE + 1][32] PROGMEM =
{
  // 0
  {0xff,0x01,0x01,0x01,0xe1,0xf1,0x39,0x19,0x19,0x39,0xf1,0xe1,0x01,0x01,0x01,0xff,
  0xff,0x80,0x80,0x80,0x87,0x8f,0x9c,0x98,0x98,0x9c,0x8f,0x87,0x80,0x80,0x80,0xff},
  // 1
  {0xff,0x01,0x01,0x01,0x01,0x21,0x31,0xf9,0xf9,0x01,0x01,0x01,0x01,0x01,0x01,0xff,
  0xff,0x80,0x80,0x80,0x80,0x80,0x80,0x9f,0x9f,0x80,0x80,0x80,0x80,0x80,0x80,0xff},
  // 2
  {0xff,0x01,0x01,0x01,0x31,0x19,0x19,0x99,0x99,0x99,0xf9,0xf1,0x01,0x01,0x01,0xff,
  0xff,0x80,0x80,0x80,0x9c,0x9e,0x9f,0x9b,0x99,0x99,0x99,0x98,0x80,0x80,0x80,0xff},
  // 3
  {0xff,0x01,0x01,0x01,0x31,0x39,0x19,0x99,0x99,0x99,0xf9,0xf1,0x01,0x01,0x01,0xff,
  0xff,0x80,0x80,0x80,0x8c,0x9c,0x98,0x99,0x99,0x99,0x9f,0x8e,0x80,0x80,0x80,0xff},
  // 4
  {0xff,0x01,0x01,0x01,0xf9,0xf9,0x81,0x81,0xf9,0xf9,0x81,0x81,0x81,0x01,0x01,0xff,
  0xff,0x80,0x80,0x80,0x80,0x81,0x81,0x81,0x9f,0x9f,0x81,0x81,0x81,0x80,0x80,0xff},
  // 5
  {0xff,0x01,0x01,0x01,0xf9,0xf9,0x99,0x99,0x99,0x99,0x99,0x19,0x01,0x01,0x01,0xff,
  0xff,0x80,0x80,0x80,0x8c,0x9d,0x99,0x99,0x99,0x99,0x9f,0x8f,0x80,0x80,0x80,0xff},
  // 6
  {0xff,0x01,0x01,0x01,0xf1,0xf9,0x99,0x99,0x99,0x99,0xb9,0x31,0x01,0x01,0x01,0xff,
  0xff,0x80,0x80,0x80,0x8f,0x9f,0x99,0x99,0x99,0x99,0x9f,0x8f,0x80,0x80,0x80,0xff},
  // 7
  {0xff,0x01,0x01,0x01,0x19,0x19,0x19,0x19,0x19,0x99,0xf9,0x79,0x01,0x01,0x01,0xff,
  0xff,0x80,0x80,0x80,0x80,0x80,0x9c,0x9e,0x83,0x81,0x80,0x80,0x80,0x80,0x80,0xff},
  // 8
  {0xff,0x01,0x01,0x01,0x71,0xf9,0x99,0x99,0x99,0x99,0xf9,0x71,0x01,0x01,0x01,0xff,
  0xff,0x80,0x80,0x80,0x8f,0x9f,0x99,0x99,0x99,0x99,0x9f,0x8f,0x80,0x80,0x80,0xff},
  // 9
  {0xff,0x01,0x01,0x01,0x71,0xf9,0x99,0x99,0x99,0x99,0xf9,0xf1,0x01,0x01,0x01,0xff,
  0xff,0x80,0x80,0x80,0x8c,0x9d,0x99,0x99,0x99,0x99,0x9f,0x8f,0x80,0x80,0x80,0xff},
  // A
  {0xff,0x01,0x01,0xe1,0xf1,0x39,0x1d,0x0d,0x0d,0x1d,0x39,0xf1,0xe1,0x01,0x01,0xff,
  0xff,0x80,0x80,0xbf,0xbf,0x83,0x83,0x83,0x83,0x83,0x83,0xbf,0xbf,0x80,0x80,0xff},
  // B
  {0xff,0x01,0x01,0xfd,0xfd,0x8d,0x8d,0x8d,0x8d,0x8d,0xdd,0xf9,0x71,0x01,0x01,0xff,
  0xff,0x80,0x80,0xbf,0xbf,0xb1,0xb1,0xb1,0xb1,0xb1,0xbb,0xbf,0x8c,0x80,0x80,0xff},
  // C
  {0xff,0x01,0x01,0xf1,0xf9,0x1d,0x0d,0x0d,0x0d,0x0d,0x0d,0x19,0x11,0x01,0x01,0xff,
  0xff,0x80,0x80,0x8f,0x9f,0xb8,0xb0,0xb0,0xb0,0xb0,0xb0,0x98,0x88,0x80,0x80,0xff},
  // D (1 << 0xd)
  {0xff,0x01,0x01,0xfd,0xfd,0x0d,0x0d,0x0d,0x0d,0x0d,0x1d,0xf9,0xf1,0x01,0x01,0xff,
  0xff,0x80,0x80,0xbf,0xbf,0xb0,0xb0,0xb0,0xb0,0xb0,0xb8,0x9f,0x8f,0x80,0x80,0xff}
  // E: Number too big.
  // {0xff,0x01,0x01,0xfd,0xfd,0x8d,0x8d,0x8d,0x8d,0x8d,0x8d,0x0d,0x0d,0x01,0x01,0xff,
  // 0xff,0x80,0x80,0xbf,0xbf,0xb1,0xb1,0xb1,0xb1,0xb1,0xb1,0xb0,0xb0,0x80,0x80,0xff},
  // F: Number too big
  // {0xff,0x01,0x01,0xfd,0xfd,0x8d,0x8d,0x8d,0x8d,0x8d,0x8d,0x0d,0x0d,0x01,0x01,0xff,
  // 0xff,0x80,0x80,0xbf,0xbf,0x81,0x81,0x81,0x81,0x81,0x81,0x80,0x80,0x80,0x80,0xff}
};

// A white square drawn with "INVERT" will invert the area
const uint8_t white_square[] PROGMEM =
{
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

// vim:filetype=arduino
