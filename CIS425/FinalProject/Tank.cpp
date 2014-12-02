#include "Tank.h"

Tank::Tank(int ml, int r, int a, int ms, elem t) : max_life(ml), life(ml), range(r), max_ammo(a), ammo(a), max_mov(ms),
			mov(ms), type(t), x(0), y(0), z(0), xf(0), yf(0), zf(0), orientation(RIGHT), state(WAITING), bullet(NULL) {}

Tank::~Tank()
{
	if (bullet != NULL)	delete bullet;
}

bool Tank::canShoot(float x2, float y2, float z2)
{
	bool ans = ( abs(abs(x - x2) + abs(y - y2) + abs(z - z2) - range) < 3*PRECISION ) && (ammo > 0);
	return ans;
}

bool Tank::canMove()
{
	return mov > 0;
}

void Tank::computeDamage(int damage)
{
	life -= damage;
	if (life < 0) life = 0;
}

Bullet* Tank::getBullet()
{
	Bullet* ans = bullet;
	return bullet;
}

void Tank::getFinalPos(float &_x, float &_y, float &_z)
{
	_x = xf;
	_y = yf;
	_z = zf;
}

int Tank::getLife()
{
	return life;
}

void Tank::getPos(float &_x, float &_y, float &_z)
{
	_x = x;
	_y = y;
	_z = z;
}

tankState Tank::getState()
{
	tankState ans = state;
	return ans;
}

elem Tank::getType()
{
	return type;
}

void Tank::modLife(int d){
	int actual = life + d;
	if (actual > max_life) life = max_life;
	else if (actual < 0) life = 0;
}

void Tank::passTurn()
{
	mov = max_mov;
	ammo = max_ammo;
}

void Tank::setMoveTo(dir dr)
{
	if (state == WAITING && canMove())
	{
		spendAMove();
		moveTo = dr;
		if (dr == UP) { xf = x; yf = y; zf = z - 1; orientation = UP; }
		else if (dr == DOWN) { xf = x; yf = y; zf = z + 1; orientation = DOWN; }
		else if (dr == RIGHT) { xf = x + 1; yf = y; zf = z; orientation = RIGHT; }
		else if (dr == LEFT) { xf = x - 1; yf = y; zf = z; orientation = LEFT; }
		state = MOVING;
	}
}

void Tank::setPos(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void Tank::setSelectTargetMode()
{
	state = SELECTING_TARGET;
}

void Tank::setWaitingMode()
{
	state = WAITING;
}

void Tank::spendAMove()
{
	mov -= 1;
}

void Tank::spendAmmo()
{
	ammo -= 1;
}
void Tank::update(int dt)
{
	switch (state)
	{
		case MOVING:
			switch (moveTo)
			{
				case UP:
					if (z > zf && abs(z - zf) > PRECISION) z -= STEP;
					else state = WAITING;
					break;
				case DOWN:
					if (z < zf && abs(z - zf) > PRECISION) z += STEP;
					else state = WAITING;
					break;
				case LEFT:
					if (x > xf && abs(x - xf) > PRECISION) x -= STEP;
					else state = WAITING;
					break;
				case RIGHT:
					if (x < xf && abs(x - xf) > PRECISION) x += STEP;
					else state = WAITING;
					break;
				default:
					break;
			}
			break;
		case SHOOTING:
			if (bullet->getState() == FLYING) bullet->update();
			else if (bullet->getState() == DONE)
			{
				bullet->reset();
				state = WAITING;
			}
			break;
		default:
			break;
	}
}
