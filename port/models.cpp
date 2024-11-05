#include "models.h"
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glext.h>
#include <SDL2/SDL.h>
#include <cstdio>

void glDrawFloor(float xWidth, float yWidth, float zWidth, float movement);
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
void glDrawCube(float xWidth, float yWidth, float zWidth, int tesselation);
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

// TODO: update all these paths...
const int numModels = 3;
const char *modelPaths[numModels] = {
    "./data/models/JetPack",
    "./data/models/Wall",
    "./data/models/LightningGun",
};

GLuint vertexBufferObjIDs[numModels] = {0};

typedef struct {
	unsigned int numVertices;
	unsigned int numFloatsPerVertex;
} modelMetadata;

modelMetadata metadataForModel[numModels];

bool loadModelData(const char *path, GLuint vbo, unsigned int *numVerticesReturned) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    printf("Could not open model file %s\n", path);
    return false;
  }

  unsigned int numVertices = 0;
  size_t n = fread(&numVertices, sizeof(unsigned int), 1, f);
  if (n != 1) {
    printf("Could not read num vertices for model %s\n", path);
    fclose(f);
    return false;
  }
  numVertices = SDL_SwapBE32(numVertices);
  if (numVertices > 1000) {
    printf("Invalid num vertices for model %s\n", path);
    fclose(f);
    return false;
  }
	// TODO: load model meta with floats per vertex

  unsigned int numValues = numVertices * 8;
  float *vertexData = new float[numValues];
  float v = 0;
  for (int i = 0; i < numValues; i++) {
    // 3 tex coordinates
    // 2 normal coordinates
    // 3 vertex coordinates
    n = fread(&v, sizeof(float), 1, f);
    if (n != 1) {
      printf("Could not read model data for %s\n", path);
      fclose(f);
      delete vertexData;
      return false;
    }
    vertexData[i] = SDL_SwapFloatBE(v);
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, numValues * sizeof(float), vertexData, GL_STATIC_DRAW);
  delete vertexData;

  *numVerticesReturned = numVertices;
  return true;
}

bool loadModels() {
  glGenBuffers(numModels, vertexBufferObjIDs);

  for (int i = 0; i < numModels; i++) {
    const char *path = modelPaths[i];
    if (!loadModelData(path, vertexBufferObjIDs[i], &numVerticesForModel[i])) {
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
	// TODO: skip tex if numFloatsPerVertex == 5
  glTexCoordPointer(3, GL_FLOAT, 8 * sizeof(float), (void *)(0));
  glNormalPointer(GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  glVertexPointer(3, GL_FLOAT, 8 * sizeof(float), (void *)(5 * sizeof(float)));
  glDrawArrays(GL_TRIANGLES, 0, numVerticesForModel[id]);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
