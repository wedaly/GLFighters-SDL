#pragma once

#include <SDL2/SDL.h>

bool initGame(int screenWidthConfig, int screenHeightConfig);
void disposeGame();
void runGameEventLoopOnce(SDL_Window *window, bool *quit);
