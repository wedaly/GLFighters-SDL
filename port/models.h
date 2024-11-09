#pragma once

bool loadModels();
void freeModels();
void drawModel(int id, bool wireframe);
void glDrawFloor(float xWidth, float yWidth, float zWidth, float movement);
void glDrawCube(float xWidth, float yWidth, float zWidth, int tesselation);

const int MODEL_CHUNK_ID = 0;
const int MODEL_FLOOR_ID = 1;
const int MODEL_FOOT_ID = 2;
const int MODEL_GRENADE_ID = 3;
const int MODEL_GRENLAUNCHER_ID = 4;
const int MODEL_HAND_ID = 5;
const int MODEL_HEAD_ID = 6;
const int MODEL_HEAD2_ID = 7;
const int MODEL_HIP_ID = 8;
const int MODEL_JETPACK_ID = 9;
const int MODEL_LASERRIFLE_ID = 10;
const int MODEL_LIGHTNINGGUN_ID = 11;
const int MODEL_LIGHTSABRE_ID = 12;
const int MODEL_LOWERARM_ID = 13;
const int MODEL_LOWERLEG_ID = 14;
const int MODEL_MACHINEGUN_ID = 15;
const int MODEL_ONE_ID = 16;
const int MODEL_RIFLE_ID = 17;
const int MODEL_ROPE_ID = 18;
const int MODEL_SWORD_ID = 19;
const int MODEL_TORSO_ID = 20;
const int MODEL_UPPERARM_ID = 21;
const int MODEL_UPPERLEG_ID = 22;
const int MODEL_WALL_ID = 23;
