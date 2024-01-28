// Compact font taken from
// https://hackaday.io/project/6309-vga-graphics-over-spi-and-serial-vgatonic/log/20759-a-tiny-4x6-pixel-font-that-will-fit-on-almost-any-microcontroller-license-mit

#include <stdint.h>
#include "Defines.h"
#include "Font.h"
#include "Platform.h"

uint16_t Font::CharIdx(const char c) {

  uint16_t idx;

  switch (c) {

    case CHAR_LETTER_A ... CHAR_LETTER_Z:
      idx = c - CHAR_LETTER_A;
      break;

    case CHAR_LETTER_A_LOWER ... CHAR_LETTER_Z_LOWER:
      idx = c - CHAR_LETTER_A_LOWER + 26;
      break;

    case CHAR_NUMBER_0 ... CHAR_NUMBER_9:
      idx = c - CHAR_NUMBER_0 + FONT_NUMBER_INDEX;
      break;

    case '!':
      idx = FONT_EXCLAMATION_INDEX;
      break;

    case '.':
      idx = FONT_PERIOD_INDEX;
      break;

    case ' ':
      idx = FONT_SPACE_INDEX;
      break;

    default:
      idx = FONT_BIDON_INDEX;
  }

  return idx * FONT_WIDTH;
}


