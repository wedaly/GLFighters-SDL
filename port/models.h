#pragma once

bool loadModels();
void freeModels();
void drawModel(int id);

const int MODEL_JETPACK_ID = 0;
const int MODEL_WALL_ID = 1;
const int MODEL_LIGHTNINGGUN_ID = 2;
const int MODEL_MACHINEGUN_ID = 3;
const int MODEL_GRENADE_ID = 4;
const int MODEL_GRENLAUNCHER_ID = 5;
const int MODEL_LIGHTSABRE_ID = 6;
const int MODEL_CHUNK_ID = 7;
const int MODEL_SWORD_ID = 8;
const int MODEL_RIFLE_ID = 9;
const int MODEL_LASERRIFLE_ID = 10;

void glDrawFloor(float xWidth, float yWidth, float zWidth, float movement);
void glDrawCube(float xWidth, float yWidth, float zWidth, int tesselation);

void Head2(void);
void Head(void);
void Hand(void);
void Lowerarm(void);
void Upperarm(void);
void Upperleg(void);
void Foot(void);
void Floor(float movement);
void Lowerleg(void);
void Hip(void);
void Torso(void);
void Rope(void);
