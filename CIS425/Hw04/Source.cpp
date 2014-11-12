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
#include "utils.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

// constants
//#define PI 3.14159265358979324

using namespace std;

// Globals
static float scrW;
static float scrH;
static float camX = 145;
static float camY = 14;
static float camZ = 180;
static float camR = 100;
static int phi = 0;
static int theta = 0;
static float light0_x = 180;
static float light0_y = 50;
static float light0_z = 20;
	// object measures
static int switchz0 = 165;
static int switchz1 = 170;
static int switchy0 = 12;
static int switchy1 = 15;
	// Light
static bool light0On = false; // White light on?
static float t = 0.0005; // attenuation factor
static float ambLight = 0.4;
static float cutoffAng = 10;
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
static bool gotKey = false;
static bool keyAnimationEnded = false;
static double keyX = 100;
static double keyZ = 120;
static double keyY = 2.5;
static bool movFrontDoor = false;
static int frontDoorAngle = 0;
static int backDoorAngle = 0;
static bool gotFlashlight = false;
static bool chooseSideToTurnKey = false;
static bool gotAnswer = false;
static bool clickedOnPumpkin = false;

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
			if (i < 130 || i >= 160 || j>80){
				glVertex3f(i, j, 0);
				glVertex3f(i + 1, j, 0);
				glVertex3f(i + 1, j + 1, 0);
				glVertex3f(i, j + 1, 0);
			}
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

void drawFrontDoor(){
	if (isSelecting) glLoadName(2);
	if (closestName == 2) movFrontDoor = true;
	glPushMatrix();
	if (movFrontDoor){ glTranslatef(160, 0, 200); glRotatef(-frontDoorAngle, 0, 1, 0); glTranslatef(-160, 0, -200); }
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
	glPopMatrix();
}

void drawBackDoor(){
	if (isSelecting) glLoadName(7);
	glPushMatrix();
	if (gotAnswer){ glTranslatef(160, 0, 0); glRotatef(backDoorAngle, 0, 1, 0); glTranslatef(-160, 0, -0); }
	matAmbAndDif[0] = 1.0; matAmbAndDif[1] = 1.0; matAmbAndDif[2] = 1.0; matAmbAndDif[3] = 1.0; //white
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glBegin(GL_QUADS);
	for (int i = 0; i < 200; i++){
		for (int j = 0; j < 200; j++){
			if (i >= 130 && i < 160 && j <= 80){
				glVertex3f(i, j, 0);
				glVertex3f(i + 1, j, 0);
				glVertex3f(i + 1, j + 1, 0);
				glVertex3f(i, j + 1, 0);
			}
		}
	}
	glEnd();
	glPopMatrix();
}

void drawKey(){
	if (isSelecting) glLoadName(4);
	if (!gotFlashlight) glColorMask(false, false, false, false);
	else { matAmbAndDif[0] = 1.0; matAmbAndDif[1] = 1.0; matAmbAndDif[2] = 0.0; matAmbAndDif[3] = 1.0; } //yellow
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glPushMatrix();

	glTranslatef(keyX, keyY, keyZ);
	glRotatef(180, 0, 1, 0);
	glutSolidSphere(1, 8, 8);
	glutSolidCone(1, 3, 8, 8);
	if (!gotFlashlight) glColorMask(true, true, true, true);
	glPopMatrix();
}

void drawTable(){
	matAmbAndDif[0] = 0.4; matAmbAndDif[1] = 0.4; matAmbAndDif[2] = 0.5; matAmbAndDif[3] = 1.0; // grey
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	for (int i = 70; i < 120; i++){
		for (int j = 90; j < 110; j++){
			glVertex3f(i, 10, j);
			glVertex3f(i+1, 10, j);
			glVertex3f(i+1, 10, j + 1);
			glVertex3f(i, 10, j+1);
		}
	}
	glEnd();
}

void drawFlashlight(){
	if (isSelecting) glLoadName(6);
	if (closestName == 6) gotFlashlight = true;
	if (!gotFlashlight){
		matAmbAndDif[0] = 1.0; matAmbAndDif[1] = 0.0; matAmbAndDif[2] = 0.0; matAmbAndDif[3] = 1.0; // red
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
		glColor3f(1.0, .0, .0);
		glPushMatrix();//tube
		GLUquadric* qobj = gluNewQuadric();
		gluQuadricNormals(qobj, GLU_SMOOTH);
		glTranslatef(110,10+1, 100);
		gluCylinder(qobj, 1.0, 1.0, 6, 8, 8);
		gluDeleteQuadric(qobj);
		glPopMatrix();
		glPushMatrix();//"head"
		glTranslatef(110, 10 + 1, 100-2);
		glutSolidCone(2, 4, 8, 8);
		glPopMatrix();
	}
}

