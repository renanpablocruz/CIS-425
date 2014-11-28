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
#include "Game.h"
#include "glutInclude.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Globals
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// screen
static Game* game = new Game();
static float scrW;
static float scrH;
// camera
static float camX = 0, camY = 0, camZ = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods - Headers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animation(int dt);
void changeCamera();
void drawScenario();
void drawScene();
void keyInput(unsigned char key, int scrX, int scrY);
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
	game->animate();
	glutPostRedisplay();
	glutTimerFunc(DELTA_T_REAL, animation, DELTA_T_VIRTUAL);
}

void changeCamera()
{
	if (game->hasAnySelectedTank(0)){ // player 1
		cout << game->hasAnySelectedTank(0) << endl;
		if (game->getStateOfTank(0) == WAITING)
			game->selectNextTank(0);
		else if (game->getStateOfTank(0) == SELECTING_TARGET)
		{
			if (game->hasAnySelectedTank(1))
				game->selectNextTank(1);
			else if (game->hasTanks(1)) 
				game->selectDefaultTank(1);
		}
	}
	else game->selectDefaultTank(0);
	glutPostRedisplay();
}

void drawScenario()
{
	if (game->hasAnySelectedTank(0))
	{
		game->getPosOfTheCurrentTank(camX, camY, camZ);
		gluLookAt(camX + 0.4, camY + 5, camZ + 5, camX, camY, camZ, 0, 1, 0);
	}
	else gluLookAt(2, 10, 10, 2, 0, 2, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game->draw();
}

void drawScene()
{
	// todo: configure light

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

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
			if (game->getStateOfTank(0) == WAITING) exit(0); // todo: open a menu
			else if (game->getStateOfTank(0) == SELECTING_TARGET) game->setWaitingMode(0);
			break;
		case 'c':
			changeCamera();
			break;
		case ' ':
			if (game->hasAnySelectedTank(0))
			{
				switch (game->getStateOfTank(0))
				{
					case WAITING:
						game->setTargetMode(0);
						game->selectDefaultTank(1);
						break;
					case SELECTING_TARGET:
						float x, y, z;
						game->getPosOfSelectedTank(1, x, y, z);
						game->shoot(0, x, y, z);
						break;
					default:
						break;
				}
			}
			break;
		case 'n':
			game->newTurn();
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void specialKeyInput(int key, int x, int y)
{
	int modifiers = glutGetModifiers();
	switch (key)
	{
		case GLUT_KEY_UP:
			if (game->hasAnySelectedTank(0))
			{
				switch (game->getStateOfTank(0))
				{
					case WAITING:
						game->moveTank(0, UP);
						break;
					case SELECTING_TARGET:

						break;
					default:
						break;
				}
			}
			break;
		case GLUT_KEY_DOWN:
			if (game->hasAnySelectedTank(0)) game->moveTank(0, DOWN);
			break;
		case GLUT_KEY_RIGHT:
			if (game->hasAnySelectedTank(0)) game->moveTank(0, RIGHT);
			break;
		case GLUT_KEY_LEFT:
			if (game->hasAnySelectedTank(0)) game->moveTank(0, LEFT);
			break;
		default:
			break;
	}
}

void printInteraction()
{

}
