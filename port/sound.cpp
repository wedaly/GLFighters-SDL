#include "sound.h"
#include <SDL2/SDL.h>

static SDL_AudioDeviceID deviceId;
static SDL_AudioSpec wavSpec;
static Uint32 wavLength;
static Uint8 *wavBuffer;

int loadSounds() {
  deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	if (deviceId < 0) {
		printf("SDL could not open audio device. SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

  if (SDL_LoadWAV("data/sounds/140.Lightsabre.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {
		printf("SDL could not load audio file. SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

  return 0;
}

void freeSounds() {
	if (deviceId > 0) {
	  SDL_CloseAudioDevice(deviceId);
	}

	if (wavBuffer != NULL) {
	  SDL_FreeWAV(wavBuffer);
	}
}

void playSound(int id) {
	SDL_ClearQueuedAudio(deviceId);

  if (SDL_QueueAudio(deviceId, wavBuffer, wavLength) < 0) {
		printf("SDL could not queue audio. SDL_Error: %s\n", SDL_GetError());
	}

  SDL_PauseAudioDevice(deviceId, 0); // 0 means unpause = start playing
}
