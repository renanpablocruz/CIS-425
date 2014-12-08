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

#define PI 3.14159265358979324

// screen
static Game* game = NULL;
static float scrW;
static float scrH;
// camera
static float camX = 0, camY = 0, camZ = 0, camR = 5;
static float camDirX = 0.4, camDirY = 5, camDirZ = 5;
static double phi = 30, theta = 180;

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
	glutTimerFunc(DELTA_T_REAL, update, DELTA_T_VIRTUAL);

	glutMainLoop();

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods - Declarations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void drawScenario()
{
	if (game->getGameState() == PLAYING)
	{
		if (game->activeBattalionHasAnySelectedTank())
		{
			game->getPosOfTheCurrentTank(camX, camY, camZ);
			gluLookAt(camX + camR*cos(degToRad(phi))*sin(degToRad(theta)), camY + camR*sin(degToRad(phi)), camZ - camR*cos(degToRad(phi))*cos(degToRad(theta)), camX, camY, camZ, 0, 1, 0);
		}
		else gluLookAt(2, 6, 10, 2, 0, 2, 0, 1, 0);
	}
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game->draw();
}

void drawScene()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	drawScenario();	

	glutSwapBuffers();
}

void keyInput(unsigned char key, int scrX, int scrY)
{

	if (game->getGameState() == PLAYING)
	{
		switch (key)
		{
			case 27: // ESC
				game->toggleMenu(GAME_MENU); // todo: open a menu
				break;
			case 8: // BSP
				if (game->getStateOfCurrentTank() == SELECTING_TARGET) game->targetToWaitingMode();
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
			case 'w':
				incAng(phi);
				break;
			case 'a':
				decAng(theta);
				break;
			case 's':
				decAng(phi);
				break;
			case 'd':
				incAng(theta);
				break;
			default:
				break;
		}
	}
	else if (game->getGameState() == MENU)
	{
		if (game->getMenu() == INITIAL_MENU)
		{
			switch (key)
			{
				case 'x':
					game->setMenu(NEW_GAME);
				default:
					break;
			}
		}
		else if (game->getMenu() == NEW_GAME)
		{
			switch (key)
			{
				case 'x':
					game->setMenu(INITIAL_MENU);
					break;
				case 'k':
					game->setNumPlayers(2);
					game->setState(PLAYING);
					game->setMenu(NO_MENU);
					break;
				case 'l':
					game->setNumPlayers(3);
					game->setState(PLAYING);
					game->setMenu(NO_MENU);
					break;
				default:
					break;
			}
		}
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
	game = new Game();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);  // normalize vectors for proper shading
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
