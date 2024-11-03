#include "sound.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

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

static Mix_Chunk *soundClips[numSoundClips] = {NULL};

bool loadSounds() {
  const int audio_rate = 48000; // match sample rate of the audio files.
  const int audio_format = MIX_DEFAULT_FORMAT;
  const int audio_channels = 1;
  const int audio_chunksize = 4096;

  if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_chunksize) < 0) {
    printf("SDL_Mixer could not open audio. SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  for (int i = 0; i < numSoundClips; i++) {
    char *path = soundClipPaths[i];
    soundClips[i] = Mix_LoadWAV(path);
    if (soundClips[i] == NULL) {
      printf("SDL_Mixer could not load audio file from '%s'. SDL_Error: %s\n", path,
             SDL_GetError());
      return false;
    }
  }

  return true;
}

void freeSounds() {
  for (int i = 0; i < numSoundClips; i++) {
    if (soundClips[i] != NULL) {
      Mix_FreeChunk(soundClips[i]);
    }
  }

  Mix_CloseAudio();
}

// TODO: implement volume
void playSound(int id, int volume) {
  if (id < 0 || id >= numSoundClips) {
    printf("Invalid sound ID %d\n", id);
    return;
  }

  if (Mix_PlayChannel(0, soundClips[id], 0) < 0) {
    printf("SDL could not play audio clip %d. SDL_Error: %s\n", id, SDL_GetError());
  }
}
