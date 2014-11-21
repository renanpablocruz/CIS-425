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

void Battalion::deselectTank(int ind)
{
	tanks[ind]->deselect();
}

void Battalion::draw()
{
	for (unsigned int i = 0; i < tanks.size(); i++)
	{
		tanks[i]->draw();
	}
}

int Battalion::selectedTank() // only make sense to call if anyselectedTank returned true
{
	for (unsigned int i = 0; i < tanks.size(); i++)
	{
		if (tanks[i]->isSelected()) return i;
	}
	return -1;
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

bool Battalion::hasTanks()
{
	bool ans = (tanks.size() > 0); // todo: ask Tarzan
	return ans;
}

void Battalion::moveTank(dir dr)
{
	tanks[selectedTank()]->setMoveTo(dr);
}

void Battalion::newTurn()
{
	for (unsigned int i = 0; i < tanks.size(); i++) tanks[i]->passTurn();
}

int Battalion::numTanks()
{
	return tanks.size();
}

void Battalion::selectFirstTank()
{
	if (hasTanks())	tanks[0]->select();
}

void Battalion::selectTank(int ind)
{
	tanks[ind]->select();
}

void Battalion::setTargetMode()
{
	tanks[selectedTank()]->setSelectTargetMode();
}

void Battalion::setWaitingMode()
{
	tanks[selectedTank()]->setWaitingMode();
}

void Battalion::shoot(float _x, float _y, float _z)
{
	tanks[selectedTank()]->shoot(_x, _y, _z);
}
