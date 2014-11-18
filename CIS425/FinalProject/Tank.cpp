#include "Tank.h"

Tank::Tank(int ml, int r, int a, int ms, int d, elem t) : max_life(ml), life(ml), range(r), ammo(a), movSpeed(ms), damage(d), type(t) {}

void Tank::modLife(int d){
	int actual = life + d;
	if (actual > max_life) life = max_life;
	else if (actual < 0) life = 0;
}

void Tank::setType(elem t)
{
	type = t;
}
