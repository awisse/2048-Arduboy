/* 
Helper functions to unclutter main file
 */
#include "Game.h"
#include "Draw.h"
#include "Controller.h"

GameStateStruct GameState;
uint16_t board[DIM][DIM];

void MoveRight();
void MoveLeft();
void MoveHorizontal(int dir);
void MoveUp();
void MoveDown();

void NewGame() {
  
  unsigned int i;
  for (i=0; i<PLACES; i++) *(*board + i) = 0;

  GameState.score = 0;
  GameState.running = true;
  GameState.modified = false;
  GameState.biggest = 0;
  GameState.moving = false;
  
  ClearScreen();
  NewPiece();
  NewPiece();
}

void StepGame() {
  
  uint8_t buttons;

  if (GameState.moving) {
    //Future animation
  } else {// No buttons accepted during move
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

  DrawGameState();    
}

void GameOver() {
  GameState.running = false;
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

void ExecuteMove(uint8_t direction) {

  EraseRect(98, 8, 29, 8);
  switch (direction) {
    case INPUT_LEFT: 
      MoveLeft();
      break;
    case INPUT_RIGHT: 
      MoveRight();
      break;
    case INPUT_UP: 
      DrawStringAt(98, 8, "Up");
      break;
    case INPUT_DOWN: 
      DrawStringAt(98, 8, "Down");
      break;
    default:
      DrawStringAt(98, 8, "Other");
      return;
  }
  NewPiece();
}

void MoveRight() {
  // All pieces to the right. Additions if possible.
  // Reminder: [x-axis][y-axis]
  uint8_t i, j;
  int k;
  // We go row by row
  for (j=0; j<DIM; j++) {
    // Shift everything to the right
    for (i=DIM-1; i>0; i--) {
      if (board[i][j] == 0) {
        for (k=i-1; k>=0; k--) {
          if (board[k][j]) {
            board[i][j] = board[k][j];
            board[k][j] = 0;
            GameState.modified = true;
            break;
          }
        }
      } 
      if (board[i][j]) {
        for (k=i-1; (k >= 0) && (board[k][j] == 0); k--);
        if (board[k][j] == board[i][j]) {
          board[i][j]++;
          board[k][j] = 0;
          GameState.score += board[i][j];
          GameState.modified = true;
        }      
      }
    }
  }
}

void MoveLeft() {
  // All pieces to the left. Additions if possible.
  // Reminder: [x-axis][y-axis]
  uint8_t i, j;
  int k;
  // We go row by row
  for (j=0; j<DIM; j++) {
    // Shift everything to the left
    for (i=0; i<DIM-1; i++) {
      if (board[i][j] == 0) {
        for (k=i+1; k<DIM; k++) {
          if (board[k][j]) {
            board[i][j] = board[k][j];
            board[k][j] = 0;
            GameState.modified = true;
            break;
          }
        }
      } 
      if (board[i][j]) {
        for (k=i+1; (k < DIM) && (board[k][j] == 0); k++);
        if (board[k][j] == board[i][j]) {
          board[i][j]++;
          board[k][j] = 0;
          GameState.score += board[i][j];
          GameState.modified = true;
        }      
      }
    }
  }
}

void MoveHorizontal(int dir) {
  // Move tiles horizontally
  // Reminder: [x-axis][y-axis]
  // TODO: Not done.
  int i, j, k;
  // We go row by row
  for (j=0; j<DIM; j++) {
    // Shift everything to the left
    for (i=0; i<DIM-1; i+=dir) {
      if (board[i][j] == 0) {
        for (k=i+dir; k<DIM; k+=dir) {
          if (board[k][j]) {
            board[i][j] = board[k][j];
            board[k][j] = 0;
            GameState.modified = true;
            break;
          }
        }
      } 
      if (board[i][j]) {
        for (k=i+1; (k < DIM) && (board[k][j] == 0); k++);
        if (board[k][j] == board[i][j]) {
          board[i][j]++;
          board[k][j] = 0;
          GameState.score += board[i][j];
          GameState.modified = true;
        }      
      }
    }
  }
}

void MoveUp() {
}

void MoveDown() {
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
