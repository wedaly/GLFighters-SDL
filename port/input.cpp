#include "input.h"
#include <SDL2/SDL.h>

static const int numKeysTracked = 62;
static bool keyState[numKeysTracked] = {0};

int translateSDLEventToKeyID(SDL_KeyboardEvent &e) {
  SDL_Keycode keycode = e.keysym.sym;
  Uint16 mod = e.keysym.mod;
  bool shift = (mod & KMOD_LSHIFT) || (mod & KMOD_RSHIFT);

  if (keycode == 'a' && !shift) {
    return KEY_P1_LEFT_ID;
  } else if (keycode == 'd' && !shift) {
    return KEY_P1_RIGHT_ID;
  } else if (keycode == 's' && !shift) {
    return KEY_P1_DOWN_ID;
  } else if (keycode == 'w' && !shift) {
    return KEY_P1_UP_ID;
  } else if (keycode == 'q' && !shift) {
    return KEY_P1_SHOOT_LEFT_ID;
  } else if (keycode == 'e' && !shift) {
    return KEY_P1_SHOOT_RIGHT_ID;
  } else if (keycode == 'r' && !shift) {
    return KEY_P1_ATTACK_ID;
  } else if (keycode == 't' && !shift) {
    return KEY_P1_BLOCK_ID;
  } else if (keycode == 'y' && !shift) {
    return KEY_P1_TURN_OFF_JETPACK_ID;
  } else if (keycode == 'x' && !shift) {
    return KEY_P1_CLOAK_ID;
  } else if (keycode == SDLK_KP_4) {
    return KEY_P2_LEFT_ID;
  } else if (keycode == SDLK_KP_6) {
    return KEY_P2_RIGHT_ID;
  } else if (keycode == SDLK_KP_5) {
    return KEY_P2_DOWN_ID;
  } else if (keycode == SDLK_KP_8) {
    return KEY_P2_UP_ID;
  } else if (keycode == SDLK_KP_7) {
    return KEY_P2_SHOOT_LEFT_ID;
  } else if (keycode == SDLK_KP_9) {
    return KEY_P2_SHOOT_RIGHT_ID;
  } else if (keycode == SDLK_KP_0) {
    return KEY_P2_ATTACK_ID;
  } else if (keycode == SDLK_KP_ENTER) {
    return KEY_P2_BLOCK_ID;
  } else if (keycode == SDLK_KP_3) {
    return KEY_P2_TURN_OFF_JETPACK_ID;
  } else if (keycode == SDLK_KP_1) {
    return KEY_P2_CLOAK_ID;
  } else if (keycode == 'i' && !shift) {
    return KEY_CAMERA_UP_ID;
  } else if (keycode == 'k' && !shift) {
    return KEY_CAMERA_DOWN_ID;
  } else if (keycode == 'j' && !shift) {
    return KEY_CAMERA_LEFT_ID;
  } else if (keycode == 'l' && !shift) {
    return KEY_CAMERA_RIGHT_ID;
  } else if (keycode == SDLK_PAGEUP) {
    return KEY_CAMERA_ZOOM_IN_ID;
  } else if (keycode == SDLK_PAGEDOWN) {
    return KEY_CAMERA_ZOOM_OUT_ID;
  } else if (keycode == SDLK_LEFT) {
    return KEY_CAMERA_ROTATE_LEFT_ID;
  } else if (keycode == SDLK_RIGHT) {
    return KEY_CAMERA_ROTATE_RIGHT_ID;
  } else if (keycode == SDLK_UP) {
    return KEY_CAMERA_ROTATE_UP_ID;
  } else if (keycode == SDLK_DOWN) {
    return KEY_CAMERA_ROTATE_DOWN_ID;
  } else if (keycode == 'f' && shift) {
    return KEY_TOGGLE_FOG_ID;
  } else if (keycode == 'm' && !shift) {
    return KEY_TOGGLE_WIREFRAME_ID;
  } else if (keycode == 'm' && shift) {
    return KEY_MAP_TOGGLE_EDITOR_ID;
  } else if (keycode == 'n' && !shift) {
    return KEY_TOGGLE_BACKGROUND_ID;
  } else if (keycode == 'n' && shift) {
    return KEY_TOGGLE_SKINS_ID;
  } else if (keycode == 'b' && !shift) {
    return KEY_TOGGLE_SLOW_MOTION_ID;
  } else if (keycode == 'b' && shift) {
    return KEY_TOGGLE_FREEZE_TIME_ID;
  } else if (keycode == 'v' && !shift) {
    return KEY_TOGGLE_FREE_CAMERA_ID;
  } else if (keycode == 'z' && !shift) {
    return KEY_RESPAWN_PLAYER_CHARACTERS_ID;
  } else if (keycode == 'z' && shift) {
    return KEY_TOGGLE_P1_WEAPON_ID;
  } else if (keycode == 'v' && shift) {
    return KEY_TOGGLE_P2_WEAPON_ID;
  } else if (keycode == 'x' && shift) {
    return KEY_TOGGLE_PARTICLE_HAND_TRAILS_ID;
  } else if (keycode == 'a' && shift) {
    return KEY_TOGGLE_POLYGON_HAND_TRAILS_ID;
  } else if (keycode == 's' && shift) {
    return KEY_TOGGLE_SHOW_INFO_ID;
  } else if (keycode == 'l' && shift) {
    return KEY_TOGGLE_LIGHTNING_ID;
  } else if (keycode == 'u' && !shift) {
    return KEY_TOGGLE_JETPACKS_ID;
  } else if (keycode == 'u' && shift) {
    return KEY_TOGGLE_UNLIMITED_AMMO_ID;
  } else if (keycode == 'i' && shift) {
    return KEY_GIVE_9999_HEALTH_ID;
  } else if (keycode == 'c' && shift) {
    return KEY_TOGGLE_P1_AI_ID;
  } else if (keycode == 'd' && shift) {
    return KEY_TOGGLE_P2_AI_ID;
  } else if (keycode == 'o' && !shift) {
    return KEY_TOGGLE_OFFENSIVE_AI_ID;
  } else if (keycode == 'o' && shift) {
    return KEY_TOGGLE_AUTO_RESPAWN_ID;
  } else if (keycode == 'c' && !shift) {
    return KEY_TOGGLE_CHANGE_GRAVITY_AND_JUMP_HEIGHT_ID;
  } else if (keycode == '=' && !shift) {
    return KEY_TOGGLE_INC_GRAVITY_ID;
  } else if (keycode == '/' && !shift) {
    return KEY_TOGGLE_DEC_GRAVITY_ID;
  } else if (keycode == '-' && !shift) {
    return KEY_TOGGLE_INC_JUMP_HEIGHT_ID;
  } else if (keycode == '=' && shift) { // + (plus)
    return KEY_TOGGLE_DEC_JUMP_HEIGHT_ID;
  } else if (keycode == SDLK_TAB) {
    return KEY_TOGGLE_FIRSTPERSON_ID;
  } else if (keycode == SDLK_KP_2) {
    return KEY_MAP_SET_TILE_PLATFORM_WITH_ROPE_ID;
  } else if (keycode == '/' && shift) { // ? (question mark)
    return KEY_MAP_ERASE_EVERYTHING_ID;
  } else if (keycode == SDLK_KP_PLUS) {
    return KEY_MAP_CREATE_WALL_ID;
  } else if (keycode == SDLK_ESCAPE) {
    return KEY_QUIT_ID;
  }

  return -1;
}

void setKeyState(int keyID, bool pressed) {
  if (keyID >= 0 && keyID < numKeysTracked) {
    keyState[keyID] = pressed;
  }
}

bool isKeyDown(int keyID) {
  if (keyID >= 0 && keyID < numKeysTracked) {
    return keyState[keyID];
  } else {
    return false;
  }
}
