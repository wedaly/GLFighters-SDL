#include "game.h"
#include "input.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <cstdio>
#include <emscripten.h>
#include <gl4esinit.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static SDL_Window *window;

static void mainLoop() {
  runGameEventLoop(window);
}

int main(int argc, char *args[]) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow("GLFighters", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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

  initialize_gl4es();

  if (!initGame(SCREEN_WIDTH, SCREEN_HEIGHT)) {
    printf("Failed to initialize game\n");
    return 1;
  }

  emscripten_set_main_loop(mainLoop, 0, 1);
  if (emscripten_set_main_loop_timing(EM_TIMING_RAF, 1) != 0) {
    printf("Failed setting emscripten main loop timing\n");
    return 1;
  }

  disposeGame();
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
