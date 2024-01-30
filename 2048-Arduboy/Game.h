#pragma once

#include <stdint.h>
#include "Defines.h"

constexpr char signature[] = "2048";

typedef struct {
  bool running;   // true if running, false if not.
  bool modified;  // true after board is modified. For refresh.
  unsigned int score;      // Current score of game.
  unsigned int highScore;  // Highest (saved) score ever.
  unsigned int biggest;    // Biggest number reached.
  uint8_t moving; // If nonzero, indicates moving direction.
  bool saved; // If state of game is saved in EEPROM
  } GameStateStruct;

// Result codes for (To|From)EEPROM
enum {
  Saved,
  NotSaved, // Never been saved.
  WrongOffset,
  TooBig,
  WrongSignature
};

// Map Arduino functions
int Random(int i0, int i1);
unsigned long Millis();
uint8_t ToEEPROM(uint8_t *bytes, int offset, int length);
uint8_t FromEEPROM(uint8_t *bytes, int offset, int length);

void InitGame();
void StepGame();
void NewGame();
void SaveGame();
uint8_t LoadGame();
void Logic();

void NewPiece();
void ExecuteMove(int direction);
void ResetHighScore();

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
