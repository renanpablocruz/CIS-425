#include "Bullet.h"

Bullet::Bullet(elem t, float _x, float _y, float _z, int dmg, float r, float h, dir o) : type(t), x(_x), y(_y), z(_z),
damage(dmg), radius(r), height(h), orientation(o) {}
