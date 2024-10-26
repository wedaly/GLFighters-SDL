#include "models.h"
#include "sound.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const Uint32 TARGET_TICKS_PER_FRAME = 16; // About 60fps

void drawFrame() {
  glLoadIdentity();
  glColor4f(0.5, 0.0, 0.0, 0.5);
  JetPack();
}

void handleKeyEvent(SDL_KeyboardEvent &e) {
  // e.keysym.sym is like SDLK_UP, SDLK_DOWN, ...
  // e.state is SDL_PRESSED or SDL_RELEASED
  printf("key event: key=%d, state=%d\n", e.keysym.sym, e.state);

  if (e.keysym.sym == 's' && e.state == SDL_PRESSED) {
    playSound(SND_LIGHTSABRE_ID);
  }
}

void runEventLoop(SDL_Window *window) {
  SDL_Event e;
  while (true) {
    Uint32 startTicks = SDL_GetTicks(); // milliseconds

    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        return;

      case SDL_KEYDOWN:
      case SDL_KEYUP:
        handleKeyEvent(e.key);
        break;
      }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawFrame();
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

  if (loadSounds() < 0) {
    printf("Failed loading sounds\n");
    return 1;
  }

  runEventLoop(window);

  freeSounds();
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
