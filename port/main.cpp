#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const Uint32 TARGET_TICKS_PER_FRAME = 16; // About 60fps

void runEventLoop(SDL_Window *window) {
  SDL_Event e;
  while (true) {
    Uint32 startTicks = SDL_GetTicks(); // milliseconds

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        return;
      }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
    SDL_GL_SwapWindow(window);

    Uint32 endTicks = SDL_GetTicks(); // milliseconds
    Uint32 elapsedTicks = endTicks - startTicks;
    if (elapsedTicks < TARGET_TICKS_PER_FRAME) {
      SDL_Delay(TARGET_TICKS_PER_FRAME - elapsedTicks);
    }
  }
}

int main(int argc, char *args[]) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("GLFighters", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_GLContext glctx = SDL_GL_CreateContext(window);
  if (glctx == NULL) {
    printf("Could not ceate OpenGL context. SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_GL_MakeCurrent(window, glctx);
  runEventLoop(window);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
