#include "Utils.h"

dir getDirForTank(float x1, float y1, float x2, float y2)
{
	dir ans;
	float ang = atan2(y2 - y1, x2 - x1); // [-PI, PI]

	if (ang < 3 * PI / 4 && ang > PI / 4) ans = UP;
	else if (ang < PI / 4 && ang > -PI / 4) ans = RIGHT;
	else if (ang < -PI / 4 && ang > -3 * PI / 4) ans = DOWN;
	else ans = LEFT;

	return ans;
}


dir getDirForBullet(float x1, float y1, float x2, float y2)
{
	dir ans;
	float ang = atan2(y2 - y1, x2 - x1); // [-PI, PI]
	if (ang <= PI && ang > PI / 2) ans = SO;
	else if (ang <= PI / 2 && ang > 0) ans = SE;
	else if (ang <= 0 && ang > - PI / 2) ans = NE;
	else ans = NO;

	return ans;
}

float degToRad(double angInDeg){
	return PI * angInDeg / 180;
}

void incAng(double& angInDeg){
	angInDeg = (int)(angInDeg + 5) % 360;
}

void decAng(double& angInDeg){
	angInDeg = (int)(angInDeg - 5) % 360;
}

float damageModifier(elem bulletType, elem tankType)
{
	switch (bulletType)
	{
		case FIRE:
			switch (tankType)
			{
				case EARTH:
					return 2;
				case WATER:
					return 0.5;
				default:
					return 1;
			}
		case WATER:
			switch (tankType)
			{
				case FIRE:
					return 2;
				case EARTH:
					return 0.5;
				case WATER:
					return 0.5;
				default:
					return 1;
			}
			break;
		case EARTH:
			switch (tankType)
			{
				case FIRE:
					return 2;
				case WATER:
					return 0.5;
				default:
					return 1;
			}
		default:
			return 1;
	}
}

void drawBackground(color selColor, float alpha)
{
	glDisable(GL_TEXTURE_2D);
	float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT);
	if (selColor == WHITE)
		glColor4f(1, 1, 1, alpha);
	else if (selColor == BLACK)
		glColor4f(0, 0, 0, alpha);
	else if (selColor == GRAY)
		glColor4f(0.5, 0.5, 0.5, alpha);
	else
		glColor4f(0, 0, 0, alpha);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, w, 0, h, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(w, 0, 0);
	glVertex3f(w, h, 0);
	glVertex3f(0, h, 0);
	glEnd();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void drawButton(int xc, int yc, int w, int h, std::string input, void *font, color selColor)
{
	drawWindow(xc, yc, w, h, selColor);
	writeText2d(input, xc, yc, true, font);
}

void drawImage(int xc, int yc, int w, int h, typesOfTextures texture)
{
	glColor4f(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glTranslatef(xc, yc, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture + 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0,1); glVertex3f(-w / 2, h / 2, 0);
	glTexCoord2d(1,1); glVertex3f(w / 2, h / 2, 0);
	glTexCoord2d(1,0); glVertex3f(w / 2, -h / 2, 0);
	glTexCoord2d(0,0); glVertex3f(-w / 2, -h / 2, 0);
	glEnd();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE);
}

void drawWindow(int xc, int yc, int w, int h, color selColor)
{
	if (selColor == WHITE) glColor4f(1, 1, 1, 0.6);
	else glColor4f(0,0,0,0.6);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glTranslatef(xc, yc, 0);
	glBegin(GL_QUADS);
	glVertex3f(-w/2, h/2, 0);
	glVertex3f(w/2, h/2, 0);
	glVertex3f(w/2, -h/2, 0);
	glVertex3f(-w/2, -h/2, 0);
	glEnd();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glColor4f(1,1,1,1);
}

void writeText2d(std::string input, float x, float y, bool centralize, void *font, color selColor)
{
	glDisable(GL_TEXTURE_2D);
	if (selColor == BLACK) glColor4f(0, 0, 0, 1);
	else glColor4f(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	if (centralize) x -= glutBitmapLength(font, (unsigned char*)input.c_str())/2;
	glRasterPos3f(x, y, 0);
	for (unsigned int i = 0; i < input.size(); i++) glutBitmapCharacter(font, input[i]);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void writeText3d(std::string input, float x, float y, float z, bool centralize, void *font)
{
	glColor4f(1,1,1,1);
	/*glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();*/
	glDisable(GL_DEPTH_TEST);
	if (centralize) x -= glutBitmapLength(font, (unsigned char*)input.c_str());
	glRasterPos3f(x, y, z);
	for (unsigned int i = 0; i < input.size(); i++) glutBitmapCharacter(font, input[i]);
	/*glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);*/
	glEnable(GL_DEPTH_TEST);
}

bool isInside(float x, float y, float xc, float yc, float w, float h)
{
	return (x > xc - w / 2 && x < xc + w / 2 && y > yc - h / 2 && y < yc + h / 2);
}
