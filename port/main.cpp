#include "game.h"
#include "input.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <cstdio>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *args[]) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("GLFighters", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  if (window == NULL) {
    printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_GLContext glctx = SDL_GL_CreateContext(window);
  if (glctx == NULL) {
    printf("Could not create OpenGL context. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  if (SDL_GL_MakeCurrent(window, glctx) < 0) {
    printf("Could not make OpenGL context current. SDL_Error: %s\n",
           SDL_GetError());
    return 1;
  }

  if (!initGame(SCREEN_WIDTH, SCREEN_HEIGHT)) {
    printf("Failed to initialize game\n");
    return 1;
  }

  runGameLoop(window);

  disposeGame();
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
