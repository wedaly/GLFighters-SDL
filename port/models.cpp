#include "models.h"
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <cstdio>

const int numModels = 24;

const char *modelPaths[numModels] = {
    "./data/models/Chunk",
    "./data/models/Floor",
    "./data/models/Foot",
    "./data/models/Grenade",
    "./data/models/Grenlauncher",
    "./data/models/Hand",
    "./data/models/Head",
    "./data/models/Head2",
    "./data/models/Hip",
    "./data/models/JetPack",
    "./data/models/LaserRifle",
    "./data/models/LightningGun",
    "./data/models/LightSabre",
    "./data/models/Lowerarm",
    "./data/models/Lowerleg",
    "./data/models/Machinegun",
    "./data/models/One",
    "./data/models/Rifle",
    "./data/models/Rope",
    "./data/models/Sword",
    "./data/models/Torso",
    "./data/models/Upperarm",
    "./data/models/Upperleg",
    "./data/models/Wall",
};

GLuint vertexBufferObjIDs[numModels] = {0};
unsigned int numVerticesForModel[numModels] = {0};

bool readUnsignedInt(FILE *f, unsigned int *i) {
  size_t n = fread(i, sizeof(unsigned int), 1, f);
  if (n != 1) {
    *i = 0;
    return false;
  }

  *i = SDL_SwapBE32(*i);
  return true;
}

bool loadModelFromFile(const char *path, int id) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    printf("Could not open model file %s\n", path);
    return false;
  }

  unsigned int numVertices = 0;
  if (!readUnsignedInt(f, &numVertices)) {
    printf("Could not read numVertices\n");
    fclose(f);
    return false;
  }

  if (numVertices == 0 || numVertices > 1000) {
    printf("Invalid numVertices %d\n", numVertices);
    fclose(f);
    return false;
  }

  unsigned int numFloats = numVertices * 8; // 2 tex + 3 normal + 3 vertex
  float *vertexData = new float[numFloats];
  size_t n = fread(vertexData, sizeof(float), numFloats, f);
  if (n != numFloats) {
    printf("Not enough float data, expected %d but got %d\n", numFloats, n);
    fclose(f);
    delete vertexData;
    return false;
  }

  for (int i = 0; i < numFloats; i++) {
    vertexData[i] = SDL_SwapFloatBE(vertexData[i]);
  }

  numVerticesForModel[id] = numVertices;
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjIDs[id]);
  glBufferData(GL_ARRAY_BUFFER, numFloats * sizeof(float), vertexData, GL_STATIC_DRAW);
  delete vertexData;

  return true;
}

bool loadModels() {
  glGenBuffers(numModels, vertexBufferObjIDs);

  for (int i = 0; i < numModels; i++) {
    const char *path = modelPaths[i];
    if (!loadModelFromFile(path, i)) {
      printf("Failed to load model from file %s\n", path);
      glDeleteBuffers(numModels, vertexBufferObjIDs);
      return false;
    }
  }

  return true;
}

void freeModels() {
  glDeleteBuffers(numModels, vertexBufferObjIDs);
}

