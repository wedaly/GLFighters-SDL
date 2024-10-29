#include "input.h"
#include <SDL2/SDL.h>

static const int numKeysTracked = 57;
static bool keyState[numKeysTracked] = {0};

int translateSDLEventToKeyID(SDL_KeyboardEvent &e) {
  switch (e.keysym.sym) {
  case 'a':
    return KEY_P1_LEFT_ID;

  case 'd':
    return KEY_P1_RIGHT_ID;

  case 's':
    return KEY_P1_DOWN_ID;

  case 'w':
    return KEY_P1_UP_ID;

  case 'q':
    return KEY_P1_SHOOT_LEFT_ID;

  case 'e':
    return KEY_P1_SHOOT_RIGHT_ID;

  case 'r':
    return KEY_P1_ATTACK_ID;

  case 't':
    return KEY_P1_BLOCK_ID;

  case 'y':
    return KEY_P1_TURN_OFF_JETPACK_ID;

  case 'x':
    return KEY_P1_CLOAK_ID;

  case SDLK_KP_4:
    return KEY_P2_LEFT_ID;

  case SDLK_KP_6:
    return KEY_P2_RIGHT_ID;

  case SDLK_KP_5:
    return KEY_P2_DOWN_ID;

  case SDLK_KP_8:
    return KEY_P2_UP_ID;

  case SDLK_KP_7:
    return KEY_P2_SHOOT_LEFT_ID;

  case SDLK_KP_9:
    return KEY_P2_SHOOT_RIGHT_ID;

  case SDLK_KP_0:
    return KEY_P2_ATTACK_ID;

  case SDLK_KP_ENTER:
    return KEY_P2_BLOCK_ID;

  case SDLK_KP_3:
    return KEY_P2_TURN_OFF_JETPACK_ID;

  case SDLK_KP_1:
    return KEY_P2_CLOAK_ID;

  case 'i':
    return KEY_CAMERA_UP_ID;

  case 'k':
    return KEY_CAMERA_DOWN_ID;

  case 'j':
    return KEY_CAMERA_LEFT_ID;

  case 'l':
    return KEY_CAMERA_RIGHT_ID;

  case SDLK_PAGEUP:
    return KEY_CAMERA_ZOOM_IN_ID;

  case SDLK_PAGEDOWN:
    return KEY_CAMERA_ZOOM_OUT_ID;

  case SDLK_LEFT:
    return KEY_CAMERA_ROTATE_LEFT_ID;

  case SDLK_RIGHT:
    return KEY_CAMERA_ROTATE_RIGHT_ID;

  case SDLK_UP:
    return KEY_CAMERA_ROTATE_UP_ID;

  case SDLK_DOWN:
    return KEY_CAMERA_ROTATE_DOWN_ID;

  case 'F':
    return KEY_TOGGLE_FOG_ID;

  case 'm':
    return KEY_TOGGLE_WIREFRAME_ID;

  case 'n':
    return KEY_TOGGLE_BACKGROUND_ID;

  case 'N':
    return KEY_TOGGLE_SKINS_ID;

  case 'b':
    return KEY_TOGGLE_SLOW_MOTION_ID;

  case 'B':
    return KEY_TOGGLE_FREEZE_TIME_ID;

  case 'v':
    return KEY_TOGGLE_FREE_CAMERA_ID;

  case 'z':
    return KEY_RESPAWN_PLAYER_CHARACTERS_ID;

  case 'Z':
    return KEY_TOGGLE_P1_WEAPON_ID;

  case 'V':
    return KEY_TOGGLE_P2_WEAPON_ID;

  case 'X':
    return KEY_TOGGLE_PARTICLE_HAND_TRAILS_ID;

  case 'A':
    return KEY_TOGGLE_POLYGON_HAND_TRAILS_ID;

  case 'S':
    return KEY_TOGGLE_SHOW_INFO_ID;

  case 'L':
    return KEY_TOGGLE_LIGHTNING_ID;

  case 'u':
    return KEY_TOGGLE_JETPACKS_ID;

  case 'U':
    return KEY_TOGGLE_UNLIMITED_AMMO_ID;

  case 'I':
    return KEY_GIVE_9999_HEALTH_ID;

  case 'C':
    return KEY_TOGGLE_P1_AI_ID;

  case 'D':
    return KEY_TOGGLE_P2_AI_ID;

  case 'o':
    return KEY_TOGGLE_OFFENSIVE_AI_ID;

  case 'O':
    return KEY_TOGGLE_AUTO_RESPAWN_ID;

  case 'c':
    return KEY_TOGGLE_CHANGE_GRAVITY_AND_JUMP_HEIGHT_ID;

  case '=':
    return KEY_TOGGLE_INC_GRAVITY_ID;

  case '/':
    return KEY_TOGGLE_DEC_GRAVITY_ID;

  case '-':
    return KEY_TOGGLE_INC_JUMP_HEIGHT_ID;

  case '+':
    return KEY_TOGGLE_DEC_JUMP_HEIGHT_ID;

	case SDLK_ESCAPE:
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
