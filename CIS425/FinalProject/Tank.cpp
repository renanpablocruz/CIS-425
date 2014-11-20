#include "Tank.h"

Tank::Tank(int ml, int r, int a, int ms, elem t) : max_life(ml), life(ml), range(r), max_ammo(a), ammo(a), max_mov(ms),
			mov(ms), type(t), x(0), y(0), z(0), xf(0), yf(0), zf(0), direction(RIGHT), inMotion(false) {} // todo: add bullet instanciation

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

void Tank::getFinalPos(float &_x, float &_y, float &_z)
{
	_x = xf;
	_y = yf;
	_z = zf;
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

void Tank::setMoveTo(dir dr)
{
	if (!inMotion)
	{
		moveTo = dr;
		if (dr == UP) { xf = x; yf = y; zf = z - 1; }
		else if (dr == DOWN) { xf = x; yf = y; zf = z + 1; }
		else if (dr == RIGHT) { xf = x + 1; yf = y; zf = z; }
		else if (dr == LEFT) { xf = x - 1; yf = y; zf = z; }
		inMotion = true;
	}
}

void Tank::animate(int dt)
{
	if (inMotion)
	{
		if (moveTo == UP){
			if (z > zf && absValue(z - zf) > PRECISION) z -= STEP;
			else inMotion = false;
		}
		else if (moveTo == DOWN){
			if (z < zf && absValue(z - zf) > PRECISION) z += STEP;
			else inMotion = false;
		}
		else if (moveTo == RIGHT){
			if (x < xf && absValue(x - xf) > PRECISION) x += STEP;
			else inMotion = false;
		}
		else if (moveTo == LEFT){
			if (x > xf && absValue(x - xf) > PRECISION) x -= STEP;
			else inMotion = false;
		}
	}
}
