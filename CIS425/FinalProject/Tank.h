#ifndef TANK_H
#define TANK_H

#define PI 3.14159265358979324

enum elem{ FIRE, WATER, EARTH};
enum dir{UP, DOWN, LEFT, RIGHT};

class Tank
{
private:
	elem type;
	int range;
	int max_life;
	int life;
	int max_ammo;
	int ammo;
	int max_mov;
	int mov;
	int damage;
	float x;
	float y;
	float z;
public:
	Tank();
	Tank(int ml, int r, int a, int ms, int d, elem t);
	void modLife(int d);
	elem getType();
	void setPos(float x, float y, float z);
	void getPos(float &_x, float &_y, float &_z);
	void move(dir direction);
	bool canMov();
	void passTurn();
	virtual void draw() = 0;
	virtual void shoot() = 0;
};

#endif
