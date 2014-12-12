#include "Panzer.h"

Panzer::Panzer(elem t) : Tank(20, 2, 4, 6, t){}

void Panzer::draw(bool selected, color selectionColor)
{
	if (selected)
	{
		if (selectionColor == RED) glColor4f(1.f, 0.f, 0.f, 0.45f);
		else if (selectionColor == BLUE) glColor4f(0.f, 0.f, 1.f, 0.45f);
		glPushMatrix();
		glTranslatef(x + 0.5, y + 0.5, z + 0.5);
		glScalef(1.3, 1.3, 1.3f);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glutSolidCube(1.f);
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glPopMatrix();
	}

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	if (getType() == FIRE) glBindTexture(GL_TEXTURE_2D, RED_CAMOUFLAGE + 1);
	else if (getType() == EARTH) glBindTexture(GL_TEXTURE_2D, BROWN_CAMOUFLAGE + 1);
	else if (getType() == WATER) glBindTexture(GL_TEXTURE_2D, BLUE_CAMOUFLAGE + 1);
	drawBody();
	glDisable(GL_TEXTURE_2D);
}

void Panzer::drawBody()
{
	glPushMatrix();
	glTranslatef(x + 0.5, y + 0.5, z + 0.5);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.5, -0.5); // top
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, -0.5, -0.5); // down
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.5, 0.5); // front
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.5, -0.5); // back
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5, 0.5, 0.5); // right
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.5, 0.5); // left
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5, -0.5, 0.5);
	glEnd();
	glPopMatrix();
}

void Panzer::shoot(float xf, float yf, float zf)
{
	if (canShoot(xf, yf, zf))
	{
		spendAmmo();
		orientation = getDirForTank(x, z, xf, zf);
		bullet = new PanzerBullet(type, x, y, z, xf, yf, zf, getDirForBullet(x, y, xf, yf));
		state = SHOOTING;
	}
}
