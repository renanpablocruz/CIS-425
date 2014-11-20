#ifndef UTILS_H
#define UTILS_H

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265358979324
#define DELTA_T_REAL 50
#define DELTA_T_VIRTUAL 50
#define STEP 0.1
#define PRECISION STEP/10

enum elem{ FIRE, WATER, EARTH };
enum dir{ UP, DOWN, LEFT, RIGHT };

float absValue(float a);

#endif
