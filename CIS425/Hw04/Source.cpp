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
static float camX = 145;
static float camY = 10;
static float camZ = 180;
static float camR = 100;
static int phi = 0;
static int theta = 0;
static float ambX = 180;
static float ambY = 50;
static float ambZ = 20;
	// object measures
static int switchz0 = 165;
static int switchz1 = 170;
static int switchy0 = 12;
static int switchy1 = 15;
	// Light
static bool light0On = false; // White light on?
static float t = 0.0005; // attenuation factor
	// Material property vectors.
static float matAmbAndDif[] = { 0.0, 0.0, 1.0, 1.0 };
static float matSpec[] = { 1.0, 1.0, 1, 0, 1.0 };
static float matShine[] = { 0.0 };
	// picking and selecting
static bool isSelecting = false; // In selection mode?
static int hits; // Number of entries in hit buffer.
static unsigned int buffer[1024]; // Hit buffer.
static unsigned int closestName = 0; // Name of closest hit.
	// animations
static int frameRate = 100; //control speed of animations
static bool foundKey = false;
static bool keyAnimationStarted = false;
static int smallSphereZ = 120;
static int smallSphereY = 2.5;
static bool clickedFrontDoor = false;
static int doorAngle = 0;

float degToRad(int angInDeg){
	return PI * angInDeg / 180;
}

void incAng(int& angInDeg){
	angInDeg = (angInDeg + 5) % 360;
}

void decAng(int& angInDeg){
	angInDeg = (angInDeg - 5) % 360;
}

