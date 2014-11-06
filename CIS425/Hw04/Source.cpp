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
static float ambX = 80;
static float ambY = 160;
static float ambZ = 20;
static bool light0On = true; // White light on?

void drawWallEdges(){
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(100, 100, 100);
	glutWireCube(200);
	glPopMatrix();
}

void drawWalls(){
	glColor3f(0.0, 0.0, 0.0);
	// todo material properties

	//south wall
	//glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(100, 100, 198);
	glScalef(1, 1, 2 / 100);
	glutSolidCube(200);
	glPopMatrix();
	//north wall
	//glColor3f(1.0, 0.0, 0.0);
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
	//Lighting

		// Light property vectors.
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec0[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightPos0[] = { ambX, ambY, ambZ, 1.0 };

		// Light0 properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);

	

		// Turn lights off/on.
	if (light0On) glEnable(GL_LIGHT0); else glDisable(GL_LIGHT0);

	// Draws
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

	gluLookAt(camX, camY, camZ, 100, 100, 0, 0, 1, 0);

	// Turn lights off to draw lamp and white edges
	glDisable(GL_LIGHTING);
	drawWallEdges();
	// draw bulb
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glPushMatrix();
	//glRotatef(xAngle, 1.0, 0.0, 0.0); // Rotation about x-axis.
	//glRotatef(yAngle, 0.0, 1.0, 0.0); // Rotation about z-axis.
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
	glColor3f(1.0, 1.0, 1.0);
	if (light0On) glutWireSphere(10, 8, 8);
	glPopMatrix();

	// Turn lights on again
	glEnable(GL_LIGHTING);
	drawWalls();

	glutSwapBuffers();
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
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	// Turn on OpenGL lighting.
	glEnable(GL_LIGHTING);

	// Material property vectors.
	float matAmbAndDif[] = { 0.0, 0.0, 1.0, 1.0 };
	float matSpec[] = { 1.0, 1.0, 1, 0, 1.0 };
	float matShine[] = { 50.0 };

	// Material properties of sphere.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	// Cull back faces.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


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
		case 'r':
			light0On = !light0On;
			glutPostRedisplay();
			break;
		case 't':
			ambX += 20;
			glutPostRedisplay();
			break;
		case 'g':
			ambX -= 20;
			glutPostRedisplay();
			break;
		case 'y':
			ambY += 20;
			glutPostRedisplay();
			break;
		case 'h':
			ambY -= 20;
			glutPostRedisplay();
			break;
		case 'u':
			ambZ += 20;
			glutPostRedisplay();
			break;
		case 'j':
			ambZ -= 20;
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
	cout << "Interactions:" << endl;
	cout << "Press q to increase camX" << endl;
	cout << "Press a to decrease camX" << endl;
	cout << "Press w to increase camY" << endl;
	cout << "Press s to decrease camY" << endl;
	cout << "Press e to increase camZ" << endl;
	cout << "Press d to decrease camZ" << endl;
	cout << "Press r to turn on/off the ambient light" << endl;
	cout << "Press t to increase ambX" << endl;
	cout << "Press g to decrease ambX" << endl;
	cout << "Press y to increase ambY" << endl;
	cout << "Press h to decrease ambY" << endl;
	cout << "Press u to increase ambZ" << endl;
	cout << "Press j to decrease ambZ" << endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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