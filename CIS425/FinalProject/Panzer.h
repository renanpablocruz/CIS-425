#ifndef PANZER_H
#define PANZER_H

#include "Tank.h"
#include "glutInclude.h"

class Panzer : public Tank
{
public:
	Panzer();
	Panzer(elem t);
	void draw();
	void shoot();
};

#endif
