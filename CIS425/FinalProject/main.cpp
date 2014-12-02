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
#include <iostream>
#include <cmath>
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

void drawScenario();
void drawScene();
void keyInput(unsigned char key, int scrX, int scrY);
void printInteraction();
void resize(int w, int h);
void selectFocus();
void setup();
void specialKeyInput(int key, int x, int y);
void update(int dt);

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
	glutTimerFunc(DELTA_T_REAL, update, DELTA_T_VIRTUAL); // wait time miliseconds and execute function with argument value

	glutMainLoop();

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods - Declarations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void drawScenario()
{
	if (game->activeBattalionHasAnySelectedTank())
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

void keyInput(unsigned char key, int scrX, int scrY)
{
	switch (key)
	{
		case 27:
			if (game->getStateOfCurrentTank() == WAITING) exit(0); // todo: open a menu
			else if (game->getStateOfCurrentTank() == SELECTING_TARGET) game->setCurrentTankToWaitingMode();
			break;
		case 'c':
			selectFocus();
			break;
		case ' ':
			if (game->currentPlayerHasAnySelectedTank())
			{
				switch (game->getStateOfCurrentTank())
				{
					case WAITING:
						game->setCurrentTankToTargetMode();
						game->selectDefaultTankForTheCurrentTargetPlayer();
						break;
					case SELECTING_TARGET:
						game->shoot();
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

void printInteraction()
{

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

void selectFocus()
{
	game->selectFocus();
	glutPostRedisplay();
}

void setup()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
}

void specialKeyInput(int key, int x, int y)
{
	int modifiers = glutGetModifiers();
	switch (key)
	{
		case GLUT_KEY_UP:
			if (game->currentPlayerHasAnySelectedTank())
			{
				switch (game->getStateOfCurrentTank())
				{
					case WAITING:
						game->moveCurrentTank(UP);
						break;
					case SELECTING_TARGET:

						break;
					default:
						break;
				}
			}
			break;
		case GLUT_KEY_DOWN:
			if (game->currentPlayerHasAnySelectedTank()) game->moveCurrentTank(DOWN);
			break;
		case GLUT_KEY_RIGHT:
			if (game->currentPlayerHasAnySelectedTank()) game->moveCurrentTank(RIGHT);
			break;
		case GLUT_KEY_LEFT:
			if (game->currentPlayerHasAnySelectedTank()) game->moveCurrentTank(LEFT);
			break;
		default:
			break;
	}
}

void update(int dt)
{
	game->update();
	glutPostRedisplay();
	glutTimerFunc(DELTA_T_REAL, update, DELTA_T_VIRTUAL);
}
