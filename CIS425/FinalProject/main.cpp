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
#include <vector>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

// Globals
// screen
static vector<Tank*> myTanks;
static float scrW;
static float scrH;
// picking and selecting
static bool isSelecting = false; // In selection mode?
static int hits; // Number of entries in hit buffer.
static unsigned int buffer[1024]; // Hit buffer.
static unsigned int closestName = 0; // Name of closest hit.

void addTank()
{
	Panzer* firstTank = new Panzer(FIRE);
	myTanks.push_back(firstTank);
}

void drawTanks()
{
	cout << "num of tanks: " << myTanks.size() << endl;
	for (int i = 0; i < myTanks.size(); i++)
	{
		if (isSelecting) glLoadName(i+2);
		if (closestName == (i + 2))
		{
			cout << "tank " << i+2 << " was selected." << endl;
		}
		int pos[3] = { i, 0, i };
		myTanks[i]->draw(pos);
	}
}

void drawTerrain()
{
	if (isSelecting) glLoadName(1);
	glColor3f(0, 0, 0);
	int size = 20;
	for (int i = -size; i < size; i++)
	{
		for (int j = -size; j < size; j++)
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
	gluLookAt(5, 0, 5, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawTerrain();
	drawTanks();

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
	glLoadIdentity();
}

void keyInput(unsigned char key, int scrX, int scrY)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
		case 't':
			addTank();
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

void specialKeyInput(int key, int x, int y)
{
	int modifier = glutGetModifiers();
	switch (key)
	{
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
	gluPickMatrix((float)x, (float)(viewport[3] - y), 2.0, 2.0, viewport);
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
	glutMouseFunc(pickFunction);
	glutSpecialFunc(specialKeyInput);
	// todo: glutTimerFunc(time, function, value); // wait time miliseconds and execute function with argument value
	glutMainLoop();

	return 0;
}