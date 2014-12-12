#include "Battalion.h"

Battalion::Battalion(int value)
{
	selectedTank = -1;
	switch (value)
	{
		case 0:
		{
			Panzer* tank = new Panzer(FIRE);
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
		case 1:
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
		case 2:
		{
			Panzer* tank = new Panzer(WATER);
			tank->setPos(2, 0, 5); // user3
			tanks.push_back(tank);

			/*tank = new Panzer(WATER);
			tank->setPos(3, 0, 2);
			tanks.push_back(tank);

			tank = new Panzer(FIRE);
			tank->setPos(3, 0, 4);
			tanks.push_back(tank);*/
			break;
		}
		default:
			break;
	}	
}

void Battalion::computeDamage(int damage, elem bulletType)
{
	tanks[selectedTank]->computeDamage(damage, bulletType);
}

void Battalion::draw(battalionState state)
{
	for (unsigned int i = 0; i < tanks.size(); i++)
	{
		color selectionColor = NONE;
		if (state == ATTACKING) selectionColor = BLUE;
		else if (state == DEFENDING) selectionColor = RED;
		tanks[i]->draw(i==selectedTank, selectionColor);
	}
}

Bullet* Battalion::getBullet()
{
	return tanks[selectedTank]->getBullet();
}

void Battalion::getPosOfSelectedTank(float &_x, float &_y, float &_z)
{
	getPosOfTank(selectedTank, _x, _y, _z);
}

void Battalion::getPosOfTank(unsigned int ind, float &x, float &y, float &z)
{
	if (ind < 0 || ind >= tanks.size())
		return;

	tanks[ind]->getPos(x, y, z);
}

int Battalion::getSelectedTank()
{
	return selectedTank;
}

tankState Battalion::getStateOfTank()
{
	tankState ans = tanks[selectedTank]->getState();
	return ans;
}

std::vector<const Tank*> Battalion::getAllTanks()
{
	std::vector<const Tank*> answer;
	for (unsigned int i = 0; i < tanks.size(); i++) answer.push_back(tanks[i]);
	return answer;
}

bool Battalion::hasAnySelectedTank()
{
	return selectedTank != -1;
}

bool Battalion::hasTanks()
{
	bool ans = (tanks.size() > 0);
	return ans;
}

void Battalion::moveTank(dir dr)
{
	tanks[selectedTank]->setMoveTo(dr);
}

void Battalion::passTurn()
{
	selectNoTank();
	for (unsigned int i = 0; i < tanks.size(); i++) tanks[i]->passTurn();
}

int Battalion::numTanks()
{
	return tanks.size();
}

void Battalion::selectDefaultTank()
{
	selectedTank = hasTanks() ? 0 : -1;
}

void Battalion::setTargetMode()
{
	tanks[selectedTank]->setSelectTargetMode();
}

void Battalion::selectNextTank()
{
	if (selectedTank != tanks.size() - 1) selectedTank += 1;
	else selectedTank = 0;
}

void Battalion::selectNoTank()
{
	selectedTank = -1;
}

void Battalion::setWaitingMode()
{
	tanks[selectedTank]->setWaitingMode();
}

void Battalion::shoot(float _x, float _y, float _z)
{
	tanks[selectedTank]->shoot(_x, _y, _z);
}

void Battalion::update(int dt)
{
	bool tankExcluded = true;
	while (tankExcluded)
	{
		tankExcluded = false;
		for (unsigned int i = 0; i < tanks.size(); i++)
		{
			if (tanks[i]->getLife() == 0)
			{
				tanks.erase(tanks.begin()+i);
				tankExcluded = true;
				break;
			}
		}
	}
	for (unsigned int i = 0; i < tanks.size(); i++) tanks[i]->update(dt);
}
