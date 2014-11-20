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
#include <vector>
#include "Tank.h"
#include "Panther.h"
#include "Panzer.h"
#include "Tiger.h"
#include "Bullet.h"
#include "PantherBullet.h"
#include "PanzerBullet.h"
#include "TigerBullet.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Globals
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// screen
static vector<Tank*> tanksUser1;
static vector<Tank*> tanksUser2;
static float scrW;
static float scrH;
// camera
static float camX = 0, camY = 0, camZ = 0;
static vector<bool> selectedTankUser1;
// picking and selecting
static bool isSelecting = false; // In selection mode?
static int hits; // Number of entries in hit buffer.
static unsigned int buffer[1024]; // Hit buffer.
static unsigned int closestName = 0; // Name of closest hit.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods - Headers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool anyselectedTank();
void defaultBullets();
void defaultTanks();
void drawScenario();
void drawScene();
void drawTanks();
void drawTerrain();
void findClosestHit(int hits, unsigned int buffer[]);
void keyInput(unsigned char key, int scrX, int scrY);
void moveDown(int value);
void moveLeft(int value);
void moveRight(int value);
void moveUp(int value);
void newTurn();
void printInteraction();
void resize(int w, int h);
int selectedTank();
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
	// todo: glutTimerFunc(time, function, value); // wait time miliseconds and execute function with argument value

	glutMainLoop();

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods - Declarations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool anyselectedTank()
{
	for (unsigned int i = 0; i < selectedTankUser1.size(); i++)
	{
		if (selectedTankUser1[i]) return true;
	}
	return false;
}

int selectedTank() // only make sense to call if anyselectedTank returned true
{
	for (unsigned int i = 0; i < selectedTankUser1.size(); i++)
	{
		if (selectedTankUser1[i]) return i;
	}
	return -1;
}

void defaultBullets()
{
	Bullet* testBullet = new PanzerBullet(EARTH, 0, 0, 0);
	testBullet->draw();
}

void defaultTanks()
{
	Panzer* firstTank = new Panzer(EARTH); // user1
	firstTank->setPos(0, 0, 0);
	tanksUser1.push_back(firstTank);
	selectedTankUser1.push_back(true);

	firstTank = new Panzer(WATER);
	firstTank->setPos(0, 0, 2);
	tanksUser1.push_back(firstTank);
	selectedTankUser1.push_back(false);

	firstTank = new Panzer(FIRE);
	firstTank->setPos(0, 0, 4);
	tanksUser1.push_back(firstTank);
	selectedTankUser1.push_back(false);

	firstTank = new Panzer(EARTH); // user2
	firstTank->setPos(3, 0, 0);
	tanksUser2.push_back(firstTank);
	
	firstTank = new Panzer(WATER);
	firstTank->setPos(3, 0, 2);
	tanksUser2.push_back(firstTank);
	
	firstTank = new Panzer(FIRE);
	firstTank->setPos(3, 0, 4);
	tanksUser2.push_back(firstTank);
}

void drawTanks()
{
	cout << "num of tanks: " << tanksUser1.size() << endl;
	for (unsigned int i = 0; i < tanksUser1.size(); i++)
	{
		//if (isSelecting) glLoadName(i+2);
		tanksUser1[i]->draw();
	}
	for (unsigned int i = 0; i < tanksUser2.size(); i++)
	{
		//if (isSelecting) glLoadName(i+2);
		tanksUser2[i]->draw();
	}
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
				glTranslatef(i+0.5, 0, j+0.5);
				glutSolidCube(1);
				glPopMatrix();
			}
		}
	}
}

void drawScenario()
{
	if (anyselectedTank())
	{
		tanksUser1[selectedTank()]->getPos(camX, camY, camZ);
		gluLookAt(camX + 5, camY + 5, camZ + 5, camX, camY, camZ, 0, 1, 0);
	}
	else gluLookAt(10, 10, 10, 2, 0, 2, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawTerrain();
	//drawTanks();
	defaultBullets();

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
	//glLoadIdentity();

	//defaultTanks();
}

void keyInput(unsigned char key, int scrX, int scrY)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
		case 't':
			defaultTanks();
			glutPostRedisplay();
			break;
		case ' ':
			if (tanksUser1.size() > 0)
			{
				if (anyselectedTank()){
					int ind = selectedTank();
					selectedTankUser1[ind] = false;
					if (ind != selectedTankUser1.size() - 1) selectedTankUser1[ind + 1] = true;
				}
				else  selectedTankUser1[0] = true;
				glutPostRedisplay();
			}
			break;
		case 'n':
			newTurn();
			break;
		default:
			break;
	}
}

