#ifndef UTILS_H
#define UTILS_H

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265358979324
float degToRad(int angInDeg);
void incAng(int& angInDeg);
void decAng(int& angInDeg);
float cosDiffAng(float u[], float v[], int length);

#endif