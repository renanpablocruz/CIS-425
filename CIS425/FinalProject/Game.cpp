#include "Game.h"

Game::Game() : bullet(NULL), createdBullet(false), myTextures(new Texture()),activeBattalion(-1), targetBattalion(-1),
				dayTime(0.f), alpha(0), currentState(INITIAL_MENU), numPlayers(0)
{
	setMouseOverButtonsFalse();
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
	if (currentState == PLAYING || currentState == GAME_MENU)
	{
		drawTerrain();
		drawSky();
		drawGrid();
		for (unsigned int i = 0; i < battalions.size(); i++)
		{
			if (i == activeBattalion)	battalions[i]->draw(ATTACKING);
			else if (i == targetBattalion) battalions[i]->draw(DEFENDING);
			else battalions[i]->draw(INACTIVE);
		}
		drawBullet();
		drawStatus();
	}
	else if (currentState == FINISH) writeCongrats();
	drawCurrentMenu();
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
			drawInitialMenu();
			break;
		case NEW_GAME:
			drawNewGameMenu();
			break;
		case GAME_MENU:
			drawGameMenu();
			break;
		default:
			break;
	}
}

void Game::drawGameMenu()
{
	float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT);
	drawBackground(BLACK, 0.4);
	drawButton(0.5*w, 0.60*h, BUTTON_DEFAULT_WIDTH_PROP*w, BUTTON_DEFAULT_HEIGHT_PROP*h, "RESUME", GLUT_BITMAP_HELVETICA_18);
	drawButton(0.5*w, 0.40*h, BUTTON_DEFAULT_WIDTH_PROP*w, BUTTON_DEFAULT_HEIGHT_PROP*h, "QUIT", GLUT_BITMAP_HELVETICA_18);
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

void Game::drawInitialMenu()
{
	float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT);
	drawBackground(GRAY);
	drawImage(0.5*w, 0.5*h, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), TANK_DRAWING);
	drawWindow(0.5*w, 0.7*h, 0.25*w, 0.3*h);
	writeText2d("CLASH OF", w / 2, 0.75*h, true, GLUT_BITMAP_TIMES_ROMAN_24);
	writeText2d("TANKS", w / 2, 0.65*h, true, GLUT_BITMAP_TIMES_ROMAN_24);
	drawButton(w / 2, 0.35*h, BUTTON_DEFAULT_WIDTH_PROP*w, BUTTON_DEFAULT_HEIGHT_PROP*h, "NEW GAME", GLUT_BITMAP_HELVETICA_18);
	drawButton(w / 2, 0.2*h, BUTTON_DEFAULT_WIDTH_PROP*w, BUTTON_DEFAULT_HEIGHT_PROP*h, "QUIT", GLUT_BITMAP_HELVETICA_18);
}

void Game::drawNewGameMenu()
{
	float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT);
	drawBackground(GRAY);
	drawImage(0.5*w, 0.5*h, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), TANK_DRAWING);
	drawWindow(0.5*w, 0.7*h, 0.25*w, 0.3*h);
	writeText2d("CLASH OF", w / 2, 0.75*h, true, GLUT_BITMAP_TIMES_ROMAN_24);
	writeText2d("TANKS", w / 2, 0.65*h, true, GLUT_BITMAP_TIMES_ROMAN_24);
	drawButton(0.25*w, 0.25*h, BUTTON_DEFAULT_WIDTH_PROP*w, BUTTON_DEFAULT_HEIGHT_PROP*h, "2 PLAYERS", GLUT_BITMAP_HELVETICA_18);
	drawButton(0.5*w, 0.25*h, BUTTON_DEFAULT_WIDTH_PROP*w, BUTTON_DEFAULT_HEIGHT_PROP*h, "3 PLAYERS", GLUT_BITMAP_HELVETICA_18);
	drawButton(0.75*w, 0.25*h, BUTTON_DEFAULT_WIDTH_PROP*w, BUTTON_DEFAULT_HEIGHT_PROP*h, "BACK", GLUT_BITMAP_HELVETICA_18);
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

	int j = 0;

	for (std::vector<Battalion*>::iterator bt = battalions.begin(); bt != battalions.end(); bt++)
	{
		if (j == 0) glColor4f(1, 1, 1, 1.0);
		else if (j == 1) glColor4f(0.75, .75, .75, 1.0);
		else glColor4f(1, 0, 0, 1.0);
		j++;

		std::vector<const Tank*> tanks = (*bt)->getAllTanks();
		for (unsigned int i = 0; i < tanks.size(); i++)
		{
			char buffer[256];
			sprintf_s(buffer, 256, "%d/%d", tanks[i]->getLife(), tanks[i]->getMaxLife());
			std::string text = buffer;
			tanks[i]->getPos(x, y, z);
			writeText3d(text, x, y + 1.f, z, false, GLUT_BITMAP_HELVETICA_18);
			y -= 24;
		}
	}
}

