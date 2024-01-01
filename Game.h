#pragma once

#include <stdint.h>
#include "Defines.h"

// Global variables
extern uint16_t board[VDIM][HDIM];
typedef struct {
  int running;    // 1 if running. 0 if not.
  int new_piece;  // 1 after a new piece is inserted (for refresh).
  int score;      // Current score of game. 
  int biggest;    // Biggest number reached.
} GameStateStruct;

extern GameStateStruct GameState;

int Random(int min, int max);
void NewGame();
bool NewPiece();
void MoveRight();
void GameOver();
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
