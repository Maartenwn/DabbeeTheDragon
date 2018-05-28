#pragma once
#include "GameStateManager.h"
class Game
{
private:
	GameStateManager* manager;
public:
	Game(GameStateManager* manager);
	~Game();
	void draw();
	float update(float deltaTime);
	void init();
	void deInit();
	void autoInput();
};

