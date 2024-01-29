#include <SDL.h>

#include <stdio.h>
#include <iostream>
#include "EEPROM.h"
#include "../2048-Arduboy/Defines.h"
#include "../2048-Arduboy/Platform.h"
#include "../2048-Arduboy/Controller.h"
#include "test.h"
/* #include "Game.h" */
/* #include "Interface.h" */
/* #include "Simulation.h" */

#define ZOOM_SCALE 4

SDL_Window* AppWindow;
SDL_Renderer* AppRenderer;
EEPROM eeprom;

Demo *demo;

// Replicate the Arduboy screen buffer here:
uint8_t sBuffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8]; 
uint8_t InputMask = 0;
void cleanup();

// Helper
void SetColour(uint8_t colour) {

  if (colour == COLOUR_WHITE) {
    SDL_SetRenderDrawColor(AppRenderer, 255, 255, 255, 255);
  } else {
    SDL_SetRenderDrawColor(AppRenderer, 0, 0, 0, 255);
  }
}

// From Platform.h
void Platform::PutPixel(uint8_t x, uint8_t y, uint8_t colour) {

  SetColour(colour);
  SDL_RenderDrawPoint(AppRenderer, x, y);
}

void Platform::DrawBitmap(const uint8_t* data, int16_t x, int16_t y, 
    uint8_t w, uint8_t h, uint8_t colour)
{
  for (int j = 0; j < h; j++)
  {
    for (int i = 0; i < w; i++)
    {
      int blockX = i / 8;
      int blockY = j / 8;
      int blocksPerWidth = w / 8;
      int blockIndex = blockY * blocksPerWidth + blockX;
      uint8_t pixels = data[blockIndex * 8 + i % 8];
      uint8_t mask = 1 << (j % 8);
      if (pixels & mask)
      {
        PutPixel(x + i, y + j, colour);
      }
    }
  }
}

void Platform::DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
    uint8_t colour) {
  
  SetColour(colour);

  if (SDL_RenderDrawLine(AppRenderer, x0, y0, x1, y1)) {
    std::cout << SDL_GetError() << std::endl;
  }
}

void DrawRect(int16_t x, int16_t y, uint8_t w, uint8_t h) {
  SDL_Rect rect;
  
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  SetColour(COLOUR_WHITE);

  if (SDL_RenderDrawRect(AppRenderer, &rect) < 0) {
    std::cout << SDL_GetError() << std::endl;
  }
}

void DrawFilledRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t colour) {
  SDL_Rect rect;
  
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  SetColour(colour);

  if (SDL_RenderFillRect(AppRenderer, &rect) < 0) {
    std::cout << SDL_GetError() << "\n";
  }
}

void Platform::DrawCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t colour) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  PutPixel(x0, y0+r, colour);
  PutPixel(x0, y0-r, colour);
  PutPixel(x0+r, y0, colour);
  PutPixel(x0-r, y0, colour);

  while (x<y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }

    x++;
    ddF_x += 2;
    f += ddF_x;

    PutPixel(x0 + x, y0 + y, colour);
    PutPixel(x0 - x, y0 + y, colour);
    PutPixel(x0 + x, y0 - y, colour);
    PutPixel(x0 - x, y0 - y, colour);
    PutPixel(x0 + y, y0 + x, colour);
    PutPixel(x0 - y, y0 + x, colour);
    PutPixel(x0 + y, y0 - x, colour);
    PutPixel(x0 - y, y0 - x, colour);
  }
}

void Platform::FillCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t colour) {
  
  SetColour(colour);

  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  PutPixel(x0, y0+r, colour);
  PutPixel(x0, y0-r, colour);
  PutPixel(x0+r, y0, colour);
  PutPixel(x0-r, y0, colour);

  while (x<y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }

    x++;
    ddF_x += 2;
    f += ddF_x;

    DrawLine(x0+x, y0-y, x0-x, y0-y, colour);
    DrawLine(x0+y, y0-x, x0-y, y0-x, colour);
  }
}

void Platform::FillScreen(uint8_t colour) {
  
  SetColour(colour);

  if (SDL_RenderClear(AppRenderer)) {
    std::cout << SDL_GetError() << "\n";
  }
}

void Platform::Clear() {
  FillScreen(COLOUR_BLACK);
}

// EEPROM
uint8_t Platform::ToEEPROM(uint8_t *bytes, int offset, int length) {
  return 0;
}
uint8_t Platform::FromEEPROM(uint8_t *bytes, int offset, int length) {
  return 0;
}

// From Controller.h
bool JustPressed(uint8_t button) {
  return InputMask & button;
}

bool JustReleased(uint8_t button) {
  return !(InputMask & button);
}

uint8_t Platform::GetInput() {
  return InputMask;
}

uint8_t ButtonState()
{
  return InputMask;
}

// Local Functions
//
void InitGame() {
  demo = new Demo();
}

int main(int argc, char* argv[])
{
  SDL_Init(SDL_INIT_VIDEO);

  SDL_CreateWindowAndRenderer(DISPLAY_WIDTH * ZOOM_SCALE, DISPLAY_HEIGHT * ZOOM_SCALE,
      SDL_WINDOW_RESIZABLE, &AppWindow, &AppRenderer);
  SDL_RenderSetLogicalSize(AppRenderer, DISPLAY_WIDTH, DISPLAY_HEIGHT);

  /* InitGame(); */

  bool running = true;
  InputMask = 0;

  while (running)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {


        case SDL_QUIT:
          running = false;
          break;

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {

            case SDLK_a:
              InputMask |= INPUT_A;
              break;

            case SDLK_LEFT:
              InputMask |= INPUT_LEFT;
              break;

            case SDLK_RIGHT:
              InputMask |= INPUT_RIGHT;
              demo->nextDemo();
              break;

            case SDLK_UP:
              InputMask |= INPUT_UP;
              break;

            case SDLK_DOWN:
              InputMask |= INPUT_DOWN;
              break;

            case SDLK_ESCAPE:
              running = false;
              break;
          }
          break;

        case SDL_KEYUP:
          switch (event.key.keysym.sym) {

            case SDLK_a:
              InputMask |= INPUT_A;
              break;

            case SDLK_LEFT:
              InputMask |= INPUT_LEFT;
              break;

            case SDLK_RIGHT:
              InputMask |= INPUT_RIGHT;
              break;

            case SDLK_UP:
              InputMask |= INPUT_UP;
              break;

            case SDLK_DOWN:
              InputMask |= INPUT_DOWN;
              break;
          }
          break;
        }
      }

    SDL_RenderPresent(AppRenderer);

    // FrameRate
    SDL_Delay(1000 / 20);

  }

  cleanup();
  return 0;
}

void cleanup() {
  delete demo;
  SDL_DestroyRenderer(AppRenderer);
  SDL_DestroyWindow(AppWindow);
  SDL_Quit();
}

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=cpp