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

#include <stdint.h>

uint8_t _GetButtons();
uint8_t GetButtons();
void HandleEvent(uint8_t buttons);
void Delay(uint16_t milliseconds);

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
