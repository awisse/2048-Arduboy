#pragma once

#ifndef ARDUINO
#include <stdint.h>
#include <string.h>
#define PROGMEM
#define PSTR
#define pgm_read_byte(x) (*((uint8_t*)x))
#define pgm_read_word(x) (*((uint16_t*)x))
#define pgm_read_ptr(x) (*((uintptr_t*)x))
#define strlen_P(x) strlen(x)
#else
#include <avr/pgmspace.h>
//#define pgm_read_ptr pgm_read_word
#endif

//#define DEBUG
#define DIM 4
// Screen dimensions
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
// Maximal value: 1 << 0xD
#define MAX_VALUE 0XD
#define TARGET_VALUE 0xB
#define PLACES DIM * DIM
// Board position on the screen
#define BOARD_X 32
#define BOARD_Y 0
// Tile size in pixels
#define TILE_SZ 16
// Position of text on screen
#define SCORE_X 100
#define SCORE_LINE 0
#define HIGHSCORE_LINE 3
#define MAX_LINE 6
#define FONT_STEP 8
#define OVER_LINE 3
// Probability (in %) of inserting 2 instead of 1 as a new piece
#define HIPROB 10
// Color codes
#define COLOUR_BLACK 0
#define COLOUR_WHITE 1
#define COLOUR_INVERT 2
// Tile flashing duration in number of frames
#define FLASH_FRAMES 4


