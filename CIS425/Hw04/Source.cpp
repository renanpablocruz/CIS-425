/******************************************
*
* Official Name:  Renan Cruz
*
* Nickname:  Pablo
*
* E-mail:  rrodr100@syr.edu
*
* Assignment:  Homework 4
*
* Environment/Compiler:  Visual Studio Pro 2013
*
* Date:  November 5, 2014
*
*******************************************/

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <time.h>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

// constants
#define PI 3.14159265358979324

using namespace std;

// Globals
static float scrW;
static float scrH;
static float camX = 100;
static float camY = 400;
static float camZ = 500;

void drawWalls(){
	//south wall
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(100, 100, 198);
	glScalef(1, 1, 2 / 100);
	glutSolidCube(200);
	glPopMatrix();
	//north wall
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(100, 100, 2);
	glScalef(1, 1, 2 / 100);
	glutSolidCube(200);
	glPopMatrix();
	//west wall
	//glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(2, 100, 100);
	glScalef(2 / 100, 1, 1);
	glutSolidCube(200);
	glPopMatrix();
	//east wall
	//glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(198, 100, 100);
	glScalef(2 / 100, 1, 1);
	glutSolidCube(200);
	glPopMatrix();
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

	gluLookAt(camX, camY, camZ, 100, 100, 0, 0, 1, 0);

	drawWalls();

	glFlush();
}

void resize(int w, int h)
{
	scrW = w;
	scrH = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.f, (double)w/h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void setup()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
}

void keyInput(unsigned char key, int scrX, int scrY)
{
	switch (key)
	{
		case 'q':
			camX += 20;
			glutPostRedisplay();
			break;
		case 'a':
			camX -= 20;
			glutPostRedisplay();
			break;
		case 'w':
			camY += 20;
			glutPostRedisplay();
			break;
		case 's':
			camY -= 20;
			glutPostRedisplay();
			break;
		case 'e':
			camZ += 20;
			glutPostRedisplay();
			break;
		case 'd':
			camZ -= 20;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

void mouseControl(int button, int state, int scrX, int scrY)
{

}

void mouseMotion(int scrX, int scrY)
{

}

void printInteraction()
{

}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Halloween House");
	setup();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);
	glutMotionFunc(mouseMotion);
	glutMainLoop();

	return 0;
}