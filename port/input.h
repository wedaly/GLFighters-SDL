#pragma once
#include <SDL2/SDL.h>

int translateSDLEventToKeyID(SDL_KeyboardEvent &e); // -1 if not tracked.
void setKeyState(int keyID, bool pressed);
bool isKeyDown(int keyID);

const int KEY_P1_LEFT_ID = 0;
const int KEY_P1_RIGHT_ID = 1;
const int KEY_P1_DOWN_ID = 2;
const int KEY_P1_UP_ID = 3;
const int KEY_P1_SHOOT_LEFT_ID = 4;
const int KEY_P1_SHOOT_RIGHT_ID = 5;
const int KEY_P1_ATTACK_ID = 6;
const int KEY_P1_BLOCK_ID = 7;
const int KEY_P1_TURN_OFF_JETPACK_ID = 8;
const int KEY_P1_CLOAK_ID = 9;

const int KEY_P2_LEFT_ID = 10;
const int KEY_P2_RIGHT_ID = 11;
const int KEY_P2_DOWN_ID = 12;
const int KEY_P2_UP_ID = 13;
const int KEY_P2_SHOOT_LEFT_ID = 14;
const int KEY_P2_SHOOT_RIGHT_ID = 15;
const int KEY_P2_ATTACK_ID = 16;
const int KEY_P2_BLOCK_ID = 17;
const int KEY_P2_TURN_OFF_JETPACK_ID = 18;
const int KEY_P2_CLOAK_ID = 19;

const int KEY_CAMERA_UP_ID = 20;
const int KEY_CAMERA_DOWN_ID = 21;
const int KEY_CAMERA_LEFT_ID = 22;
const int KEY_CAMERA_RIGHT_ID = 23;
const int KEY_CAMERA_ZOOM_IN_ID = 24;
const int KEY_CAMERA_ZOOM_OUT_ID = 25;
const int KEY_CAMERA_ROTATE_LEFT_ID = 26;
const int KEY_CAMERA_ROTATE_RIGHT_ID = 27;
const int KEY_CAMERA_ROTATE_UP_ID = 28;
const int KEY_CAMERA_ROTATE_DOWN_ID = 29;

const int KEY_TOGGLE_FOG_ID = 30;
const int KEY_TOGGLE_WIREFRAME_ID = 31;
const int KEY_TOGGLE_BACKGROUND_ID = 32;
const int KEY_TOGGLE_SKINS_ID = 33;
const int KEY_TOGGLE_SLOW_MOTION_ID = 34;
const int KEY_TOGGLE_FREEZE_TIME_ID = 35;
const int KEY_TOGGLE_FREE_CAMERA_ID = 36;
const int KEY_RESPAWN_PLAYER_CHARACTERS_ID = 37;
const int KEY_TOGGLE_P1_WEAPON_ID = 38;
const int KEY_TOGGLE_P2_WEAPON_ID = 39;
const int KEY_TOGGLE_PARTICLE_HAND_TRAILS_ID = 40;
const int KEY_TOGGLE_POLYGON_HAND_TRAILS_ID = 41;
const int KEY_TOGGLE_SHOW_INFO_ID = 42;
const int KEY_TOGGLE_LIGHTING_ID = 43;
const int KEY_TOGGLE_JETPACKS_ID = 44;
const int KEY_TOGGLE_UNLIMITED_AMMO_ID = 45;
const int KEY_GIVE_9999_HEALTH_ID = 46;

const int KEY_TOGGLE_P1_AI_ID = 47;
const int KEY_TOGGLE_P2_AI_ID = 48;
const int KEY_TOGGLE_OFFENSIVE_AI_ID = 49;
const int KEY_TOGGLE_AUTO_RESPAWN_ID = 50;

const int KEY_TOGGLE_CHANGE_GRAVITY_AND_JUMP_HEIGHT_ID = 51;
const int KEY_TOGGLE_INC_GRAVITY_ID = 52;
const int KEY_TOGGLE_DEC_GRAVITY_ID = 53;
const int KEY_TOGGLE_INC_JUMP_HEIGHT_ID = 54;
const int KEY_TOGGLE_DEC_JUMP_HEIGHT_ID = 55;

const int KEY_TOGGLE_FIRSTPERSON_ID = 56;

// Map keys
const int KEY_MAP_TOGGLE_EDITOR_ID = 57;
const int KEY_MAP_ERASE_ID = KEY_P2_ATTACK_ID;            // both keypad 0
const int KEY_MAP_SET_TILE_PLATFORM_ID = KEY_P2_CLOAK_ID; // both keypad 1
const int KEY_MAP_SET_TILE_PLATFORM_WITH_ROPE_ID = 58;
const int KEY_MAP_SET_TILE_ROPE_ID = KEY_P2_TURN_OFF_JETPACK_ID;       // both keypad 3
const int KEY_MAP_SELECTION_UP_ID = KEY_P2_UP_ID;                      // both keypad 8
const int KEY_MAP_SELECTION_DOWN_ID = KEY_P2_DOWN_ID;                  // both keypad 5
const int KEY_MAP_SELECTION_LEFT_ID = KEY_P2_LEFT_ID;                  // both keypad 4
const int KEY_MAP_SELECTION_RIGHT_ID = KEY_P2_RIGHT_ID;                // both keypad 6
const int KEY_MAP_CREATE_SPAWNPOINT_ID = KEY_P2_SHOOT_LEFT_ID;         // both keypad 7
const int KEY_MAP_CHANGE_SPAWNPOINT_NUMBER_ID = KEY_P2_SHOOT_RIGHT_ID; // both keypad 9
const int KEY_MAP_ERASE_EVERYTHING_ID = 59;
const int KEY_MAP_CREATE_WALL_ID = 60;
