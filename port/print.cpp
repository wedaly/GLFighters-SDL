#include "print.h"
#include "textures.h"
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <cstdio>
#include <cstring>

static const int numFontChars = 256;
static GLuint fontVertexBufferObjIDs[numFontChars] = {0};
static int fontTextureID = 0;

bool createFont(int textureID) {
  fontTextureID = textureID;
  bindTexture(fontTextureID);

  glGenBuffers(numFontChars, fontVertexBufferObjIDs);
  float vertexData[16];
  for (int i = 0; i < numFontChars; i++) {
    float cx = float(i % 16) / 16.0f;
    float cy = float(i / 16) / 16.0f;

    // texture bottom-left
    vertexData[0] = cx;
    vertexData[1] = 1 - cy - 0.0625f;

    // vertex bottom-left
    vertexData[2] = 0.0f;
    vertexData[3] = 0.0f;

    // texture bottom-right
    vertexData[4] = cx + 0.0625f;
    vertexData[5] = 1 - cy - 0.0625f;

    // vertex bottom-right
    vertexData[6] = 16.0f;
    vertexData[7] = 0.0f;

    // texture top-right
    vertexData[8] = cx + 0.0625f;
    vertexData[9] = 1 - cy;

    // vertex top-right
    vertexData[10] = 16.0f;
    vertexData[11] = 16.0f;

    // texture top-left
    vertexData[12] = cx;
    vertexData[13] = 1 - cy;

    // vertex top-left
    vertexData[14] = 0.0f;
    vertexData[15] = 16.0f;

    glBindBuffer(GL_ARRAY_BUFFER, fontVertexBufferObjIDs[i]);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertexData, GL_STATIC_DRAW);
  }

  return true;
}

void freeFont() {
  glDeleteBuffers(numFontChars, fontVertexBufferObjIDs);
}

void printToScreen(int x, int y, const char *s, bool italicize, float size, int screenwidth, int screenheight) {
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

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);

  for (size_t i = 0; i < strlen(s); i++) {
    int vboID = s[i] - 32 + offset; // start from ASCII ' '
    if (vboID >= 0 && vboID < numFontChars) {
      glBindBuffer(GL_ARRAY_BUFFER, fontVertexBufferObjIDs[vboID]);
      glTexCoordPointer(2, GL_FLOAT, 4 * sizeof(float), (void *)(0));
      glVertexPointer(2, GL_FLOAT, 4 * sizeof(float), (void *)(2 * sizeof(float)));
      glDrawArrays(GL_QUADS, 0, 4);
    }
    glTranslatef(16.0f, 0.0f, 0.0f);
  }

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glEnable(GL_DEPTH_TEST);
}
