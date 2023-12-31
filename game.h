/* Helper functions to unclutter main file
 */
#pragma once
#include <stdint.h>
#include "defines.h"

// Global variables
uint16_t board[VDIM][HDIM];
int running;    // 1 if running. 0 if not.
int new_piece;  // 1 after a new piece is inserted (for refresh).
int score;      // Current score of game. 
int biggest;    // Biggest number reached.

void newGame();
BOOLEAN newPiece();
void moveRight();
void gameOver();
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
