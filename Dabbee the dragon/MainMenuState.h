#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "Game.h"

class MainMenuState :
	public GameState
{
public:
	GameStateManager * manager;
	Game * game;

	MainMenuState(GameStateManager* manager);
	~MainMenuState();
	void draw();
	void update(float deltaTime);
	void init();
	void deInit();
	void resize(int w, int h);
};

