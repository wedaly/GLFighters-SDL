#pragma once

#include <SDL2/SDL.h>

bool initGame(int screenWidthConfig, int screenHeightConfig);
void disposeGame();
void runGameEventLoop(SDL_Window *window);
