#include "Bullet.h"

Bullet::Bullet(elem t, float _x, float _y, float _z, float _xf, float _yf, float _zf, int dmg, float r, float h, dir o) : type(t), x(_x), y(_y), z(_z),
		xf(_xf), yf(_yf), zf(_zf), damage(dmg), radius(r), height(h), orientation(o), state(FLYING) {}

void Bullet::animate()
{
	switch (orientation)
	{
		case NE:
			if (x < xf && abs(x - xf) > PRECISION)
			{
				x += STEP;
				if (z > zf && abs(z - zf) > PRECISION) z -= STEP;
			}
			break;
		case SE:
			if (x < xf && abs(x - xf) > PRECISION)
			{
				x += STEP;
				if (z < zf && abs(z - zf) > PRECISION) z += STEP;
			}
			break;
		case SO:
			if (x > xf && abs(x - xf) > PRECISION)
			{
				x -= STEP;
				if (z < zf && abs(z - zf) > PRECISION) z += STEP;
			}
			break;
		case NO:
			if (x > xf && abs(x - xf) > PRECISION)
			{
				x -= STEP;
				if (z > zf && abs(z - zf) > PRECISION) z -= STEP;
			}
			break;
		default:
			break;
	}
}
