#include "Game.h"

Game::Game() : tanksUser1(new Battalion(1)), tanksUser2(new Battalion(2)){}

void Game::animate()
{
	tanksUser1->animate(DELTA_T_VIRTUAL);
	tanksUser2->animate(DELTA_T_VIRTUAL);
}

void Game::draw()
{
	tanksUser1->draw();
	tanksUser2->draw();
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
	switch (player)
	{
		case 1:
			tanksUser1->getPosOfTank(tanksUser1->getSelectedTank(), _x, _y, _z);
			break;
		case 2:
			tanksUser2->getPosOfTank(tanksUser2->getSelectedTank(), _x, _y, _z);
			break;
		default:
			break;
	}
}

void Game::getPosOfTheCurrentTank(float &_x, float &_y, float &_z)
{
	if (getStateOfTank(1) == WAITING) tanksUser1->getPosOfTank(tanksUser1->getSelectedTank(), _x, _y, _z);
	else if (tanksUser1->getStateOfTank() == SELECTING_TARGET) tanksUser2->getPosOfTank(tanksUser2->getSelectedTank(), _x, _y, _z);
	
}

void Game::getPosOfTank(int player, int indOfTank, float &_x, float &_y, float &_z)
{
	switch (player)
	{
		case 1:
			tanksUser1->getPosOfTank(indOfTank, _x, _y, _z);
			break;
		case 2:
			tanksUser2->getPosOfTank(indOfTank, _x, _y, _z);
			break;
		default:
			break;
	}
	
}

tankState Game::getStateOfTank(int player)
{
	switch (player)
	{
		case 1:
			return tanksUser1->getStateOfTank();
		case 2:
			return tanksUser2->getStateOfTank();
		default:
			return INVALID_TANK;
			break;
	}
}

bool Game::hasAnySelectedTank(int player)
{
	switch (player)
	{
		case 1:
			return tanksUser1->anySelectedTank();
		case 2:
			return tanksUser2->anySelectedTank();
		default:
			return false;
	}
}

bool Game::hasTanks(int player)
{
	switch (player)
	{
		case 1:
			return tanksUser1->hasTanks();
		case 2:
			return tanksUser2->hasTanks();
		default:
			return false;
			break;
	}
}

void Game::moveTank(int player, dir direction)
{
	switch (player)
	{
		case 1:
			tanksUser1->moveTank(direction);
			break;
		case 2:
			tanksUser2->moveTank(direction);
			break;
		default:
			break;
	}
}

void Game::newTurn()
{
	tanksUser1->newTurn();
	tanksUser2->newTurn();
}

void Game::selectDefaultTank(int player)
{
	switch (player)
	{
		case 1:
			tanksUser1->selectDefaultTank();
			break;
		case 2:
			tanksUser2->selectDefaultTank();
			break;
		default:
			break;
	}
}

void Game::selectNextTank(int player)
{
	switch (player)
	{
		case 1:
			if (tanksUser1->getSelectedTank() != tanksUser1->numTanks() - 1) tanksUser1->selectNextTank();
			else tanksUser1->selectNoTank();
			break;
		case 2:
			tanksUser2->selectNextTank();
			break;
		default:
			break;
	}

}

void Game::setTargetMode(int player)
{
	switch (player)
	{
		case 1:
			tanksUser1->setTargetMode();
			break;
		case 2:
			tanksUser2->setTargetMode();
			break;
		default:
			break;
	}
}

void Game::setWaitingMode(int player)
{
	switch (player)
	{
		case 1:
			tanksUser1->setWaitingMode();
			break;
		case 2:
			tanksUser2->setWaitingMode();
			break;
		default:
			break;
	}
}

void Game::shoot(int player, int x, int y, int z)
{
	switch (player)
	{
		case 1:
			tanksUser1->shoot(x, y, z);
			break;
		case 2:
			tanksUser2->shoot(x, y, z);
			break;
		default:
			break;
	}
}
