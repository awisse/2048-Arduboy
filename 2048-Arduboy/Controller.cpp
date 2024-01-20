#include "Controller.h"
#include "Game.h"

void HandleEvent(uint8_t buttons) {

  if (buttons & INPUT_A) {
    // For debugging only
    // NewPiece();
  }

  if (buttons & INPUT_B) {
    NewGame();
  }

  if (buttons & (INPUT_UP | INPUT_DOWN | INPUT_LEFT | INPUT_RIGHT)) {
    ExecuteMove(buttons);
  }
  
}

uint8_t GetButtons() {
  // De-bounced version
  static bool buttonDown=false;
  uint8_t buttons;

  buttons = _GetButtons();
  if (!buttons) {
    buttonDown = false;
    return 0;
  } else if (buttonDown) {
    return 0;
  }

  buttonDown = true;
  return buttons;
  
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
