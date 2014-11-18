#ifndef UTILS_H
#define UTILS_H

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265358979324

float degToRad(double angInDeg);
void incAng(double& angInDeg);
void decAng(double& angInDeg);
float cosDiffAng(float u[], float v[], int length);
void delay(int sec);

#endif
