#pragma once
/*
 * Manage User Interactions
 * Dispatch Events
 */
#define INPUT_LEFT 32u
#define INPUT_RIGHT 64u
#define INPUT_UP 128u
#define INPUT_DOWN 16u
#define INPUT_A 8u
#define INPUT_B 4u
#define LONG_PRESS 2000

#include <stdint.h>

bool JustPressed(uint8_t button);
bool JustReleased(uint8_t button);
uint8_t ButtonState();
void HandleEvent();

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
