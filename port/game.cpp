#include "game.h"
#include "models.h"
#include "print.h"
#include "sound.h"
#include "textures.h"
#include <GL/gl.h>
#include <cstdio>

bool initGame(int screenwidth, int screenheight) {
  glEnable(GL_TEXTURE_2D);

  if (!loadTextures()) {
    printf("Failed loading textures\n");
    return false;
  }

  if (!createFont(TEX_FONT_ID)) {
    printf("Failed creating font\n");
    return false;
  }

  if (!loadSounds()) {
    printf("Failed loading sounds\n");
    return false;
  }

  return true;
}

void disposeGame() {
  freeSounds();
  freeFont();
  freeTextures();
}

void handleKeypress(int keyID) {
}

void drawGameFrame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  bindTexture(TEX_RED_HELMET_ID);
  Head();
  glFlush();
}

void updateGameState() {
}
