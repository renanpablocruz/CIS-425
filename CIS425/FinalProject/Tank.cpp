#include "Tank.h"

Tank::Tank(int ml, int r, int a, int ms, elem t) : max_life(ml), life(ml), range(r), max_ammo(a), ammo(a), max_mov(ms),
			mov(ms), type(t), x(0), y(0), z(0) {}

void Tank::modLife(int d){
	int actual = life + d;
	if (actual > max_life) life = max_life;
	else if (actual < 0) life = 0;
}

elem Tank::getType()
{
	return type;
}

void Tank::setPos(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void Tank::getPos(float &_x, float &_y, float &_z)
{
	_x = x;
	_y = y;
	_z = z;
}

void Tank::move(dir direction)
{
	float step = 0.2;
	float _x, _y, _z;
	this->getPos(_x, _y, _z);
	if (direction == UP) setPos(_x, _y, _z - step);
	else if (direction == DOWN)	setPos(_x, _y, _z + step);
	else if (direction == RIGHT) setPos(_x + step, _y, _z);
	else if (direction == LEFT) setPos(_x - step, _y, _z);
}

bool Tank::canMov()
{
	if (mov > 0)
	{
		mov -= 1;
		return true;
	}
	else return false;
}

void Tank::passTurn()
{
	mov = max_mov;
	ammo = max_ammo;
}