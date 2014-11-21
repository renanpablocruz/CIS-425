#ifndef PANZERBULLET_H
#define PANZERBULLET_H

#include "Bullet.h"

class PanzerBullet : public Bullet
{
public:
	PanzerBullet();
	PanzerBullet(elem t, float _x, float _y, float _z, float _xf, float _yf, float _zf, dir o);
	~PanzerBullet();
	void draw();
};

#endif