void drawWalls(){
	if (isSelecting) glLoadName(1);
	// south wall
		// draw wall
	glNormal3f(0, 0, -1);
	if (closestName == 1){
		matAmbAndDif[0] = 1.0; matAmbAndDif[1] = 0.0; matAmbAndDif[2] = 0.0; matAmbAndDif[3] = 1.0; //red
	}
	else{
		matAmbAndDif[0] = 1.0; matAmbAndDif[1] = 1.0; matAmbAndDif[2] = 0.0; matAmbAndDif[3] = 1.0; //yellow
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glBegin(GL_QUADS);
	for (int i = 0; i < 200; i++){
		for (int j = 0; j < 200; j++){
			if (i < 130 || i >= 160 || j>80){
				glVertex3f(i, j, 200);
				glVertex3f(i + 1, j, 200);
				glVertex3f(i + 1, j + 1, 200);
				glVertex3f(i, j + 1, 200);
			}
		}
	}
	glEnd();
	// north wall
	glNormal3f(0, 0, 1);
	matAmbAndDif[0] = 0.0; matAmbAndDif[1] = 0.0; matAmbAndDif[2] = 1.0; matAmbAndDif[3] = 1.0; //blue
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	matShine[0] = 50.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
	glBegin(GL_QUADS);
	for (int i = 0; i < 200; i++){
		for (int j = 0; j < 200; j++){
			glVertex3f(i, j, 0);
			glVertex3f(i+1, j, 0);
			glVertex3f(i+1, j+1, 0);
			glVertex3f(i, j+1, 0);
		}
	}
	glEnd();
	matShine[0] = 0.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
	// east wall
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	matAmbAndDif[0] = 0.0; matAmbAndDif[1] = 1.0; matAmbAndDif[2] = 0.0; matAmbAndDif[3] = 1.0; //green
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	for (int i = 0; i < 200; i++){
		for (int j = 0; j < 200; j++){
			glVertex3f(200, j, i);
			glVertex3f(200, j, i+1);
			glVertex3f(200, j+1, i+1);
			glVertex3f(200, j+1, i);
		}
	}
	glEnd();
	// west wall
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	matAmbAndDif[0] = 0.0; matAmbAndDif[1] = 1.0; matAmbAndDif[2] = 0.0; matAmbAndDif[3] = 1.0; //green
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	for (int i = 0; i < 200; i++){
		for (int j = 0; j < 200; j++){
			glVertex3f(0, j, i);
			glVertex3f(0, j, i + 1);
			glVertex3f(0, j + 1, i + 1);
			glVertex3f(0, j + 1, i);
		}
	}
	glEnd();
}

void drawDoor(){
	if (isSelecting) glLoadName(2);
	if (closestName == 2) clickedFrontDoor = true;
	if (clickedFrontDoor){ glTranslatef(160, 0, 200); glRotatef(-doorAngle, 0, 1, 0); glTranslatef(-160, 0, -200); }
	matAmbAndDif[0] = 1.0; matAmbAndDif[1] = 1.0; matAmbAndDif[2] = 1.0; matAmbAndDif[3] = 1.0; //yellow
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glBegin(GL_QUADS);
	for (int i = 0; i < 200; i++){
		for (int j = 0; j < 200; j++){
			if (i >= 130 && i < 160 && j <= 80){
				glVertex3f(i, j, 200);
				glVertex3f(i + 1, j, 200);
				glVertex3f(i + 1, j + 1, 200);
				glVertex3f(i, j + 1, 200);
			}
		}
	}
	glEnd();
	if (clickedFrontDoor){ glTranslatef(160, 0, 200); glRotatef(doorAngle, 0, 1, 0); glTranslatef(-160, 0, -200); }
}

void drawSpheres(){
	if (isSelecting) glLoadName(3);
	if (closestName == 3){
		matAmbAndDif[0] = 1.0; matAmbAndDif[1] = 0.0; matAmbAndDif[2] = 0.0; matAmbAndDif[3] = 1.0; //red
	}
	else{
		matAmbAndDif[0] = 1.0; matAmbAndDif[1] = 1.0; matAmbAndDif[2] = 1.0; matAmbAndDif[3] = 1.0; //white
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glPushMatrix();
	glTranslatef(100, 4, 100);
	glutSolidSphere(4, 8, 8);
	glPopMatrix();

	if (isSelecting) glLoadName(4);
	if (!foundKey) glColorMask(false, false, false, false);
	else { matAmbAndDif[0] = 1.0; matAmbAndDif[1] = 1.0; matAmbAndDif[2] = 0.0; matAmbAndDif[3] = 1.0; } //yellow
		//matAmbAndDif[0] = 1.0; matAmbAndDif[1] = 1.0; matAmbAndDif[2] = 0.0; matAmbAndDif[3] = 1.0; //yellow
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glPushMatrix();
	glTranslatef(100, smallSphereY, smallSphereZ);
	glutSolidSphere(2.5, 8, 8);
	if (!foundKey) glColorMask(true, true, true, true);
	glPopMatrix();
}

void drawBulb(){
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(ambX, ambY, ambZ);
	glutWireSphere(4, 8, 8);
	glPopMatrix();
}

void drawSwitch(){
	if (isSelecting) glLoadName(5);
	if (closestName == 5) { light0On = !light0On; closestName = 0; }
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	matAmbAndDif[0] = 0.0; matAmbAndDif[1] = 0.0; matAmbAndDif[2] = 1.0; matAmbAndDif[3] = 1.0; //cyan
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	for (int i = switchz0; i < switchz1; i++){
		for (int j = switchy0; j < switchy1; j++){
			glVertex3f(1, j, i);
			glVertex3f(1, j, i + 1);
			glVertex3f(1, j + 1, i + 1);
			glVertex3f(1, j + 1, i);
		}
	}
	glEnd();
}

void drawWindow(){
	glNormal3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glColor3f(0, 0, 0); //backgroung
	glRectf(120, 12, 80, 42);
	glColor3f(1.0, 1.0, 1.0); //bright side of moon
	glBegin(GL_POLYGON);
	for (int i = 0, R= 5 ; i < 20; i++){
		glVertex3f(110 + R*cos(2 * PI*i / 20), 30 + R*sin(2 * PI*i / 20), -1);
	}
	glEnd();
	glColor3f(0, 0, 0); //dark side of moon
	glBegin(GL_POLYGON);
	for (int i = 0, R = 5; i < 20; i++){
		glVertex3f(109 + R*cos(2 * PI*i / 20), 29 + R*sin(2 * PI*i / 20), -2);
	}
	glEnd();
	glColor3f(1.0, 1.0, 1.0); // stars
	glTranslatef(0, 0, -3);
	glRectf(90, 30, 89, 31);
	glRectf(92, 24, 91, 25);
	glRectf(95, 27, 94, 28);
	glRectf(100, 29, 99, 30);
	glRectf(105, 28, 104, 29);
	glPopMatrix();
	glColor3f(1.0, 0.0, 1.0);
}

void drawScenario(){
	gluLookAt(camX, camY, camZ, camX + camR*cos(degToRad(phi))*sin(degToRad(theta)), camY + camR*sin(degToRad(phi)), camZ - camR*cos(degToRad(phi))*cos(degToRad(theta)), 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	// Turn lights on again to draw the other objects
	glEnable(GL_LIGHTING);
	drawWalls();
	drawDoor();
	drawSpheres();
	drawSwitch();

	// Turn lights off to draw lamp
	glDisable(GL_LIGHTING);
	if (light0On) drawBulb();
	drawWindow();

	glEnable(GL_LIGHTING);

	if (isSelecting) glPopName(); // Clear name stack.
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
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	// Light quadratic attenuation factor.
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, t);

		// Turn lights off/on.
	if (light0On) glEnable(GL_LIGHT0); else glDisable(GL_LIGHT0);


	// Draws
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

	
	// Draw ball and torus in rendering mode.
	isSelecting = false;
	drawScenario();

	glutSwapBuffers();
}

// Process hit buffer to find record with smallest min-z value.
void findClosestHit(int hits, unsigned int buffer[])
{
	unsigned int *ptr, minZ;

	minZ = 0xffffffff; // 2^32 - 1
	ptr = buffer;
	closestName = 0;
	for (int i = 0; i < hits; i++)
	{
		ptr++;
		if (*ptr < minZ)
		{
			minZ = *ptr;
			ptr += 2;
			closestName = *ptr;
			ptr++;
		}
		else ptr += 3;
	}
	//if (closestName != 0) highlightFrames = 10;
	cout << "object " << closestName << " was clicked" << endl;
}

// The mouse callback routine.
void pickFunction(int button, int state, int x, int y)
{
	int viewport[4]; // Viewport data.

	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return; // Don't react unless left button is pressed.

	glGetIntegerv(GL_VIEWPORT, viewport); // Get viewport data.

	glSelectBuffer(1024, buffer); // Specify buffer to write hit records in selection mode
	(void)glRenderMode(GL_SELECT); // Enter selection mode.

	// Save the viewing volume defined in the resize routine.
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	// Define a viewing volume corresponding to selecting in 3 x 3 region around the cursor.
	glLoadIdentity();
	gluPickMatrix((float)x, (float)(viewport[3] - y), 3.0, 3.0, viewport);
	gluPerspective(45.0f, (double)scrW / scrH, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW); // Return to modelview mode before drawing.
	glLoadIdentity();

	glInitNames(); // Initializes the name stack to empty.
	glPushName(0); // Puts name 0 on top of stack.

	// Determine hits by calling drawBallAndTorus() so that names are assigned.
	isSelecting = true;
	drawScenario();

	hits = glRenderMode(GL_RENDER); // Return to rendering mode, returning number of hits.

			// debug
	cout << hits << " hits." << endl;

	// Restore viewing volume of the resize routine and return to modelview mode.
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	// Determine closest of the hit objects (if any).
	findClosestHit(hits, buffer);

	glutPostRedisplay();
}

void resize(int w, int h)
{
	scrW = w;
	scrH = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (double)w / h, 1.0, 1000.0);
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

	//todo ambient light setup

	// Material properties of sphere.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

	// Cull back faces.
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

void keyInput(unsigned char key, int scrX, int scrY)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
		case 'q':
			camX -= 5;
			glutPostRedisplay();
			break;
		case 'a':
			camX += 5;
			glutPostRedisplay();
			break;
		case 'w':
			camY += 5;
			glutPostRedisplay();
			break;
		case 's':
			camY -= 5;
			glutPostRedisplay();
			break;
		case 'e':
			camZ -= 5;
			glutPostRedisplay();
			break;
		case 'd':
			camZ += 5;
			glutPostRedisplay();
			break;
		case 'r':
			light0On = !light0On;
			glutPostRedisplay();
			break;
		case 't':
			ambX -= 5;
			glutPostRedisplay();
			break;
		case 'g':
			ambX += 5;
			glutPostRedisplay();
			break;
		case 'y':
			ambY += 5;
			glutPostRedisplay();
			break;
		case 'h':
			ambY -= 5;
			glutPostRedisplay();
			break;
		case 'u':
			ambZ -= 5;
			glutPostRedisplay();
			break;
		case 'j':
			ambZ += 5;
			glutPostRedisplay();
			break;
		case 'i':
			incAng(phi);
			glutPostRedisplay();
			break;
		case 'k':
			decAng(phi);
			glutPostRedisplay();
			break;
		case 'o':
			decAng(theta);
			glutPostRedisplay();
			break;
		case 'l':
			incAng(theta);
			glutPostRedisplay();
			break;
		case 'z':
			if(t > 0.0) t -= 0.0005;
			cout << "t = " << t << endl;
			glutPostRedisplay();
			break;
		case 'Z':
			t += 0.0005;
			cout << "t = " << t << endl;
			glutPostRedisplay();
			break;
		case 'm':
			foundKey = !foundKey;
			glutPostRedisplay();
			break;
		case 'n':
			clickedFrontDoor = !clickedFrontDoor;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

void animate(int value)
{
	if (foundKey){
		if (!keyAnimationStarted){
			if (smallSphereY < 100) smallSphereY += 1;
			else if (smallSphereZ > 5) smallSphereZ -= 5;
		}
		else{

		}
	}
	if (clickedFrontDoor){
		if (doorAngle < 120) doorAngle += 5;
		//else clickedFrontDoor = false;
	}
	glutTimerFunc(frameRate, animate, 1);
	glutPostRedisplay();
}

void printInteraction()
{
	cout << "Interactions:" << endl;
	cout << "Press q to decrease camX" << endl;
	cout << "Press a to increase camX" << endl;
	cout << "Press w to increase camY" << endl;
	cout << "Press s to increase camY" << endl;
	cout << "Press e to decrease camZ" << endl;
	cout << "Press d to decrease camZ" << endl;
	cout << "Press r to turn on/off the ambient light" << endl;
	cout << "Press t to decrease ambX" << endl;
	cout << "Press g to increase ambX" << endl;
	cout << "Press y to increase ambY" << endl;
	cout << "Press h to decrease ambY" << endl;
	cout << "Press u to decrease ambZ" << endl;
	cout << "Press j to increase ambZ" << endl;
	cout << "Press i to increase phi" << endl;
	cout << "Press k to decrease phi" << endl;
	cout << "Press o to decrease theta" << endl;
	cout << "Press l to increase theta" << endl;
	cout << "Press Z to increase attenuation" << endl;
	cout << "Press z to decrease attenuation" << endl;

	cout << "Press m to toggle foundKey" << endl;
	cout << "Press n to toggle doorAngle" << endl;
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
	glutMouseFunc(pickFunction);
	glutTimerFunc(5, animate, 1); // wait 5 miliseconds and execute this fuction for the first time
	glutMainLoop();

	return 0;
}