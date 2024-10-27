#include "textures.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static const int numTextures = 72;
static char *texturePaths[]{
    "./data/PenguinBody.bmp",
    "./data/PenguinFeet.bmp",
    "./data/Smoke.bmp",
    "./data/Marble.bmp",
    "./data/Blue/Torso.bmp",
    "./data/Bluepurple.bmp",
    "./data/Blue/Helmet.bmp",
    "./data/Blue/Upperarm.bmp",
    "./data/Blue/Lowerleg.bmp",
    "./data/Blue/Shoes.bmp",
    "./data/Rope.bmp",
    "./data/Grid.bmp",
    "./data/Star.bmp",
    "./data/Red/Torso.bmp",
    "./data/Red/Shoes.bmp",
    "./data/Red/Helmet.bmp",
    "./data/Red/Upperarm.bmp",
    "./data/Red/Lowerleg.bmp",
    "./data/Green/Torso.bmp",
    "./data/Green/Shoes.bmp",
    "./data/Green/Helmet.bmp",
    "./data/Green/Upperarm.bmp",
    "./data/Green/Lowerleg.bmp",
    "./data/Yellow/Torso.bmp",
    "./data/Yellow/Shoes.bmp",
    "./data/Yellow/Helmet.bmp",
    "./data/Yellow/Upperarm.bmp",
    "./data/Yellow/Lowerleg.bmp",
    "./data/Metal.bmp",
    "./data/Matrix.bmp",
    "./data/MatrixDark.bmp",
    "./data/MetalMesh.bmp",
    "./data/LaserRifle.bmp",
    "./data/Black/Torso.bmp",
    "./data/Black/Shoes.bmp",
    "./data/Black/Helmet.bmp",
    "./data/Black/Upperarm.bmp",
    "./data/Black/Lowerleg.bmp",
    "./data/Laser.bmp",
    "./data/LaserFront.bmp",
    "./data/MachineGun.bmp",
    "./data/Sword.bmp",
    "./data/Rifle.bmp",
    "./data/Island/Right.bmp",
    "./data/Island/Back.bmp",
    "./data/Island/Left.bmp",
    "./data/Island/Front.bmp",
    "./data/Island/Down.bmp",
    "./data/Island/Up.bmp",
    "./data/Jetpack.bmp",
    "./data/LightSabre.bmp",
    "./data/LightBlade.bmp",
    "./data/LightBladeFront.bmp",
    "./data/SmokePuff.bmp",
    "./data/Lava/Right.bmp",
    "./data/Lava/Back.bmp",
    "./data/Lava/Left.bmp",
    "./data/Lava/Front.bmp",
    "./data/Lava/Down.bmp",
    "./data/Lava/Up.bmp",
    "./data/Snowy/Right.bmp",
    "./data/Snowy/Back.bmp",
    "./data/Snowy/Left.bmp",
    "./data/Snowy/Front.bmp",
    "./data/Snowy/Down.bmp",
    "./data/Snowy/Up.bmp",
    "./data/Grenskin.bmp",
    "./data/Grenade.bmp",
    "./data/LightningGun.bmp",
    "./data/Lightning.bmp",
    "./data/BladeTrail.bmp",
    "./data/Font.bmp",
};

static GLuint textureIDs[numTextures];

static int loadTextureFromImage(char *path, GLuint textureID) {
  SDL_Surface *surface = IMG_Load(path);
  if (surface == NULL) {
    printf("Error loading SDL surface from '%s'. SDL_Error: %s\n", path,
           SDL_GetError());
    return 1;
  }

  glBindTexture(GL_TEXTURE_2D, textureID);
  int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode,
               GL_UNSIGNED_BYTE, surface->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  SDL_FreeSurface(surface);
  return 0;
}

int loadTextures() {
  glGenTextures(numTextures, textureIDs);
  for (int i = 0; i < numTextures; i++) {
    if (loadTextureFromImage(texturePaths[i], textureIDs[i]) != 0) {
      return 1;
    }
  }
  return 0;
}

void freeTextures() { glDeleteTextures(numTextures, textureIDs); }

void bindTexture(int id) { glBindTexture(GL_TEXTURE_2D, textureIDs[id]); }
