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

#define BUTTON_DEFAULT_WIDTH_PROP 0.2
#define BUTTON_DEFAULT_HEIGHT_PROP 0.1

enum gameState{ INITIAL_MENU, NEW_GAME, PLAYING, GAME_MENU, FINISH };

class Game
{
private:
	std::vector<Battalion*> battalions;
	int activeBattalion;
	int targetBattalion;
	Bullet* bullet;
	bool createdBullet;
	Texture* myTextures;
	gameState currentState;
	float dayTime;
	float alpha;
	int numPlayers;

	bool mouseOverResumeButton;
	bool mouseOverQuitButton;

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
	void drawNewGameMenu();
	void drawSky();
	void drawStatus();
	void drawTerrain();
	void drawPlan();
	void getBullet();
	gameState getGameState();
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
	void selectNoTank(int player);
	void setCurrentTankToTargetMode();
	void setCurrentTankToWaitingMode();
	void setMouseOverButtonsFalse();
	void setNumPlayers(int numPlyrs);
	void setState(gameState newState);
	void setTargetMode(int player);
	void setWaitingMode(int player);
	void shoot();
	void targetToWaitingMode();
	void togglePlayingAndState(gameState newState);
	void update(int clsName = 0, int mx = 0, int my = 0);
	void writeCongrats();

	void pickFunction(int button, int state, int s_x, int s_y);
};

#endif