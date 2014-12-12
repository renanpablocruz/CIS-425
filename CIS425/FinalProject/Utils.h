#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <string>
#include "glutInclude.h"
#include "Texture.h"

#define PI 3.14159265358979324
#define DELTA_T_REAL 50
#define DELTA_T_VIRTUAL 50
#define STEP 0.1
#define PRECISION STEP/10

enum elem{ FIRE, WATER, EARTH };
enum dir{ UP, DOWN, LEFT, RIGHT, NE, SE, SO, NO };
enum color{NONE, BLUE, RED, WHITE, BLACK, GRAY};

dir getDirForTank(float x1, float y1, float x2, float y2);
dir getDirForBullet(float x1, float y1, float x2, float y2);

float degToRad(double angInDeg);
void incAng(double& angInDeg);
void decAng(double& angInDeg);

float damageModifier(elem bulletType, elem tankType);

void drawBackground(color selColor = BLACK, float alpha = 1);
void drawButton(int xc, int yc, int w, int h, std::string input, void *font, color selColor = NONE);
void drawImage(int xc, int yc, int w, int h, typesOfTextures texture);
void drawWindow(int x, int y, int w, int h, color selColor = NONE);

void writeText2d(std::string input, float x, float y, bool centralize, void *font, color selColor = WHITE);
void writeText3d(std::string input, float x, float y, float z, bool centralize, void *font);

bool isInside(float x, float y, float xc, float yc, float w, float h);

#endif
