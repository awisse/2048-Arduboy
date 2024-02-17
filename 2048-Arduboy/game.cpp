/*
Helper functions to unclutter main .ino file
 */
#include "globals.h"
#include "game.h"
#include "draw.h"
#include "controller.h"
#include "platform.h"

#ifdef DEBUG
#include "debug.h"
#endif

uint16_t board[DIM][DIM];
GameStateStruct GameState;
static int16_t flash;

void NewGame();
bool MoveTiles(uint8_t direction); // True if something moved
void GameOver();
void BoardMask(uint16_t mask);
uint8_t CheckSignature(const char* signature, uint16_t offset);

void InitGame() {
  uint8_t loadState = LoadGame();

  if ((loadState != Saved) || (!GameState.running)) {
    NewGame();
    return;
  }

  InitScreen();
  flash = 0;
}

bool StepGame() {

  if (GameState.moving) {
    // Future animation
    // No buttons accepted during move
  } else {
    HandleEvent();
  }

  Logic();

  if (GameState.modified) {
    DrawMap(board);
    if (GameState.score > GameState.highScore) {
      GameState.highScore = GameState.score;
    }
    DrawScore(GameState.score, GameState.highScore, GameState.biggest);
    GameState.modified = false;
    GameState.saved = false;
  }

  if (GameState.biggest == MAX_VALUE) {
    GameOver();
    /* TODO: This **has to be improved**.
     * Very frustrating to be kicked out after
     * having reached MAX_VALUE without reward */
  } else if (GameState.biggest == TARGET_VALUE) {
    // TODO: Big Reward !!!
    // Stars!!
  }
  DrawGameState(GameState.running);

  // FIXME: Only draw if changes on board
  return true;

}

void NewGame() {

  InitScreen();

  BoardMask(0);
  flash = 0;

  GameState.score = 0;
  GameState.running = true;
  GameState.biggest = 0;
  GameState.moving = false;
  GameState.saved = true;

  NewPiece();
  NewPiece();
}

void Logic() {

  if (flash > 0) {
    Flash(board);
    if (--flash == 0) {
      BoardMask(0x7FFF);
      GameState.modified = true;
    }
  }

}

void GameOver() {
  GameState.running = false;
  SaveGame(); // Mainly to save highscore
  DrawGameOver();
  // Later: Save high score, etc.
}

void SaveGame() {

  if (GameState.saved) {
    return;
  }
  GameState.saved = true;
  GameState.moving = false;

  // Save Signature
  if (Platform::ToEEPROM((uint8_t*)signature, 0, 4u) != Saved) {
    return;
  }

  // Save Length
  if (Platform::ToEEPROM((uint8_t*)&eeprom_sz, 4, 2u) != Saved) {
    return;
  }

  // Save GameState
  if (Platform::ToEEPROM((uint8_t*)&GameState, 6, sizeof(GameState)) != Saved)
  {
    return;
  }
  // Save Board
  if (Platform::ToEEPROM((uint8_t*)board, 6 + sizeof(GameState),
      sizeof(board)) != Saved) {
    return;
  }
}

uint8_t LoadGame() {

  uint16_t highScore = GameState.highScore;
  uint16_t eeprom_length;
  uint8_t offset; // If length not saved
  uint8_t savedState = CheckSignature(signature, 0);

  if (savedState != Saved) {
    return savedState;
  }

  // Check whether two bytes after signature are == eeprom_sz
  savedState = Platform::FromEEPROM((uint8_t*)&eeprom_length, 4, 2u);
  if (savedState != Saved) {
    return savedState;
  }
  offset = (eeprom_length == eeprom_sz) ? 2 : 0;

  savedState = Platform::FromEEPROM((uint8_t*)&GameState, 4 + offset,
    sizeof(GameState));
  if (savedState != Saved) {
    return savedState;
  }

  savedState = Platform::FromEEPROM((uint8_t*)board,
    4 + offset + sizeof(GameState), sizeof(board));
  if (savedState != Saved) {
    return savedState;
  }

  GameState.saved = true;
  GameState.modified = true;
  // High Score is forever
  if (highScore > GameState.highScore) {
    GameState.highScore = highScore;
  }
  return savedState;
}

