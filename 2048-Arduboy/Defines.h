#pragma once

//#define DEBUG
#define DIM 4
// Screen dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// Maximal value: 1 << 0xD
#define MAX_VALUE 0XD
#define TARGET_VALUE 0xB
#define PLACES DIM * DIM
// Board position on the screen
#define BOARD_X 32
#define BOARD_Y 0
// Tile size in pixels
#define TILE_SZ 16
// Position of scores on screen
#define SCORE_X 100
#define SCORE_Y 0
#define HIGHSCORE_Y 20
#define MAX_Y 40
#define FONT_STEP 8
// Probability (in %) of inserting 2 instead of 1 as a new piece
#define HIPROB 10
// Color codes
#define _BLACK 0
#define _WHITE 1
#define _INVERT 2
// Tile flashing duration in number of frames
#define FLASH_FRAMES 4


