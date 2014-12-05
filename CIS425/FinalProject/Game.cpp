#include "Game.h"

Game::Game() : bullet(NULL), createdBullet(false), myTextures(new Texture()), currentState(INITIAL_MENU),
		       activeBattalion(0), targetBattalion(1), dayTime(0.f), alpha(0)
{
	battalions.push_back(new Battalion(1));
	battalions.push_back(new Battalion(2));
	battalions.push_back(new Battalion(3));
}

bool Game::activeBattalionHasAnySelectedTank()
{
	return hasAnySelectedTank(activeBattalion);
}

void Game::computeDamage(int damage, elem bulletType)
{
	battalions[targetBattalion]->computeDamage(damage, bulletType);
}

bool Game::currentPlayerHasAnySelectedTank()
{
	return battalions[activeBattalion]->hasAnySelectedTank();
}

void Game::draw()
{
	drawTerrain();
	drawSky();
	drawGrid();
	for (unsigned int i = 0; i < battalions.size(); i++)
	{
		if (i==activeBattalion)	battalions[i]->draw(ATTACKING);
		else if (i == targetBattalion) battalions[i]->draw(DEFENDING);
		else battalions[i]->draw(INACTIVE);
	}
	
	drawBullet();
	drawStatus();
	drawCurrentMenu();
	if (isTheGameOver()) writeCongrats();
}

void Game::drawBullet()
{
	if (bullet != NULL) bullet->draw();
}

void Game::drawCurrentMenu() //todo: implement it
{
	switch (currentState)
	{
		case INITIAL_MENU:
			break;
		default:
			break;
	}
}

void Game::drawGrid()
{
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	for (int i = -GRID_SIZE / 2; i < GRID_SIZE / 2; i++)
	{
		for (int j = -GRID_SIZE / 2; j < GRID_SIZE / 2; j++)
		{
			glBegin(GL_LINE_STRIP);
			glVertex3f(i, 0.01, j);
			glVertex3f(i + 1, 0.01, j);
			glVertex3f(i + 1, 0.01, j + 1);
			glVertex3f(i, 0.01, j + 1);
			glEnd();
		}
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void Game::drawPlan()
{
	glColor4f(.5, .5, .5, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-GRID_SIZE / 2, 0, -GRID_SIZE / 2);
	glVertex3f(GRID_SIZE / 2, 0, -GRID_SIZE / 2);
	glVertex3f(GRID_SIZE / 2, 0, GRID_SIZE / 2);
	glVertex3f(-GRID_SIZE / 2, 0, GRID_SIZE / 2);
	glEnd();
	glColor4f(1.0, 1.0, 1.0, 1.0);
}

void Game::drawSky()
{
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, LIGHT_SKY + 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-GRID_SIZE, GRID_SIZE, -15);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(GRID_SIZE, GRID_SIZE, -15);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(GRID_SIZE, 0, -15);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-GRID_SIZE, 0, -15);
	glEnd();

	glColor4f(1.0, 1.0, 1.0, dayTime);

	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, DARK_SKY + 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-GRID_SIZE, GRID_SIZE, -15);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(GRID_SIZE, GRID_SIZE, -15);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(GRID_SIZE, 0, -15);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-GRID_SIZE, 0, -15);
	glEnd();
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_TEXTURE_2D);
	glColor4f(1.0, 1.0, 1.0, 1.0);
}

void Game::drawStatus()
{
	float x, y, z;

	//black background
	glColor4f(1.0, 1.0, 1.0, 1.0);

	for (std::vector<Battalion*>::iterator bt = battalions.begin(); bt != battalions.end(); bt++)
	{
		std::vector<const Tank*> tanks = (*bt)->getAllTanks();
		for (unsigned int i = 0; i < tanks.size(); i++)
		{
			char buffer[256];
			sprintf(buffer, "%d/%d", tanks[i]->getLife(), tanks[i]->getMaxLife());
			std::string text = buffer;
			tanks[i]->getPos(x, y, z);
			writeText(text, x, y + 1.f, z, false);
			y -= 24;
		}
	}
}

void Game::drawTerrain()
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, LIGHT_GROUND + 1);
	for (int i = -GRID_SIZE/2; i < GRID_SIZE/2; i+=5)
	{
		for (int j = -GRID_SIZE/2; j < GRID_SIZE/2; j+=5)
		{	
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0, j);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 5, 0, j);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 5, 0, j + 5);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0, j + 5);
			glEnd();
		}
	}

	glColor4f(1.0f, 1.0f, 1.0f, dayTime);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, DARK_GROUND + 1);
	for (int i = -GRID_SIZE / 2; i < GRID_SIZE / 2; i += 5)
	{
		for (int j = -GRID_SIZE / 2; j < GRID_SIZE / 2; j += 5)
		{
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0, j);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 5, 0, j);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 5, 0, j + 5);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0, j + 5);
			glEnd();
		}
	}
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
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
	int count = battalions.size();
	for (unsigned int i = 0; i < battalions.size(); i++)
	{
		if (battalions[i]->numTanks() == 0) count -= 1;
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
	bool aPlayerIsDead = true;
	while (aPlayerIsDead)
	{
		aPlayerIsDead = false;
		for (unsigned int i = 0; i < battalions.size(); i++)
		{
			if (battalions[i]->numTanks() == 0)
			{
				battalions.erase(battalions.begin() + i);
				aPlayerIsDead = true;
				break;
			}
		}
	}
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
			computeDamage(bullet->getDamage(), bullet->getType());
			createdBullet = false;
			bullet = NULL;
		}
	}
	alpha += 0.1;
	dayTime = sin(degToRad(alpha));
	if (alpha > 180) alpha = 0;
}

void Game::writeCongrats()
{
	std::cout << "game is over" << std::endl;
}
