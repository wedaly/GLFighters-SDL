#include "print.h"
#include "textures.h"
#include <GL/gl.h>
#include <cstdio>
#include <cstring>

static GLuint fontDisplayListsBase = 0;
static const int numFontDisplayLists = 256;
static int fontTextureID = 0;

bool createFont(int textureID) {
  fontTextureID = textureID;
  bindTexture(fontTextureID);

  fontDisplayListsBase = glGenLists(numFontDisplayLists);
  if (fontDisplayListsBase == 0) {
    printf("Error creating font display list\n");
    return false;
  }

  for (int i = 0; i < numFontDisplayLists; i++) {
    float cx = float(i % 16) / 16.0f;
    float cy = float(i / 16) / 16.0f;

    glNewList(fontDisplayListsBase + i, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(cx, 1 - cy - 0.0625f);
    glVertex2i(0, 0);
    glTexCoord2f(cx + 0.0625f, 1 - cy - 0.0625f);
    glVertex2i(16, 0);
    glTexCoord2f(cx + 0.0625f, 1 - cy);
    glVertex2i(16, 16);
    glTexCoord2f(cx, 1 - cy);
    glVertex2i(0, 16);
    glEnd();
    glTranslated(16, 0, 0);
    glEndList();
  }

  return true;
}

void freeFont() {
  fontTextureID = 0;
  if (fontDisplayListsBase != 0) {
    glDeleteLists(fontDisplayListsBase, numFontDisplayLists);
  }
}

void printToScreen(int x, int y, char *s, bool italicize, float size, int screenwidth, int screenheight) {
  int offset = italicize ? 128 : 0;
  bindTexture(fontTextureID);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, screenwidth, 0, screenheight, -100, 100);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glScalef(size, size, 1);
  glTranslated(x, y, 0);
  glListBase(fontDisplayListsBase - 32 + offset);
  glCallLists(strlen(s), GL_BYTE, s);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glEnable(GL_DEPTH_TEST);
}