void NewPiece() {
  // Insert a new piece in the board.
  //
  uint16_t i, n = 0;
  uint8_t zeroes[PLACES];

  for (i = 0; i < PLACES; i++) {
    if (!board[i & 3][i >> 2]) zeroes[n++] = i;
  }

  if (n == 0) {
    GameOver();
    return; // Board Full
  }

  i = zeroes[Platform::Random(0, n)];
  // Reuse n to save memory
  n = (Platform::Random(0, 100) < HIPROB) ? 2 : 1;
  board[i & 3][i >> 2] = n;

  if ((1U << n) > GameState.biggest) {
    GameState.biggest = 1U << n;
  }

  GameState.modified = true;

}

void ExecuteMove(uint8_t direction) {

  if (!(direction & (INPUT_LEFT | INPUT_RIGHT | INPUT_UP | INPUT_DOWN))) {
    // This can't happen if event dispatched by controller
    EraseRect(98, 8, 29, 8);
    Text::DrawString(U8"BOOM!", 98, 8);
    return;
  }
  bool moved = MoveTiles(direction);
  if (moved) {
    NewPiece();
  }
}

// Define two functions to access the values of the board.
// boardv inverts the indices for the algorithm to apply
// in the vertical direction.
uint16_t* boardv(uint8_t x, uint8_t y) {
  return &board[y][x];
}
// boardh(i, j) returns the address of the value of board[i][j]
uint16_t* boardh(uint8_t x, uint8_t y) {
  return &board[x][y];
}

bool MoveTiles(uint8_t direction) { // Universal move in all directions
  // Move tiles in any direction
  // Reminder: board[x-axis][y-axis]
  uint16_t sum;
  int8_t i, j, k;  // Loop variables
  int8_t from, to; // Loop limits
  int8_t dir;      // Sign
  uint16_t* (*Board)(uint8_t, uint8_t); // Access function
  bool moved = false; // True if at least one move


  // Depending of the direction chosen by the user, configure the
  // algorithm correspondingly
  if ((direction == INPUT_UP) || (direction == INPUT_LEFT)) {
    from = 0;
    to = DIM - 1;
    dir = 1;
  } else {
    from = DIM - 1;
    to = 0;
    dir = -1;
  }
  if ((direction == INPUT_UP) || (direction == INPUT_DOWN)) {
    Board = boardv;
  } else {
    Board = boardh;
  }

  // Row by row for horizontal, column by column for vertical
  for (j=0; j<DIM; j++) {
    // Shift everything to the "dir"
    for (i=from; dir*i<to; i+=dir) {
      if (*Board(i,j) == 0) {
        for (k=i+dir; dir*k<=dir*to; k+=dir) {
          if (*Board(k,j)) {
            *Board(i,j) = *Board(k,j);
            *Board(k,j) = 0;
            moved = true; 
            break;
          }
        }
      }
      if (*Board(i,j)) {
        for (k=i+dir; (dir*k<dir*to) && (*Board(k,j) == 0); k+=dir);
        if (*Board(k,j) == *Board(i,j)) {
          sum = 1 << ++(*Board(i,j));
          if (sum > GameState.biggest) {
            GameState.biggest = sum;
          }
          GameState.score += sum;
          *Board(i,j) |= 0x8000; // Set highest bit for flashing
          flash = FLASH_FRAMES;
          *Board(k,j) = 0;
          moved = true;
        }
      }
    }
  }
  return moved; 
}

void BoardMask(uint16_t mask) {
  // Logical and of all board values with mask;
  uint16_t i;
  for (i=0; i<PLACES; i++) {
    *(*board + i) &= mask;
  }
}

void ResetHighScore() {
  GameState.highScore = 0;
}

uint8_t CheckSignature(const char* signature, uint16_t offset) {
  char id[4];
  uint8_t i;
  SavedState savedState = Platform::FromEEPROM((uint8_t*)id, offset, 4);

  if (savedState != Saved) {
    return savedState;
  }

  for (i=0; i<4; i++) {
    if (id[i] != signature[i]) {
      return WrongSignature;
    }
  }

  return Saved;
}

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab
