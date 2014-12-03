#include "Game.h"

Game::Game()
{
	battalions.push_back(new Battalion(1));
	battalions.push_back(new Battalion(2));
	battalions.push_back(new Battalion(3));
	activeBattalion = 0;
	targetBattalion = 1;
	bullet = NULL;
	
	myTextures = new Texture();
	createdBullet = false;
}

bool Game::activeBattalionHasAnySelectedTank()
{
	return hasAnySelectedTank(activeBattalion);
}

void Game::computeDamage(int damage)
{
	battalions[targetBattalion]->computeDamage(damage);
}

bool Game::currentPlayerHasAnySelectedTank()
{
	return battalions[activeBattalion]->hasAnySelectedTank();
}

void Game::draw()
{
	for (unsigned int i = 0; i < battalions.size(); i++) battalions[i]->draw();
	drawTerrain();
	drawBullet();
	if (isTheGameOver()) writeCongrats();
}

void Game::drawBullet()
{
	if (bullet != NULL) bullet->draw();
}

void Game::drawTerrain()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GROUND + 1);
	for (int i = -GRID_SIZE/2; i < GRID_SIZE/2; i++)
	{
		for (int j = -GRID_SIZE/2; j < GRID_SIZE/2; j++)
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i, 0, j);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0, j);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0, j + 1);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0, j + 1);
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);
}

void Game::getBullet()
{
	bullet = battalions[activeBattalion]->getBullet();
}

void Game::getPosOfSelectedTank(int player, float &_x, float &_y, float &_z)
{
	battalions[player]->getPosOfTank(battalions[player]->getSelectedTank(), _x, _y, _z);
}

void Game::getPosOfTank(int player, int indOfTank, float &_x, float &_y, float &_z)
{
	battalions[player]->getPosOfTank(indOfTank, _x, _y, _z);
}

void Game::getPosOfTheCurrentTank(float &_x, float &_y, float &_z)
{
	if (getStateOfTank(activeBattalion) == WAITING) battalions[activeBattalion]->getPosOfTank(battalions[activeBattalion]->getSelectedTank(), _x, _y, _z);
	else if (getStateOfTank(activeBattalion) == SELECTING_TARGET) battalions[targetBattalion]->getPosOfTank(battalions[targetBattalion]->getSelectedTank(), _x, _y, _z);	
}

tankState Game::getStateOfCurrentTank()
{
	return battalions[activeBattalion]->getStateOfTank();
}

tankState Game::getStateOfTank(int player)
{
	return battalions[player]->getStateOfTank();
}

bool Game::hasAnySelectedTank(int player)
{
	return battalions[player]->hasAnySelectedTank();
}

bool Game::hasTanks(int player)
{
	return battalions[player]->hasTanks();
}

bool Game::isTheGameOver()
{
	int count = 0;
	for (unsigned int i = 0; i < battalions.size(); i++)
	{
		if (battalions[i]->numTanks() == 0) count += 1;
	}
	return count == 1;
}

void Game::moveCurrentTank(dir direction)
{
	battalions[activeBattalion]->moveTank(direction);
}

void Game::moveTank(int player, dir direction)
{
	battalions[player]->moveTank(direction);
}

void Game::newTurn()
{
	for (unsigned int i = 0; i < battalions.size(); i++) battalions[i]->passTurn();
	activeBattalion = (activeBattalion + 1) % battalions.size();
	targetBattalion = (activeBattalion == 0) ? 1 : 0;
	std::cout << std::endl;
}

void Game::selectDefaultTank(int player)
{
	battalions[player]->selectDefaultTank();
}

void Game::selectDefaultTankForTheCurrentTargetPlayer()
{
	battalions[targetBattalion]->selectDefaultTank();
}

void Game::selectFocus()
{
	if (hasAnySelectedTank(activeBattalion)){
		if (getStateOfTank(activeBattalion) == WAITING)
			selectNextTank(activeBattalion);
		else if (getStateOfTank(activeBattalion) == SELECTING_TARGET)
		{
			if (battalions[targetBattalion]->getSelectedTank() != battalions[targetBattalion]->numTanks() - 1)
				selectNextTank(targetBattalion);
			else
			{
				battalions[targetBattalion]->selectNoTank();
				targetBattalion = (targetBattalion + 1) % battalions.size();
				if (targetBattalion == activeBattalion)
					targetBattalion = (targetBattalion + 1) % battalions.size();
				battalions[targetBattalion]->selectDefaultTank();
			}
		}
	}
	else selectDefaultTank(activeBattalion);
}

void Game::selectNextTank(int player)
{
	if (battalions[player]->getSelectedTank() != battalions[player]->numTanks() - 1)
	{
		battalions[player]->selectNextTank();
		return;
	}
	if (player == activeBattalion) battalions[player]->selectNoTank();
	else if (player == targetBattalion)
	{
		battalions[player]->selectNoTank();

		int targetBattalion = player;
		while (targetBattalion == activeBattalion) targetBattalion = (targetBattalion + 1) % battalions.size();
		battalions[targetBattalion]->selectNextTank();
	}
}

void Game::setCurrentTankToTargetMode()
{
	battalions[activeBattalion]->setTargetMode();
}

void Game::setCurrentTankToWaitingMode()
{
	battalions[activeBattalion]->setWaitingMode();
}

void Game::setTargetMode(int player)
{
	battalions[player]->setTargetMode();
}

void Game::setWaitingMode(int player)
{
	battalions[player]->setWaitingMode();
}

void Game::shoot()
{
	float x, y, z;
	getPosOfSelectedTank(targetBattalion, x, y, z);
	battalions[activeBattalion]->shoot(x, y, z);
	getBullet();
	std::cout << std::endl;
}

void Game::update()
{
	for (unsigned int i = 0; i < battalions.size(); i++) battalions[i]->update(DELTA_T_VIRTUAL);
	if (bullet != NULL)
	{
		if (bullet->getState() != READY && createdBullet == false)
			createdBullet = true;
		else if (bullet->getState() == READY && createdBullet == true)
		{
			computeDamage(bullet->getDamage());
			createdBullet = false;
			bullet = NULL;
		}
	}
}

void Game::writeCongrats()
{
	std::cout << "game is over" << std::endl;
}
