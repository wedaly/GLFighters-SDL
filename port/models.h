#pragma once

bool loadModels();
void freeModels();
void drawModel(int id);

const int MODEL_JETPACK_ID = 0;
const int MODEL_WALL_ID = 1;
const int MODEL_LIGHTNINGGUN_ID = 2;

void Machinegun(void);
void Grenade(void);
void Grenlauncher(void);
void LightSabre(void);
void Chunk(void);
void Sword(void);
void Rifle(void);
void LaserRifle(void);
void One(void);
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
