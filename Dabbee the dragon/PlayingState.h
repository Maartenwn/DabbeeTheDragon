#pragma once
#include "GameState.h"
#include "GameStateManager.h"


class PlayingState :
	public GameState
{
public:
	GameStateManager * manager;

	PlayingState(GameStateManager* manager);
	~PlayingState();

	void drawHUD();
	void draw();
	void update(float deltaTime);
	void init();
	void deInit();
};

