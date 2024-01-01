/* 
Helper functions to unclutter main file
 */
#include "Game.h"

GameStateStruct GameState;
uint16_t board[VDIM][HDIM];

void NewGame() {
  
  int i;
  for (i=0; i<PLACES; i++) *(*board + i) = 0;
  // Debugging
  for (i=0;i<4;i++) {
    for (int j=0;j<4;j++) {
      
    }
  }
  NewPiece();
  GameState.score = 0;
  GameState.running = 1;

}

bool NewPiece() {
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
    GameOver();
    return;
  }

  i = zeroes[Random(0, n)];
  r = newval[(Random(0, 100) < HIPROB)];
  board[i & 3][i >> 2] = r;

  if (r > GameState.biggest) {
    GameState.biggest = r;
  }
  GameState.new_piece = 1;
}

void MoveRight() {
  // All pieces to the right. Additions if possible.
  int i, j;
  // We can go row by row
  for (j=0; j<VDIM; j++); 
}

void GameOver() {
  GameState.running = 0;
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
