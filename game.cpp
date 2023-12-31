/* 
Helper functions to unclutter main file
 */
#include "game.h"

void newGame() {
  
  int i;
  for (i=0; i<PLACES; i++) *(*board + i) = 0;
  newPiece();
  score = 0;
  running = 1;

}

BOOLEAN newPiece() {
  // Insert a new piece in the board.
  //
  int i, n = 0;
  int r;  // To decide betweeen 1 and 2 for an new piece
  uint16_t newval[2] = { 1u, 2u };
  uint8_t zeroes[PLACES];
  
  for (i = 0; i < PLACES; i++) {
    if (!board[i & 3][i >> 2]) zeroes[n++] = i;
  }

  if (n == 0) {
    gameOver();
    return;
  }

  i = zeroes[(int)random(0, n)];
  r = newval[(random(0, 100) < HIPROB)];
  board[i & 3][i >> 2] = r;

  if (r > biggest) biggest = r;
  new_piece = 1;
}

void moveRight() {
  // All pieces to the right. Additions if possible.
  int i, j;
  // We can go row by row
  for (j=0; j<VDIM; j++); 
}

void gameOver() {
  running = 0;
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
