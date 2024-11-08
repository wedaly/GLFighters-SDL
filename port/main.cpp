#include "game.h"
#include "input.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <cstdio>

#ifdef __EMSCRIPTEN__
#include "gl4esinit.h"
#include <emscripten.h>
#endif

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static SDL_Window *window = NULL;
static bool quit = false;

#ifdef __EMSCRIPTEN__
static void emscriptenMainLoopCallback() {
  runGameEventLoopOnce(window, &quit);
  if (quit) {
    emscripten_cancel_main_loop();
  }
}

static void runGameEventLoop() {
  emscripten_set_main_loop(emscriptenMainLoopCallback, 0, 1);
  if (emscripten_set_main_loop_timing(EM_TIMING_RAF, 1) != 0) {
    printf("Failed setting emscripten main loop timing\n");
  }
}
#else
static void runGameEventLoop() {
  const Uint32 TARGET_TICKS_PER_FRAME = 16; // About 60fps
  while (!quit) {
    Uint64 startTicks = SDL_GetTicks64(); // milliseconds
    runGameEventLoopOnce(window, &quit);
    Uint64 endTicks = SDL_GetTicks64();
    if (endTicks > startTicks && endTicks - startTicks < TARGET_TICKS_PER_FRAME) {
      SDL_Delay(TARGET_TICKS_PER_FRAME - (endTicks - startTicks));
    }
  }
}
#endif

int main() {
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

#ifdef __EMSCRIPTEN__
  initialize_gl4es();
#endif

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

  runGameEventLoop();

  disposeGame();
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
