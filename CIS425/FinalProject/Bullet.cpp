#include "Bullet.h"

Bullet::Bullet(elem t, float _x, float _y, float _z, float _xf, float _yf, float _zf, int dmg, float r, float h, dir o) : type(t), x(_x), y(_y), z(_z),
		xf(_xf), yf(_yf), zf(_zf), damage(dmg), radius(r), height(h), orientation(o), state(FLYING) {}

Bullet::~Bullet() {}

int Bullet::getDamage()
{
	return damage;
}

elem Bullet::getType()
{
	return type;
}

bulletState Bullet::getState()
{
	bulletState ans = state;
	return ans;
}

void Bullet::reset()
{
	state = READY;
}

void Bullet::update()
{
	bool hadMove = false;
	switch (orientation)
	{
		case NE:
			if (x < xf && abs(x - xf) > PRECISION){ x += STEP; hadMove = true; }
			if (z > zf && abs(z - zf) > PRECISION){ z -= STEP; hadMove = true; }
			break;
		case SE:
			if (x < xf && abs(x - xf) > PRECISION){ x += STEP; hadMove = true; }
			if (z < zf && abs(z - zf) > PRECISION){ z += STEP; hadMove = true; }
			break;
		case SO:
			if (x > xf && abs(x - xf) > PRECISION){ x -= STEP; hadMove = true; }
			if (z < zf && abs(z - zf) > PRECISION){ z += STEP; hadMove = true; }
			break;
		case NO:
			if (x > xf && abs(x - xf) > PRECISION){ x -= STEP; hadMove = true; }
			if (z > zf && abs(z - zf) > PRECISION){ z -= STEP; hadMove = true; }
			break;
		default:
			break;
	}
	if (!hadMove) state = DONE;
}
