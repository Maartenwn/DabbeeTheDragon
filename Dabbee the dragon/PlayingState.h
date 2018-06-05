#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "Game.h"



class PlayingState :
	public GameState
{
private :
	Game* playingGame;
public:
	GameStateManager * manager;

	PlayingState(GameStateManager* manager);
	~PlayingState();

	void resize(int w, int h);
	void drawHUD();
	void draw();
	void update(float deltaTime);
	void init();
	void deInit();
};

