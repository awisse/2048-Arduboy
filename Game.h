#pragma once

#include <stdint.h>
#include "Defines.h"

#define LEFT 1
#define RIGHT -1
#define UP 1
#define DOWN -1

// Global variables
extern uint16_t board[DIM][DIM]; // [x-axis(h)][y-axis(v)]
typedef struct {
  bool running;   // true if running, false if not.
  bool modified;  // true after board is modified. For refresh.
  unsigned int score;      // Current score of game. 
  unsigned int biggest;    // Biggest number reached.
  uint8_t moving; // If nonzero, indicates moving direction.
  } GameStateStruct;



extern GameStateStruct GameState;

int Random(int min, int max);

void NewGame();
void StepGame();

void NewPiece();
void ExecuteMove(uint8_t direction);

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
