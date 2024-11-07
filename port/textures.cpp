#include "textures.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static const int numTextures = 72;
static char *texturePaths[]{
    "./data/images/PenguinBody.tga",
    "./data/images/PenguinFeet.tga",
    "./data/images/Smoke.tga",
    "./data/images/Marble.tga",
    "./data/images/Blue/Torso.tga",
    "./data/images/Bluepurple.tga",
    "./data/images/Blue/Helmet.tga",
    "./data/images/Blue/Upperarm.tga",
    "./data/images/Blue/Lowerleg.tga",
    "./data/images/Blue/Shoes.tga",
    "./data/images/Rope.tga",
    "./data/images/Grid.tga",
    "./data/images/star.tga",
    "./data/images/Red/Torso.tga",
    "./data/images/Red/Shoes.tga",
    "./data/images/Red/Helmet.tga",
    "./data/images/Red/Upperarm.tga",
    "./data/images/Red/Lowerleg.tga",
    "./data/images/Green/Torso.tga",
    "./data/images/Green/Shoes.tga",
    "./data/images/Green/Helmet.tga",
    "./data/images/Green/Upperarm.tga",
    "./data/images/Green/Lowerleg.tga",
    "./data/images/Yellow/Torso.tga",
    "./data/images/Yellow/Shoes.tga",
    "./data/images/Yellow/Helmet.tga",
    "./data/images/Yellow/Upperarm.tga",
    "./data/images/Yellow/Lowerleg.tga",
    "./data/images/Metal.tga",
    "./data/images/Matrix.tga",
    "./data/images/MatrixDark.tga",
    "./data/images/MetalMesh.tga",
    "./data/images/LaserRifle.tga",
    "./data/images/Black/Torso.tga",
    "./data/images/Black/Shoes.tga",
    "./data/images/Black/Helmet.tga",
    "./data/images/Black/Upperarm.tga",
    "./data/images/Black/Lowerleg.tga",
    "./data/images/Laser.tga",
    "./data/images/LaserFront.tga",
    "./data/images/MachineGun.tga",
    "./data/images/Sword.tga",
    "./data/images/Rifle.tga",
    "./data/images/Island/Right.tga",
    "./data/images/Island/Back.tga",
    "./data/images/Island/Left.tga",
    "./data/images/Island/Front.tga",
    "./data/images/Island/Down.tga",
    "./data/images/Island/Up.tga",
    "./data/images/JetPack.tga",
    "./data/images/LightSabre.tga",
    "./data/images/LightBlade.tga",
    "./data/images/LightBladeFront.tga",
    "./data/images/smokepuff.tga",
    "./data/images/Lava/Right.tga",
    "./data/images/Lava/Back.tga",
    "./data/images/Lava/Left.tga",
    "./data/images/Lava/Front.tga",
    "./data/images/Lava/Down.tga",
    "./data/images/Lava/Up.tga",
    "./data/images/Snowy/Right.tga",
    "./data/images/Snowy/Back.tga",
    "./data/images/Snowy/Left.tga",
    "./data/images/Snowy/Front.tga",
    "./data/images/Snowy/Down.tga",
    "./data/images/Snowy/Up.tga",
    "./data/images/Grenskin.tga",
    "./data/images/Grenade.tga",
    "./data/images/LightningGun.tga",
    "./data/images/Lightning.tga",
    "./data/images/BladeTrail.tga",
    "./data/images/Font.tga",
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
  SDL_Surface *surface = IMG_Load(path);
  if (surface == NULL) {
    printf("Error loading SDL surface from '%s'. SDL_Error: %s\n", path,
           IMG_GetError());
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
