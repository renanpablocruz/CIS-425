#include "Battalion.h"

Battalion::Battalion(int value)
{
	switch (value)
	{
		case 1:
		{
			Panzer* tank = new Panzer(EARTH);
			tank->setPos(0, 0, 0); // user1
			tanks.push_back(tank);

			tank = new Panzer(WATER);
			tank->setPos(0, 0, 2);
			tanks.push_back(tank);

			tank = new Panzer(FIRE);
			tank->setPos(0, 0, 4);
			tanks.push_back(tank);
			break;
		}
		case 2:
		{
			Panzer* tank = new Panzer(EARTH);
			tank->setPos(3, 0, 0); // user2
			tanks.push_back(tank);

			tank = new Panzer(WATER);
			tank->setPos(3, 0, 2);
			tanks.push_back(tank);

			tank = new Panzer(FIRE);
			tank->setPos(3, 0, 4);
			tanks.push_back(tank);
			break;
		}
		default:
			break;
	}	
}

void Battalion::animate(int dt)
{
	for (unsigned int i = 0; i < tanks.size(); i++) tanks[i]->animate(dt);
}

bool Battalion::anySelectedTank()
{
	for (unsigned int i = 0; i < tanks.size(); i++)
	{
		if (tanks[i]->isSelected()) return true;
	}
	return false;
}

int Battalion::selectedTank() // only make sense to call if anyselectedTank returned true
{
	for (unsigned int i = 0; i < tanks.size(); i++)
	{
		if (tanks[i]->isSelected()) return i;
	}
	return -1;
}

void Battalion::draw()
{
	for (unsigned int i = 0; i < tanks.size(); i++)
	{
		tanks[i]->draw();
	}
}

bool Battalion::hasTanks()
{
	bool ans = (tanks.size() > 0); // todo: ask Tarzan
	return ans;
}

void Battalion::selectTank(int ind)
{
	tanks[ind]->select();
}

void Battalion::deselectTank(int ind)
{
	tanks[ind]->deselect();
}

int Battalion::numTanks()
{
	return tanks.size();
}

void Battalion::getPosOfTank(int ind, float &x, float &y, float &z)
{
	tanks[ind]->getPos(x, y, z);
}

tankState Battalion::getStateOfTank()
{
	tankState ans = tanks[selectedTank()]->getState();
	return ans;
}

void Battalion::setTargetModeOfSelectedTank()
{
	tanks[selectedTank()]->setSelectTargetMode();
}

void Battalion::shoot()
{
	tanks[selectedTank()]->shoot();
}

void Battalion::moveTank(dir dr)
{
	tanks[selectedTank()]->setMoveTo(dr);
}

void Battalion::newTurn()
{
	for (unsigned int i = 0; i < tanks.size(); i++) tanks[i]->passTurn();
}