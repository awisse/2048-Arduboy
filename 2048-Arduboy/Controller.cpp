#include "Controller.h"
#include "Game.h"
#include "Defines.h"

#ifdef DEBUG
#include "debug.h"
#endif

uint8_t DebouncedButtons();

void HandleEvent() {

  static unsigned long startAPress, startBPress;
  static bool AButtonDown, BButtonDown;
  static int BButtonLongPressCycles;
  uint8_t buttons;

  if (JustPressed(INPUT_A)) {
    AButtonDown = true;
    startAPress = Millis();
  }

  if (JustReleased(INPUT_A)) {
    AButtonDown = false;
    startAPress = Millis();
  }

  if (AButtonDown && (Millis() - startAPress) > LONG_PRESS) {
    startBPress = Millis();
    // Handle Long Press Event
    LoadGame();
  }

  if (JustPressed(INPUT_B)) {
    BButtonDown = true;
    startBPress = Millis();
    // Handle Button Down Event
    SaveGame();
  }

  if (JustReleased(INPUT_B)) {
    BButtonDown = false;
    startBPress = Millis();
    BButtonLongPressCycles = 0;
    // Handle Button Up Event
  }

  if (BButtonDown && (Millis() - startBPress) > LONG_PRESS) {
    startBPress = Millis();
    BButtonLongPressCycles++;
  #ifdef DEBUG
    DebugPrint(BButtonLongPressCycles);
  #endif
    // Handle Long Press Event
    NewGame();
  }

  // Special: Erase high score
  if (BButtonDown && AButtonDown && (BButtonLongPressCycles > 4)) {
  #ifdef DEBUG
    DebugPrint("Reset high score");
  #endif
    ResetHighScore();
  }

  buttons = DebouncedButtons();
  if (buttons & (INPUT_UP | INPUT_DOWN | INPUT_LEFT | INPUT_RIGHT)) {
    ExecuteMove(buttons);
  }
}

uint8_t DebouncedButtons() {
  static bool pressed;
  uint8_t buttons = ButtonState();

  if (!buttons) {
    pressed = false;
    return 0;
  } else if (pressed) {
    return 0;
  }

  pressed = true;
  return buttons;
}

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