void moveUp(int value)
{
	if (value == 5)
	{
		if (!tanksUser1[selectedTank()]->canMov()) return;
	}
	else if (value == 0) return;
	if (anyselectedTank())
	{
		tanksUser1[selectedTank()]->move(UP);
		glutTimerFunc(50, moveUp, --value);
		glutPostRedisplay();
	}
}

void moveDown(int value)
{
	if (value == 5)
	{
		if (!tanksUser1[selectedTank()]->canMov()) return;
	}
	else if (value == 0) return;
	if (anyselectedTank())
	{
		tanksUser1[selectedTank()]->move(DOWN);
		glutTimerFunc(50, moveDown, --value);
		glutPostRedisplay();
	}
}

void moveRight(int value)
{
	if (value == 5)
	{
		if (!tanksUser1[selectedTank()]->canMov()) return;
	}
	else if (value == 0) return;
	if (anyselectedTank())
	{
		tanksUser1[selectedTank()]->move(RIGHT);
		glutTimerFunc(50, moveRight, --value);
		glutPostRedisplay();
	}
}

void moveLeft(int value)
{
	if (value == 5)
	{
		if (!tanksUser1[selectedTank()]->canMov()) return;
	}
	else if (value == 0) return;
	if (anyselectedTank())
	{
		tanksUser1[selectedTank()]->move(LEFT);
		glutTimerFunc(50, moveLeft, --value);
		glutPostRedisplay();
	}
}

void specialKeyInput(int key, int x, int y)
{
	int modifier = glutGetModifiers();
	switch (key)
	{
		case GLUT_KEY_UP:
			glutTimerFunc(50, moveUp, 5);
			break;
		case GLUT_KEY_DOWN:
			glutTimerFunc(50, moveDown, 5);
			break;
		case GLUT_KEY_RIGHT:
			glutTimerFunc(50, moveRight, 5);
			break;
		case GLUT_KEY_LEFT:
			glutTimerFunc(50, moveLeft, 5);
			break;
		default:
			break;
	}
}

void findClosestHit(int hits, unsigned int buffer[])
{
	unsigned int *ptr, minZ;

	minZ = 0xffffffff; //minZ = 0xffffffff;
	ptr = buffer;
	closestName = 0;
	for (int i = 0; i < hits; i++)
	{
		ptr++;
			cout << "Z: " << *ptr << endl;
			ptr += 2;
			cout << "name of intersections: " << *ptr << endl;
			ptr -= 2;
		if (*ptr < minZ) //if (*ptr < minZ)
		{
			minZ = *ptr;
			ptr += 2;
			closestName = *ptr;
			ptr++;
		}
		else ptr += 3;
	}
		cout << "hits: " << hits << endl;
		cout << "clicked at " << closestName << endl << endl;
}

void pickFunction(int button, int state, int x, int y)
{
	int viewport[4];

	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

	glGetIntegerv(GL_VIEWPORT, viewport);

	glSelectBuffer(1024, buffer);
	(void)glRenderMode(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	gluPickMatrix((float)x, (float)(viewport[3] - y), 3.0, 3.0, viewport);
	gluPerspective(80.0f, (double)scrW / scrH, 1.0, 1000.0); // same as in resize

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glInitNames();
	glPushName(0);

	isSelecting = true;
	// todo: function that draw objects but doesn't configure light (change!!!)     
	drawScenario();

	hits = glRenderMode(GL_RENDER);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	findClosestHit(hits, buffer);

	glutPostRedisplay();
}

void printInteraction()
{

}

void newTurn()
{
	for (unsigned int i = 0; i < tanksUser1.size(); i++)	tanksUser1[i]->passTurn();
}
