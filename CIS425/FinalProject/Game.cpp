#include "Game.h"

Game::Game()
{
	battalions.push_back(new Battalion(1));
	battalions.push_back(new Battalion(2));
	battalionShooting = 0;
	battalionBeingTargeted = 1;
}

void Game::animate()
{
	for (int i = 0; i < battalions.size(); i++) battalions[i]->animate(DELTA_T_VIRTUAL);
}

void Game::draw()
{
	for (int i = 0; i < battalions.size(); i++) battalions[i]->draw();
	drawTerrain();
}

void Game::drawTerrain()
{
	glColor3f(0, 0, 0);
	int size = 20;
	for (int i = -size; i < size; i++)
	{
		for (int j = -size; j < size; j++) //for (int j = -size; j < size; j++)
		{
			glColor3f(0, 0, 0);
			glBegin(GL_LINE_STRIP);
			glVertex3f(i, 0, j);
			glVertex3f(i + 1, 0, j);
			glVertex3f(i + 1, 0, j + 1);
			glVertex3f(i, 0, j + 1);
			glEnd();

			if (i % 5 == 0 && j % 5 == 0) // markers
			{
				glColor3f(0.4, 0.4, 0.6);
				glPushMatrix();
				glTranslatef(0, 0.05, 0);
				glScalef(1, 0.1, 1);
				glTranslatef(i + 0.5, 0, j + 0.5);
				glutSolidCube(1);
				glPopMatrix();
			}
		}
	}
}

void Game::getPosOfSelectedTank(int player, float &_x, float &_y, float &_z)
{
	battalions[player]->getPosOfTank(battalions[player]->getSelectedTank(), _x, _y, _z);
}

void Game::getPosOfTheCurrentTank(float &_x, float &_y, float &_z)
{
	if (getStateOfTank(battalionShooting) == WAITING) battalions[battalionShooting]->getPosOfTank(battalions[battalionShooting]->getSelectedTank(), _x, _y, _z);
	else if (getStateOfTank(battalionShooting) == SELECTING_TARGET) battalions[battalionBeingTargeted]->getPosOfTank(battalions[battalionBeingTargeted]->getSelectedTank(), _x, _y, _z);	
}

void Game::getPosOfTank(int player, int indOfTank, float &_x, float &_y, float &_z)
{
	battalions[player]->getPosOfTank(indOfTank, _x, _y, _z);
}

tankState Game::getStateOfTank(int player)
{
	return battalions[player]->getStateOfTank();
}

bool Game::hasAnySelectedTank(int player)
{
	return battalions[player]->anySelectedTank();
}

bool Game::hasTanks(int player)
{
	return battalions[player]->hasTanks();
}

void Game::moveTank(int player, dir direction)
{
	battalions[player]->moveTank(direction);
}

void Game::newTurn()
{
	for (int i = 0; i < battalions.size(); i++) battalions[i]->newTurn();
}

void Game::selectDefaultTank(int player)
{
	battalions[player]->selectDefaultTank();
}

void Game::selectNextTank(int player)
{
	if (battalions[player]->getSelectedTank() != battalions[player]->numTanks() - 1)
	{
		battalions[player]->selectNextTank();
		return;
	}
	if (player == battalionShooting) battalions[player]->selectNoTank();
	else if (player == battalionBeingTargeted)
	{
		battalions[player]->selectNoTank();

		int targetBattalion = player;
		while (targetBattalion == battalionShooting) targetBattalion = (targetBattalion + 1) % battalions.size();
		battalions[targetBattalion]->selectNextTank();
	}
}

void Game::setTargetMode(int player)
{
	battalions[player]->setTargetMode();
}

void Game::setWaitingMode(int player)
{
	battalions[player]->setWaitingMode();
}

void Game::shoot(int player, int x, int y, int z)
{
	battalions[player]->shoot(x, y, z);
}
