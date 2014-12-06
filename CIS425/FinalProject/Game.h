#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Tank.h"
#include "Battalion.h"
#include "PantherBullet.h"
#include "PanzerBullet.h"
#include "TigerBullet.h"
#include "Texture.h"
#include "Utils.h"

#define GRID_SIZE 80

enum gameMenu{ NO_MENU, INITIAL_MENU, GAME_MENU };

class Game
{
private:
	std::vector<Battalion*> battalions;
	int activeBattalion;
	int targetBattalion;
	Bullet* bullet;
	bool createdBullet;
	Texture* myTextures;
	gameMenu currentMenu;
	float dayTime;
	float alpha;
public:
	Game();
	bool activeBattalionHasAnySelectedTank();
	void computeDamage(int damage, elem bulletType);
	bool currentPlayerHasAnySelectedTank();
	void draw();
	void drawBullet();
	void drawCurrentMenu();
	void drawGameMenu();
	void drawGrid();
	void drawInitialMenu();
	void drawSky();
	void drawStatus();
	void drawTerrain();
	void drawPlan();
	void getBullet();
	void getPosOfTheCurrentTank(float &x, float &y, float &z);
	void getPosOfSelectedTank(int player, float &x, float &y, float &z);
	void getPosOfTank(int player, int indOfTank, float &x, float &y, float &z);
	tankState getStateOfCurrentTank();
	tankState getStateOfTank(int player);
	bool hasAnySelectedTank(int player);
	bool hasTanks(int player);
	bool isTheGameOver();
	void moveCurrentTank(dir direction);
	void moveTank(int player, dir direction);
	void newTurn();
	void selectDefaultTank(int player);
	void selectDefaultTankForTheCurrentTargetPlayer();
	void selectFocus();
	void selectNextTank(int player);
	void setCurrentTankToTargetMode();
	void setCurrentTankToWaitingMode();
	void setMenu(gameMenu menu);
	void setTargetMode(int player);
	void setWaitingMode(int player);
	void shoot();
	void toggleMenu(gameMenu menu);
	void update();
	void writeCongrats();
};

#endif