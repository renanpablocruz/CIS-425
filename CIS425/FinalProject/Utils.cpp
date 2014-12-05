#include <math.h>
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

void writeText(std::string input, float x, float y, float z, bool centralize)
{
	/*glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();*/
	glDisable(GL_DEPTH_TEST);
	if (centralize)
	{
		x -= glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)input.c_str());
	}
	glRasterPos3f(x, y, z);
	for (unsigned int i = 0; i < input.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, input[i]);
	}
	/*glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);*/
	glEnable(GL_DEPTH_TEST);

}
