#pragma once

bool createFont(int textureID);
void freeFont();
void printToScreen(int x, int y, const char *s, bool italicize, float size, int screenwidth, int screenheight);