void drawPumpkin(){
	if (isSelecting) glLoadName(3);
	if (closestName == 3) clickedOnPumpkin = true;
	if (clickedOnPumpkin){
		matAmbAndDif[0] = 1.0; matAmbAndDif[1] = 0.4; matAmbAndDif[2] = 0.0; matAmbAndDif[3] = 1.0; // orange
		float matEmission[] = {1.0, 0.4, 0.0, 1.0 };
		glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
	}
	else{
		matAmbAndDif[0] = 0.6; matAmbAndDif[1] = 0.2; matAmbAndDif[2] = 0.0; matAmbAndDif[3] = 1.0; // brown
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glPushMatrix();
	glTranslatef(80, 14, 100);
	glutSolidSphere(4, 8, 8);
	glPopMatrix();
	float matEmission[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
}

void drawBulb(){
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(light0_x, light0_y, light0_z);
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
	if (gotKey && !chooseSideToTurnKey)
		gluLookAt(camX, camY, camZ, keyX, keyY, keyZ, 0, 1, 0);
	else
		gluLookAt(camX, camY, camZ, camX + camR*cos(degToRad(phi))*sin(degToRad(theta)), camY + camR*sin(degToRad(phi)), camZ - camR*cos(degToRad(phi))*cos(degToRad(theta)), 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Turn lights on again to draw the other objects
	glEnable(GL_LIGHTING);
	drawWalls();
	drawFrontDoor();
	drawBackDoor();
	drawTable();
	drawFlashlight();
	drawPumpkin();
	drawKey();
	drawSwitch();
	drawFlashlight();

	// Turn lights off to draw lamp
	glDisable(GL_LIGHTING);
	if (light0On) drawBulb();
	drawWindow();

	glEnable(GL_LIGHTING);

	if (isSelecting) glPopName(); // Clear name stack.
}

void drawKeyOptions(){

}

void drawScene()
{
	//Lighting

		// Light0 is the light bulb
	float lightAmb0[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec0[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightPos0[] = { light0_x, light0_y, light0_z, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, t);

	// light1 is the flashlight
	float lightAmb1[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightDifAndSpec1[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightPos1[] = { camX, camY, camZ, 1.0 };
	float lightDir1[3];
	if (gotKey){
		lightDir1[0] = keyX - camX;
		lightDir1[1] = keyY - camY;
		lightDir1[2] = keyZ - camZ;
	}
	else{
		lightDir1[0] = cos(degToRad(phi))*sin(degToRad(theta)); 
		lightDir1[1] = sin(degToRad(phi));
		lightDir1[2] = -cos(degToRad(phi))*cos(degToRad(theta));
	}
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cutoffAng);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, t);

	// global ambient light
	float globAmb[] = { ambLight, ambLight, ambLight, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

		// Turn lights off/on.
	if (light0On) glEnable(GL_LIGHT0); else glDisable(GL_LIGHT0);
	if (gotFlashlight) glEnable(GL_LIGHT1); else glDisable(GL_LIGHT1);


	// Draws
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

	// Draw scenario in rendering mode.
	isSelecting = false;
	drawScenario();
	if (keyAnimationEnded){
		if(!chooseSideToTurnKey) drawKeyOptions();
		else if (!gotAnswer); //spin around
		else; // open door and finish it
	}

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

bool findKey(){
	float sightDir[] = { cos(degToRad(phi))*sin(degToRad(theta)), sin(degToRad(phi)), -cos(degToRad(phi))*cos(degToRad(theta))};
	float keyDir[] = { keyX - camX, keyY - camY, keyZ - camZ };
	return cosDiffAng(sightDir, keyDir, 3) > cos(degToRad(cutoffAng));
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
			light0_x -= 5;
			glutPostRedisplay();
			break;
		case 'g':
			light0_x += 5;
			glutPostRedisplay();
			break;
		case 'y':
			light0_y += 5;
			glutPostRedisplay();
			break;
		case 'h':
			light0_y -= 5;
			glutPostRedisplay();
			break;
		case 'u':
			light0_z -= 5;
			glutPostRedisplay();
			break;
		case 'j':
			light0_z += 5;
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
			gotKey = !gotKey;
			glutPostRedisplay();
			break;
		case 'n':
			movFrontDoor = !movFrontDoor;
			glutPostRedisplay();
			break;
		case 'b':
			if(ambLight > 0) ambLight -= 0.05;
			glutPostRedisplay();
			break;
		case 'B':
			if (ambLight < 1) ambLight += 0.05;
			glutPostRedisplay();
			break;
		case 'v':
			gotFlashlight = !gotFlashlight;
			glutPostRedisplay();
			break;
		case 'x':
			gotAnswer = !gotAnswer;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

void animate(int value)
{
	if (gotKey){
		if (!keyAnimationEnded){
			if (keyY < 20){
				keyY += 1;
				camY += 1;
			}
			else if (keyZ > 5){
				keyZ -= 5;
				camZ -= 5;
			}
			else keyAnimationEnded = true;
		}
	}
	else{
		if(gotFlashlight) gotKey = findKey();
	}
	if (movFrontDoor){
		if (frontDoorAngle < 120) frontDoorAngle += 5;
		else movFrontDoor = false;
	}
	if (gotAnswer){
		if (backDoorAngle < 120) backDoorAngle += 5;
		//else gotAnswer = false;
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
	cout << "Press t to decrease light0_x" << endl;
	cout << "Press g to increase light0_x" << endl;
	cout << "Press y to increase light0_y" << endl;
	cout << "Press h to decrease light0_y" << endl;
	cout << "Press u to decrease light0_z" << endl;
	cout << "Press j to increase light0_z" << endl;
	cout << "Press i to increase phi" << endl;
	cout << "Press k to decrease phi" << endl;
	cout << "Press o to decrease theta" << endl;
	cout << "Press l to increase theta" << endl;
	cout << "Press Z to increase attenuation" << endl;
	cout << "Press z to decrease attenuation" << endl;
	cout << "Press B to increase ambLight" << endl;
	cout << "Press b to decrease ambLight" << endl;

	cout << "Press m to toggle gotKey" << endl;
	cout << "Press n to toggle doorAngle" << endl;
	cout << "Press v to toggle gotFlashlightf" << endl;
	cout << "Press x to toggle gotAnswer" << endl;
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