void Game::drawTerrain()
{
	//glEnable(GL_DEPTH_TEST);
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

gameState Game::getGameState()
{
	return currentState;
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
		{
			selectNextTank(activeBattalion);
			selectNoTank(targetBattalion);
		}
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

void Game::selectNoTank(int player)
{
	battalions[player]->selectNoTank();
}

void Game::setCurrentTankToTargetMode()
{
	battalions[activeBattalion]->setTargetMode();
}

void Game::setCurrentTankToWaitingMode()
{
	battalions[activeBattalion]->setWaitingMode();
}

void Game::setMouseOverButtonsFalse()
{
	mouseOverResumeButton = false;
	mouseOverQuitButton = false;
}

void Game::setNumPlayers(int numPlyrs)
{
	int num = 0;
	while (num < numPlyrs)
	{
		battalions.push_back(new Battalion(num));
		num += 1;
	}
	activeBattalion = 0;
	targetBattalion = 1;
}

void Game::setState(gameState newState)
{
	currentState = newState;
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

void Game::targetToWaitingMode()
{
	setCurrentTankToWaitingMode();
	selectNoTank(targetBattalion);
}

void Game::update(int clsName, int mx, int my)
{

	if (currentState == PLAYING && isTheGameOver())
	{
		currentState = FINISH;
		return;
	}

	for (unsigned int i = 0; i < battalions.size(); i++) battalions[i]->update(DELTA_T_VIRTUAL);

	if (bullet != NULL)
	{
		if (bullet->getState() != READY && createdBullet == false)
			createdBullet = true;
		else if (bullet->getState() == READY && createdBullet == true)
		{
			computeDamage(bullet->getDamage(), bullet->getType());
			selectNoTank(targetBattalion);
			createdBullet = false;
			bullet = NULL;
		}
	}

	switch (currentState)
	{
		case INITIAL_MENU:
			break;
		case NEW_GAME:
			break;
		case PLAYING:
			alpha += 0.1;
			dayTime = sin(degToRad(alpha));
			if (alpha > 180) alpha = 0;
			break;
		case GAME_MENU:
			break;
		default:
			break;
	}
}

void Game::toggleBetweenStates(gameState stateA, gameState stateB)
{
	if (currentState == stateA) currentState = stateB;
	else if (currentState == stateB) currentState = stateA;
	//throw std::string("My exception");
}

void Game::writeCongrats()
{
	float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT);
	drawWindow(w/2, h/2, 150, 70);
	char buffer[256];
	//sprintf(buffer, "Player %d won", activeBattalion+1);
	sprintf_s(buffer, 256, "Player %d won", activeBattalion + 1);
	std::string text = buffer;
	writeText2d(buffer, w/2, h/2, true, GLUT_BITMAP_HELVETICA_18);
}

void Game::pickFunction(int button, int state, int s_x, int s_y)
{
	
	float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT);

	std::cout << "x: " << s_x << ", y: " << s_y << std::endl;
	std::cout << "inf_x: " << 0.4*w << ", sup_x: " << 0.6*w << std::endl;
	std::cout << "inf_y: " << 0.4*h << ", sup_y: " << 0.5*h << std::endl;

	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

	switch (currentState)
	{
		case INITIAL_MENU:
			if (s_x > 0.4*w && s_x < 0.6*w && s_y < 0.75*h && s_y > 0.55*h) // new game button
				setState(NEW_GAME);
			else if (s_x > 0.4*w && s_x < 0.6*w && s_y < 0.85*h && s_y > 0.75*h) // quit button
				exit(0);
			break;
		case NEW_GAME:
			//std::cout << "catch it" << std::endl;
			if (s_x > 0.15*w && s_x < 0.35*w && s_y < 0.8*h && s_y > 0.7*h) // 2 player button
			{
				setNumPlayers(2);
				setState(PLAYING);
			}
			else if (s_x > 0.4*w && s_x < 0.6*w && s_y < 0.8*h && s_y > 0.7*h) // 3 players button
			{
				setNumPlayers(3);
				setState(PLAYING);
			}
			else if (s_x > 0.65*w && s_x < 0.85*w && s_y < 0.8*h && s_y > 0.7*h) // back button
				setState(INITIAL_MENU);
			break;
		case GAME_MENU:
			if (s_x > 0.4*w && s_x < 0.6*w && s_y < 0.45*h && s_y > 0.25*h) // resume button
				setState(PLAYING);
			else if (s_x > 0.4*w && s_x < 0.6*w && s_y < 0.75*h && s_y > 0.55*h) // quit button
				exit(0);
			break;
		default:
			break;
	}

	glutPostRedisplay();
}
