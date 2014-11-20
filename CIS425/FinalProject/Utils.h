#ifndef UTILS_H
#define UTILS_H

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265358979324

enum elem{ FIRE, WATER, EARTH };
enum dir{ UP, DOWN, LEFT, RIGHT };

#endif
