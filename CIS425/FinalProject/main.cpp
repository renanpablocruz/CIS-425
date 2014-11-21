/******************************************
*
* Official Name:  Renan Cruz
*
* Nickname:  Pablo
*
* E-mail:  rrodr100@syr.edu
*
* Assignment:  Final Project
*
* Environment/Compiler:  Visual Studio Pro 2013
*
*******************************************/

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "Tank.h"
#include "Panther.h"
#include "Panzer.h"
#include "Tiger.h"
#include "Bullet.h"
#include "PantherBullet.h"
#include "PanzerBullet.h"
#include "TigerBullet.h"
#include "Battalion.h"

#include "glutInclude.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Globals
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// screen
static Battalion* tanksUser1 = new Battalion(1);
static Battalion* tanksUser2 = new Battalion(2);
static float scrW;
static float scrH;
// camera
static float camX = 0, camY = 0, camZ = 0;
// picking and selecting
static bool isSelecting = false; // In selection mode?
static int hits; // Number of entries in hit buffer.
static unsigned int buffer[1024]; // Hit buffer.
static unsigned int closestName = 0; // Name of closest hit.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods - Headers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animation(int dt);
void changeCamera();
void defaultBullets();
void drawScenario();
void drawScene();
void drawTerrain();
void keyInput(unsigned char key, int scrX, int scrY);
void moveDown(int value);
void moveLeft(int value);
void moveRight(int value);
void moveUp(int value);
void printInteraction();
void resize(int w, int h);
void setup();
void specialKeyInput(int key, int x, int y);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Final Project");
	setup();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	//glutMouseFunc(pickFunction);
	glutSpecialFunc(specialKeyInput);
	glutTimerFunc(DELTA_T_REAL, animation, DELTA_T_VIRTUAL); // wait time miliseconds and execute function with argument value

	glutMainLoop();

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods - Declarations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animation(int dt)
{
	tanksUser1->animate(DELTA_T_VIRTUAL);
	tanksUser2->animate(DELTA_T_VIRTUAL);
	glutPostRedisplay();
	glutTimerFunc(DELTA_T_REAL, animation, DELTA_T_VIRTUAL);
}

void changeCamera()
{
	if (tanksUser1->hasTanks())
	{
		if (tanksUser1->anySelectedTank()){
			if (tanksUser1->getStateOfTank() == WAITING)
			{
				int ind = tanksUser1->selectedTank();
				tanksUser1->deselectTank(ind);
				if (ind != tanksUser1->numTanks() - 1) tanksUser1->selectTank(ind + 1);
			}
			else if (tanksUser1->getStateOfTank() == SELECTING_TARGET)
			{
				if (tanksUser2->anySelectedTank())
				{
					int ind = tanksUser2->selectedTank();
					tanksUser2->deselectTank(ind);
					tanksUser2->selectTank((ind + 1) % tanksUser2->numTanks());
				}
				else if (tanksUser2->hasTanks()) tanksUser2->selectTank(0);
			}
		}
		else  tanksUser1->selectTank(0);
		glutPostRedisplay();
	}
}

void defaultBullets()
{
	Bullet* testBullet = new PanzerBullet(EARTH, 0, 0, 0, 5, 0, 5, RIGHT);
	testBullet->draw();
}

void drawTerrain()
{
	if (isSelecting) glLoadName(1);
	glColor3f(0, 0, 0);
	int size = 20;
	for (int i = -size; i < size; i++)
	{
		for (int j = -size; j < size; j++) //for (int j = -size; j < size; j++)
		{
			glColor3f(0, 0, 0);
			glBegin(GL_LINE_STRIP);
			glVertex3f(i, 0, j);
			glVertex3f(i + 1, 0, j);
			glVertex3f(i + 1, 0, j + 1);
			glVertex3f(i, 0, j + 1);
			glEnd();

			if (i % 5 == 0 && j % 5 == 0) // markers
			{
				glColor3f(0.4, 0.4, 0.6);
				glPushMatrix();
				glTranslatef(0, 0.05, 0);
				glScalef(1, 0.1, 1);
				glTranslatef(i + 0.5, 0, j + 0.5);
				glutSolidCube(1);
				glPopMatrix();
			}
		}
	}
}

void drawScenario()
{
	if (tanksUser1->anySelectedTank())
	{
		if (tanksUser1->getStateOfTank() == WAITING) tanksUser1->getPosOfTank(tanksUser1->selectedTank(), camX, camY, camZ);
		else if (tanksUser1->getStateOfTank() == SELECTING_TARGET) tanksUser2->getPosOfTank(tanksUser2->selectedTank(), camX, camY, camZ);
		gluLookAt(camX + 0.4, camY + 5, camZ + 5, camX, camY, camZ, 0, 1, 0);
	}
	else gluLookAt(2, 10, 10, 2, 0, 2, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawTerrain();
	tanksUser1->draw();
	tanksUser2->draw();
	//defaultBullets();

	if (isSelecting) glPopName(); // Clear name stack.
}

void drawScene()
{
	// todo: configure light

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

	isSelecting = false;
	drawScenario();	

	glutSwapBuffers();
}

void resize(int w, int h)
{
	scrW = w;
	scrH = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0f, (double)w / h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void setup()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
}

void keyInput(unsigned char key, int scrX, int scrY)
{
	switch (key)
	{
		case 27:
			if (tanksUser1->getStateOfTank() == WAITING) exit(0); // todo: open a menu
			else if (tanksUser1->getStateOfTank() == SELECTING_TARGET) tanksUser1->setWaitingMode();
			break;
		case 'c':
			changeCamera();
			break;
		case ' ':
			if (tanksUser1->anySelectedTank())
			{
				switch (tanksUser1->getStateOfTank())
				{
					case WAITING:
						tanksUser1->setTargetMode();
						tanksUser2->selectFirstTank();
						break;
					case SELECTING_TARGET:
						float x, y, z;
						tanksUser2->getPosOfTank(tanksUser2->selectedTank(), x, y, z);
						tanksUser1->shoot(x, y, z);
						break;
					default:
						break;
				}
			}
			break;
		case 'n':
			tanksUser1->newTurn();
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void specialKeyInput(int key, int x, int y)
{
	int modifier = glutGetModifiers();
	switch (key)
	{
		case GLUT_KEY_UP:
			if (tanksUser1->anySelectedTank())
			{
				switch (tanksUser1->getStateOfTank())
				{
					case WAITING:
						tanksUser1->moveTank(UP);
						break;
					case SELECTING_TARGET:

						break;
					default:
						break;
				}
			}
			break;
		case GLUT_KEY_DOWN:
			if (tanksUser1->anySelectedTank()) tanksUser1->moveTank(DOWN);
			break;
		case GLUT_KEY_RIGHT:
			if (tanksUser1->anySelectedTank()) tanksUser1->moveTank(RIGHT);
			break;
		case GLUT_KEY_LEFT:
			if (tanksUser1->anySelectedTank()) tanksUser1->moveTank(LEFT);
			break;
		default:
			break;
	}
}

void printInteraction()
{

}

