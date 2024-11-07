#include "textures.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>

static const int numTextures = 72;
static char *texturePaths[]{
    "./data/images/PenguinBody.bmp",
    "./data/images/PenguinFeet.bmp",
    "./data/images/Smoke.bmp",
    "./data/images/Marble.bmp",
    "./data/images/Blue/Torso.bmp",
    "./data/images/Bluepurple.bmp",
    "./data/images/Blue/Helmet.bmp",
    "./data/images/Blue/Upperarm.bmp",
    "./data/images/Blue/Lowerleg.bmp",
    "./data/images/Blue/Shoes.bmp",
    "./data/images/Rope.bmp",
    "./data/images/Grid.bmp",
    "./data/images/star.bmp",
    "./data/images/Red/Torso.bmp",
    "./data/images/Red/Shoes.bmp",
    "./data/images/Red/Helmet.bmp",
    "./data/images/Red/Upperarm.bmp",
    "./data/images/Red/Lowerleg.bmp",
    "./data/images/Green/Torso.bmp",
    "./data/images/Green/Shoes.bmp",
    "./data/images/Green/Helmet.bmp",
    "./data/images/Green/Upperarm.bmp",
    "./data/images/Green/Lowerleg.bmp",
    "./data/images/Yellow/Torso.bmp",
    "./data/images/Yellow/Shoes.bmp",
    "./data/images/Yellow/Helmet.bmp",
    "./data/images/Yellow/Upperarm.bmp",
    "./data/images/Yellow/Lowerleg.bmp",
    "./data/images/Metal.bmp",
    "./data/images/Matrix.bmp",
    "./data/images/MatrixDark.bmp",
    "./data/images/MetalMesh.bmp",
    "./data/images/LaserRifle.bmp",
    "./data/images/Black/Torso.bmp",
    "./data/images/Black/Shoes.bmp",
    "./data/images/Black/Helmet.bmp",
    "./data/images/Black/Upperarm.bmp",
    "./data/images/Black/Lowerleg.bmp",
    "./data/images/Laser.bmp",
    "./data/images/LaserFront.bmp",
    "./data/images/MachineGun.bmp",
    "./data/images/Sword.bmp",
    "./data/images/Rifle.bmp",
    "./data/images/Island/Right.bmp",
    "./data/images/Island/Back.bmp",
    "./data/images/Island/Left.bmp",
    "./data/images/Island/Front.bmp",
    "./data/images/Island/Down.bmp",
    "./data/images/Island/Up.bmp",
    "./data/images/JetPack.bmp",
    "./data/images/LightSabre.bmp",
    "./data/images/LightBlade.bmp",
    "./data/images/LightBladeFront.bmp",
    "./data/images/smokepuff.bmp",
    "./data/images/Lava/Right.bmp",
    "./data/images/Lava/Back.bmp",
    "./data/images/Lava/Left.bmp",
    "./data/images/Lava/Front.bmp",
    "./data/images/Lava/Down.bmp",
    "./data/images/Lava/Up.bmp",
    "./data/images/Snowy/Right.bmp",
    "./data/images/Snowy/Back.bmp",
    "./data/images/Snowy/Left.bmp",
    "./data/images/Snowy/Front.bmp",
    "./data/images/Snowy/Down.bmp",
    "./data/images/Snowy/Up.bmp",
    "./data/images/Grenskin.bmp",
    "./data/images/Grenade.bmp",
    "./data/images/LightningGun.bmp",
    "./data/images/Lightning.bmp",
    "./data/images/BladeTrail.bmp",
    "./data/images/Font.bmp",
};

static GLuint textureIDs[numTextures];

static void flipSurfaceVertically(SDL_Surface *surface) {
  SDL_LockSurface(surface);
  int pitch = surface->pitch;
  char *pixels = (char *)(surface->pixels);
  char tmp[pitch];

  for (int i = 0; i < surface->h / 2; i++) {
    char *row1 = pixels + i * pitch;
    char *row2 = pixels + (surface->h - i - 1) * pitch;
    memcpy(tmp, row1, pitch);
    memcpy(row1, row2, pitch);
    memcpy(row2, tmp, pitch);
  }
  SDL_UnlockSurface(surface);
}

static void swapRedAndBlue(SDL_Surface *surface) {
  SDL_LockSurface(surface);
  char *pixels = (char *)(surface->pixels);
  int bpp = surface->format->BytesPerPixel;
  int n = surface->w * surface->h * bpp;

  for (int i = 0; i < n; i += bpp) {
    char tmp = pixels[i];
    pixels[i] = pixels[i + 2];
    pixels[i + 2] = tmp;
  }

  SDL_UnlockSurface(surface);
}

static bool loadTextureFromImage(char *path, GLuint textureID) {
  SDL_Surface *surface = SDL_LoadBMP(path);
  if (surface == NULL) {
    printf("Error loading SDL surface from '%s'. SDL_Error: %s\n", path,
           SDL_GetError());
    return false;
  }

  flipSurfaceVertically(surface);
  swapRedAndBlue(surface);

  glBindTexture(GL_TEXTURE_2D, textureID);
  int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode,
               GL_UNSIGNED_BYTE, surface->pixels);
  SDL_FreeSurface(surface);
  return true;
}

bool loadTextures() {
  glGenTextures(numTextures, textureIDs);
  for (int i = 0; i < numTextures; i++) {
    if (!loadTextureFromImage(texturePaths[i], textureIDs[i])) {
      return false;
    }
  }
  return true;
}

void freeTextures() {
  glDeleteTextures(numTextures, textureIDs);
}

void bindTexture(int id) {
  glBindTexture(GL_TEXTURE_2D, textureIDs[id]);
}
