#include "Tank.h"

Tank::Tank(int ml, int r, int a, int ms, elem t) : max_life(ml), life(ml), range(r), max_ammo(a), ammo(a), max_mov(ms),
			mov(ms), type(t), x(0), y(0), z(0), xf(0), yf(0), zf(0), orientation(RIGHT), state(WAITING), selection(false) {} // todo: add bullet instanciation

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
	if (state == WAITING && mov > 0)
	{
		mov -= 1;
		moveTo = dr;
		if (dr == UP) { xf = x; yf = y; zf = z - 1; }
		else if (dr == DOWN) { xf = x; yf = y; zf = z + 1; }
		else if (dr == RIGHT) { xf = x + 1; yf = y; zf = z; }
		else if (dr == LEFT) { xf = x - 1; yf = y; zf = z; }
		state = MOVING;
		// todo: change orientation
	}
}

void Tank::animate(int dt)
{
	switch(state)
	{
		case MOVING:
			switch (moveTo)
			{
				case UP:
					if (z > zf && absValue(z - zf) > PRECISION) z -= STEP;
					else state = WAITING;
					break;
				case DOWN:
					if (z < zf && absValue(z - zf) > PRECISION) z += STEP;
					else state = WAITING;
					break;
				case LEFT:
					if (x > xf && absValue(x - xf) > PRECISION) x -= STEP;
					else state = WAITING;
					break;
				case RIGHT:
					if (x < xf && absValue(x - xf) > PRECISION) x += STEP;
					else state = WAITING;
					break;
				default:
					break;
			}
			break;
		case SHOOTING:

			break;
		default:
			break;
	}
}

tankState Tank::getState()
{
	return state;
}

void Tank::setSelectTargetMode()
{
	state = SELECTING_TARGET;
}

void Tank::select()
{
	selection = true;
}

void Tank::deselect()
{
	selection = false;
}

bool Tank::isSelected()
{
	bool ans = selection;
	return ans;
}