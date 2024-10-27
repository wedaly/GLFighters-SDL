#include "sound.h"
#include <SDL2/SDL.h>

static const int numSoundClips = 31;
static char *soundClipPaths[] = {
    "./data/sounds/128.Roll.wav",
    "./data/sounds/129.Step.wav",
    "./data/sounds/130.Land.wav",
    "./data/sounds/131.Break.wav",
    "./data/sounds/132.Break2.wav",
    "./data/sounds/133.Zap.wav",
    "./data/sounds/134.Boom.wav",
    "./data/sounds/135.Snap.wav",
    "./data/sounds/136.Metalslide.wav",
    "./data/sounds/137.MetalSlide2.wav",
    "./data/sounds/138.MachineGun.wav",
    "./data/sounds/139.Jetpack.wav",
    "./data/sounds/140.Lightsabre.wav",
    "./data/sounds/141.Bink.wav",
    "./data/sounds/142.Gunshot1.wav",
    "./data/sounds/143.Gunshot2.wav",
    "./data/sounds/144.Gunshot3.wav",
    "./data/sounds/145.Grenlaunch2.wav",
    "./data/sounds/146.mgunshot1sys7.wav",
    "./data/sounds/147.mgunshot2sys7.wav",
    "./data/sounds/148.mgunshot3sys7.wav",
    "./data/sounds/149.BigBoom.wav",
    "./data/sounds/150.Lightningsys7.wav",
    "./data/sounds/151.Lightninglowsys7.wav",
    "./data/sounds/152.Lightninghighsys7.wav",
    "./data/sounds/153.woosh1sys7.wav",
    "./data/sounds/154.woosh2sys7.wav",
    "./data/sounds/155.woosh3sys7.wav",
    "./data/sounds/156.Saber3sys7.wav",
    "./data/sounds/157.Saber1sys7.wav",
    "./data/sounds/158.Saber2sys7.wav",
};

typedef struct {
  SDL_AudioSpec wavSpec;
  Uint32 wavLength;
  Uint8 *wavBuffer;
} soundClip;

static SDL_AudioDeviceID deviceId;
static soundClip soundClips[numSoundClips];

bool loadSounds() {
  for (int i = 0; i < numSoundClips; i++) {
    char *path = soundClipPaths[i];
    soundClip *sc = &(soundClips[i]);
    sc->wavBuffer = NULL;
    sc->wavLength = 0;

    if (SDL_LoadWAV(path, &sc->wavSpec, &sc->wavBuffer, &sc->wavLength) ==
        NULL) {
      printf("SDL could not load audio file from '%s'. SDL_Error: %s\n", path,
             SDL_GetError());
      return false;
    }
  }

  deviceId = SDL_OpenAudioDevice(NULL, 0, &soundClips[0].wavSpec, NULL, 0);
  if (deviceId < 0) {
    printf("SDL could not open audio device. SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

void freeSounds() {
  if (deviceId > 0) {
    SDL_CloseAudioDevice(deviceId);
  }

  for (int i = 0; i < numSoundClips; i++) {
    Uint8 *wavBuffer = soundClips[i].wavBuffer;
    if (wavBuffer != NULL) {
      SDL_FreeWAV(wavBuffer);
    }
  }
}

void playSound(int id) {
  if (id < 0 || id >= numSoundClips) {
    printf("Invalid sound ID %d\n", id);
    return;
  }

  SDL_ClearQueuedAudio(deviceId);

  soundClip *sc = &soundClips[id];
  if (SDL_QueueAudio(deviceId, sc->wavBuffer, sc->wavLength) < 0) {
    printf("SDL could not queue audio. SDL_Error: %s\n", SDL_GetError());
  }

  SDL_PauseAudioDevice(deviceId, 0); // 0 means unpause = start playing
}
