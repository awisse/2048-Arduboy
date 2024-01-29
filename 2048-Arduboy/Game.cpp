/*
Helper functions to unclutter main .ino file
 */
#include "Game.h"
#include "Draw.h"
#include "Controller.h"
#include "Platform.h"

uint16_t board[DIM][DIM];
GameStateStruct GameState;
static int16_t flash;

void NewGame();
void MoveTiles(int direction);
void GameOver();
void BoardMask(uint16_t mask);

void InitGame() {
  uint8_t loadState = LoadGame();

  if ((loadState != Saved) || (!GameState.running)) {
    NewGame();
    return;
  }

  InitScreen();
  flash = 0;
}

void StepGame() {

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
  }
  DrawGameState(GameState.running);

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

  // Save GameState
  if (Platform::ToEEPROM((uint8_t*)&GameState, 0, sizeof(GameState)) != Saved) {
    return;
  }
  // Save Board
  if (Platform::ToEEPROM((uint8_t*)board, sizeof(GameState), sizeof(board)) != Saved) {
    return;
  }
}

uint8_t LoadGame() {

  unsigned int highScore = GameState.highScore;
  uint8_t savedState = Platform::FromEEPROM((uint8_t*)&GameState, 0, sizeof(GameState));
  if (savedState == Saved) {
    savedState = Platform::FromEEPROM((uint8_t*)board, sizeof(GameState), sizeof(board));
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
  unsigned int i, n = 0;
  uint8_t zeroes[PLACES];

  for (i = 0; i < PLACES; i++) {
    if (!board[i & 3][i >> 2]) zeroes[n++] = i;
  }

  if (n == 0) {
    GameOver();
    return; // Board Full
  }

  i = zeroes[Random(0, n)];
  // Reuse n to save memory
  n = (Random(0, 100) < HIPROB) ? 2 : 1;
  board[i & 3][i >> 2] = n;

  if ((1U << n) > GameState.biggest) {
    GameState.biggest = 1U << n;
  }

  GameState.modified = true;

}

void ExecuteMove(int direction) {

  if (!(direction & (INPUT_LEFT | INPUT_RIGHT | INPUT_UP | INPUT_DOWN))) {
    // This can't happen if event dispatched by controller
    EraseRect(98, 8, 29, 8);
    DrawString("BOOM!", 98, 1);
    return;
  }
  MoveTiles(direction);
  NewPiece();
}

// Define two functions to access the values of the board.
// boardv inverts the indices for the algorithm to apply
// in the vertical direction.
uint16_t* boardv(int x, int y) {
  return &board[y][x];
}
// boardh(i, j) returns the address of the value of board[i][j]
uint16_t* boardh(int x, int y) {
  return &board[x][y];
}

void MoveTiles(int direction) { // Universal move in all directions
  // Move tiles in any direction
  // Reminder: board[x-axis][y-axis]
  unsigned int sum;
  int i, j, k;  // Loop variables
  int from, to; // Loop limits
  int dir;      // Sign
  uint16_t* (*Board)(int, int); // Access function


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
        }
      }
    }
  }
}

void BoardMask(uint16_t mask) {
  // Logical and of all board values with mask;
  unsigned int i;
  for (i=0; i<PLACES; i++) {
    *(*board + i) &= mask;
  }
}

void ResetHighScore() {
  GameState.highScore = 0;
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
