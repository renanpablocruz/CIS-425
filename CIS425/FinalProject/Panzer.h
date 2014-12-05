#ifndef PANZER_H
#define PANZER_H

#include <iostream>
#include "Tank.h"
#include "glutInclude.h"
#include "Utils.h"
#include "PanzerBullet.h"

class Panzer : public Tank
{
public:
	Panzer();
	Panzer(elem t);
	void draw(bool selected, color selection);
	void drawBody();
	Bullet* getBullet();
	void shoot(float _x, float _y, float _z);
};

#endif