void drawModel(int id) {
  if (id < 0 || id >= numModels) {
    printf("Invalid model id %d\n", id);
    return;
  }

  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjIDs[id]);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);
  glTexCoordPointer(3, GL_FLOAT, 8 * sizeof(float), (void *)(0));
  glNormalPointer(GL_FLOAT, 8 * sizeof(float), (void *)(2 * sizeof(float)));
  glVertexPointer(3, GL_FLOAT, 8 * sizeof(float), (void *)(5 * sizeof(float)));
  glDrawArrays(GL_TRIANGLES, 0, numVerticesForModel[id]);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void glDrawFloor(float xWidth, float yWidth, float zWidth, float movement) {
  int tesselation = 1;
  int normallength = -1;
  glBegin(GL_QUADS);
  // Front Face
  glNormal3f(0.0f, 0.0f, -normallength);
  glTexCoord2f(0.0f, movement);
  glVertex3f(-xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, movement);
  glVertex3f(xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(xWidth, yWidth, zWidth);
  glTexCoord2f(0.0f, tesselation + movement);
  glVertex3f(-xWidth, yWidth, zWidth);
  // Back Face
  glNormal3f(0.0f, 0.0f, normallength);
  glTexCoord2f(tesselation, movement);
  glVertex3f(-xWidth, -yWidth, -zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(-xWidth, yWidth, -zWidth);
  glTexCoord2f(0.0f, tesselation + movement);
  glVertex3f(xWidth, yWidth, -zWidth);
  glTexCoord2f(0.0f, movement);
  glVertex3f(xWidth, -yWidth, -zWidth);
  // Top Face
  glNormal3f(0.0f, -normallength, 0.0f);
  glTexCoord2f(0.0f, tesselation + movement);
  glVertex3f(-xWidth, yWidth, -zWidth);
  glTexCoord2f(0.0f, movement);
  glVertex3f(-xWidth, yWidth, zWidth);
  glTexCoord2f(tesselation, movement);
  glVertex3f(xWidth, yWidth, zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(xWidth, yWidth, -zWidth);
  // Bottom Face
  glNormal3f(0.0f, normallength, 0.0f);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(-xWidth, -yWidth, -zWidth);
  glTexCoord2f(0.0f, tesselation + movement);
  glVertex3f(xWidth, -yWidth, -zWidth);
  glTexCoord2f(0.0f, movement);
  glVertex3f(xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, movement);
  glVertex3f(-xWidth, -yWidth, zWidth);
  // Right face
  glNormal3f(-normallength, 0.0f, 0.0f);
  glTexCoord2f(tesselation, movement);
  glVertex3f(xWidth, -yWidth, -zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(xWidth, yWidth, -zWidth);
  glTexCoord2f(0.0f, tesselation + movement);
  glVertex3f(xWidth, yWidth, zWidth);
  glTexCoord2f(0.0f, movement);
  glVertex3f(xWidth, -yWidth, zWidth);
  // Left Face
  glNormal3f(normallength, 0.0f, 0.0f);
  glTexCoord2f(0.0f, movement);
  glVertex3f(-xWidth, -yWidth, -zWidth);
  glTexCoord2f(tesselation, movement);
  glVertex3f(-xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(-xWidth, yWidth, zWidth);
  glTexCoord2f(0.0f, tesselation + movement);
  glVertex3f(-xWidth, yWidth, -zWidth);
  glEnd();
}

void glDrawCube(float xWidth, float yWidth, float zWidth, int tesselation) {
  int normallength = -1;
  glBegin(GL_QUADS);
  // Front Face
  // glNormal3f( 0.0f, 0.0f, -normallength);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, 0.0f);
  glVertex3f(xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, tesselation);
  glVertex3f(xWidth, yWidth, zWidth);
  glTexCoord2f(0.0f, tesselation);
  glVertex3f(-xWidth, yWidth, zWidth);
  // Back Face
  // glNormal3f( 0.0f, 0.0f,normallength);
  glTexCoord2f(tesselation, 0.0f);
  glVertex3f(-xWidth, -yWidth, -zWidth);
  glTexCoord2f(tesselation, tesselation);
  glVertex3f(-xWidth, yWidth, -zWidth);
  glTexCoord2f(0.0f, tesselation);
  glVertex3f(xWidth, yWidth, -zWidth);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(xWidth, -yWidth, -zWidth);
  // Top Face
  // glNormal3f( 0.0f, -normallength, 0.0f);
  glTexCoord2f(0.0f, tesselation);
  glVertex3f(-xWidth, yWidth, -zWidth);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-xWidth, yWidth, zWidth);
  glTexCoord2f(tesselation, 0.0f);
  glVertex3f(xWidth, yWidth, zWidth);
  glTexCoord2f(tesselation, tesselation);
  glVertex3f(xWidth, yWidth, -zWidth);
  // Bottom Face
  // glNormal3f( 0.0f,normallength, 0.0f);
  glTexCoord2f(tesselation, tesselation);
  glVertex3f(-xWidth, -yWidth, -zWidth);
  glTexCoord2f(0.0f, tesselation);
  glVertex3f(xWidth, -yWidth, -zWidth);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, 0.0f);
  glVertex3f(-xWidth, -yWidth, zWidth);
  // Right face
  // glNormal3f( -normallength, 0.0f, 0.0f);
  glTexCoord2f(tesselation, 0.0f);
  glVertex3f(xWidth, -yWidth, -zWidth);
  glTexCoord2f(tesselation, tesselation);
  glVertex3f(xWidth, yWidth, -zWidth);
  glTexCoord2f(0.0f, tesselation);
  glVertex3f(xWidth, yWidth, zWidth);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(xWidth, -yWidth, zWidth);
  // Left Face
  // glNormal3f(normallength, 0.0f, 0.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-xWidth, -yWidth, -zWidth);
  glTexCoord2f(tesselation, 0.0f);
  glVertex3f(-xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, tesselation);
  glVertex3f(-xWidth, yWidth, zWidth);
  glTexCoord2f(0.0f, tesselation);
  glVertex3f(-xWidth, yWidth, -zWidth);
  glEnd();
}
