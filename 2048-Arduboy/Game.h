#pragma once

#include <stdint.h>
#include "Defines.h"

typedef struct {
  bool running;   // true if running, false if not.
  bool modified;  // true after board is modified. For refresh.
  unsigned int score;      // Current score of game.
  unsigned int biggest;    // Biggest number reached.
  uint8_t moving; // If nonzero, indicates moving direction.
  unsigned long start;
  } GameStateStruct;

// Map Arduino functions
int Random(int min, int max);
unsigned long Millis();

void NewGame();
void StepGame();
void Logic();

void NewPiece();
void ExecuteMove(int direction);

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
