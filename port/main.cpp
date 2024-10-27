#include "input.h"
#include "models.h"
#include "print.h"
#include "sound.h"
#include "textures.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <cstdio>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const Uint32 TARGET_TICKS_PER_FRAME = 16; // About 60fps

void drawFrame() {
  glLoadIdentity();
  bindTexture(TEX_RED_HELMET_ID);
  Head();

  printToScreen(10, 10, "012345", false, 1.0, SCREEN_WIDTH, SCREEN_HEIGHT);

  if (isKeyDown(KEY_P1_LEFT_ID)) {
    printToScreen(10, 30, "p1 left", false, 1.0, SCREEN_WIDTH, SCREEN_HEIGHT);
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
        int keyID = translateSDLEventToKeyID(e.key);
        if (keyID >= 0) {
          setKeyState(keyID, bool(e.key.state == SDL_PRESSED));
        }
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

  glEnable(GL_TEXTURE_2D);
  if (!loadTextures()) {
    printf("Failed loading textures\n");
    return 1;
  }

  if (!createFont(TEX_FONT_ID)) {
    printf("Failed creating font\n");
    return 1;
  }

  if (!loadSounds()) {
    printf("Failed loading sounds\n");
    return 1;
  }

  runEventLoop(window);

  freeSounds();
  freeFont();
  freeTextures();
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
