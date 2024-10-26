#include "sound.h"
#include <SDL2/SDL.h>

static SDL_AudioDeviceID deviceId;
static SDL_AudioSpec wavSpec;
static Uint32 wavLength;
static Uint8 *wavBuffer;

int loadSounds() {
  SDL_LoadWAV("data/sounds/140.Lightsabre.wav", &wavSpec, &wavBuffer,
              &wavLength);

  deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

  // TODO: error handling...
  return 0;
}

void freeSounds() {
  SDL_CloseAudioDevice(deviceId);
  SDL_FreeWAV(wavBuffer);
}

// TODO: volume...
int playSound(int id) {
  SDL_QueueAudio(deviceId, wavBuffer, wavLength);
  SDL_PauseAudioDevice(deviceId, 0);

  // TODO: error handling
  return 0;
}
