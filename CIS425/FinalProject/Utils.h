#ifndef UTILS_H
#define UTILS_H

#include "glutInclude.h"

#define PI 3.14159265358979324
#define DELTA_T_REAL 50
#define DELTA_T_VIRTUAL 50
#define STEP 0.1
#define PRECISION STEP/10

enum elem{ FIRE, WATER, EARTH };
enum dir{ UP, DOWN, LEFT, RIGHT, NE, SE, SO, NO };

dir getDirForTank(float x1, float y1, float x2, float y2);
dir getDirForBullet(float x1, float y1, float x2, float y2);

#endif
