/* 
Helper functions to unclutter main .ino file
 */
#include "Game.h"
#include "Draw.h"
#include "Controller.h"

GameStateStruct GameState;
uint16_t board[DIM][DIM];

void MoveTiles(int direction);
void GameOver();

void NewGame() {
  
  unsigned int i;
  for (i=0; i<PLACES; i++) *(*board + i) = 0;

  GameState.score = 0;
  GameState.running = true;
  GameState.modified = false;
  GameState.biggest = 0;
  GameState.moving = false;
  GameState.start = Millis();
  
  ClearScreen();
  NewPiece();
  NewPiece();
}

void StepGame() {
  
  uint8_t buttons;

  if (GameState.moving) {
    //Future animation
    // No buttons accepted during move
  } else {
    buttons = GetButtons();
#ifdef DEBUG
    // EraseRect(98, 8, 29, 8);  
    // SetCursor(98,8);
    // DrawInt(buttons);
#endif    
    HandleEvent(buttons);
  }

  if (GameState.modified) {
    DrawMap();
  }

  if (GameState.biggest == MAX_VALUE) {
    GameOver();
    /* TODO: This **has to be improved**. 
     * Very frustrating to be kicked out after
     * having reached MAX_VALUE without reward */
  } else if (GameState.biggest == TARGET_VALUE) {
    // TODO: Big Reward !!!
  }
  DrawGameState();    
}

void GameOver() {
  GameState.running = false;
  // TODO: Save Game State: High Score, biggest, time.
  DrawGameOver();
  // Later: Save high score, etc.
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

  if (n > GameState.biggest) {
    GameState.biggest = n;
  }
  
  GameState.modified = true;

}

void ExecuteMove(int direction) {

  if (!(direction & (INPUT_LEFT | INPUT_RIGHT | INPUT_UP | INPUT_DOWN))) {
    // This can't happen if event dispatched by controller
    EraseRect(98, 8, 29, 8);
    DrawStringAt(98, 8, "BOOM!");
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
          (*Board(i,j))++;
          GameState.biggest = *Board(i,j);
          *Board(k,j) = 0;
        }
      }
    }
  }
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino