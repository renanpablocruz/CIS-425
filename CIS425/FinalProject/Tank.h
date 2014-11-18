#ifndef TANK_H
#define TANK_H

#define PI 3.14159265358979324

enum elem{ FIRE, WATER, EARTH};

class Tank
{
private:
	elem type;
	int max_life;
	int life;
	int range;
	int ammo;
	int movSpeed;
	int damage;
public:
	Tank();
	Tank(int ml, int r, int a, int ms, int d, elem t);
	void modLife(int d);
	void setType(elem t);
	virtual void draw(double size);
	virtual void shoot();
};

#endif
