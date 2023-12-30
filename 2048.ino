#include <Arduboy2.h>
#include "sprites.h"
#define VDIM 4
#define HDIM 4
#define PLACES VDIM * HDIM
// Probability of inserting a bigger new number (over 100)
#define HIPROB 20
// Make an instance of arduboy used for many functions
Arduboy2 arduboy;

// Global variables
uint16_t board[VDIM][HDIM];
int running, new_piece;

void drawMap();
void gameOver();

void setup() {
  // put your setup code here, to run once:
  //initiate arduboy instance
  arduboy.begin();

  // here we set the framerate to 30, we do not need to run at default 60 and
  // it saves us battery life.
  arduboy.setFrameRate(20);

  // Initialize board
  memset(board, 0, PLACES);
  //randomSeed();

  while (!arduboy.pressed(A_BUTTON)) {
    arduboy.idle();
  }
  arduboy.clear();
  // We need the delay before the first button press for a good seed
  arduboy.initRandomSeed();
  newPiece();
  running = 1;

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
  arduboy.display();
  if (arduboy.pressed(A_BUTTON)) {
    newPiece();
    // Unbounce the button
    delay(100);
  }

  arduboy.idle();
}

bool newPiece() {
  // Insert a new piece in the board.
  //
  int i, n = 0;
  int r = random(0, 100);  // To decide betweeen 1 and 2 for an new piece
  uint16_t newval[2] = { 1u, 2u };
  uint8_t zeroes[PLACES];
  memset(zeroes, 0, PLACES);

  for (i = 0; i < PLACES; i++) {
    if (!board[i & 3][i >> 2]) zeroes[n++] = i;
  }

  if (n == 0) {
    gameOver();
    return;
  }

  i = zeroes[(int)random(0, n)];
  board[i & 3][i >> 2] = newval[(random(0, 100) < HIPROB)];

  new_piece = 1;
}

void drawMap() {
  int16_t i, value;
  // Draw 4x4 map of numbers in board.
  arduboy.fillRect(32, 0, 64, 64, BLACK);
  arduboy.drawLine(32, 0, 32, 63);
  arduboy.drawLine(96, 0, 96, 63);
  for (i = 16; i < 64; i += 16) {
    arduboy.drawLine(32, i, 96, i);
    arduboy.drawLine(32 + i, 0, 32 + i, 63);
  }

  for (i = 0; i < PLACES; i++) {
    if ((value = board[i >> 2][i & 3])) {
      arduboy.drawBitmap(32 + ((i << 2) & 0x30), (i << 4) & 0x30, numbers[value], 16, 16);
    }
  }
  arduboy.display();
  new_piece = 0;
}

void gameOver() {
  arduboy.fillRect(30, 20, 69, 24, BLACK);
  arduboy.drawRect(30, 20, 69, 24);
  arduboy.drawRect(29, 19, 71, 26);
  arduboy.setCursor(36, 28);
  arduboy.print("GAME OVER");
  arduboy.display();
  running = 0;
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab
