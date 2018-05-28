#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "PlayingState.h"

class MainMenuState :
	public GameState
{
public:
	GameStateManager * manager;
	PlayingState * game;

	MainMenuState(GameStateManager* manager);
	~MainMenuState();
	void draw();
	void update(float deltaTime);
	void init();
	void deInit();
};

