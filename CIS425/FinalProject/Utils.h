#ifndef UTILS_H
#define UTILS_H

#include "glutInclude.h"
#include <string>

#define PI 3.14159265358979324
#define DELTA_T_REAL 50
#define DELTA_T_VIRTUAL 50
#define STEP 0.1
#define PRECISION STEP/10

enum elem{ FIRE, WATER, EARTH };
enum dir{ UP, DOWN, LEFT, RIGHT, NE, SE, SO, NO };
enum color{NONE, BLUE, RED};

dir getDirForTank(float x1, float y1, float x2, float y2);
dir getDirForBullet(float x1, float y1, float x2, float y2);

float degToRad(double angInDeg);
void incAng(double& angInDeg);
void decAng(double& angInDeg);

float damageModifier(elem bulletType, elem tankType);

void drawBlackBackground();
void drawWindow(int x, int y, int w, int h);

void writeText2d(std::string input, float x, float y, bool centralize, void *font);
void writeText3d(std::string input, float x, float y, float z, bool centralize, void *font);

#endif
