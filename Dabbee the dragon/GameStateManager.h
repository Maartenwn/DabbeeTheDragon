#pragma once
#ifndef HGAMESTATEMANAGER
#define HGAMESTATEMANAGER

#include <vector>
#include <iostream>
#include "GameState.h"


using namespace std;

class GameStateManager
{
public:
	int currentState;
	vector<GameState*> states;
	GameStateManager();
	~GameStateManager();
	void init();
	void draw();
	void update(float deltaTime);
	void deInit();
	void changeState(int state);
};

#endif // !HGAMESTATEMANAGER


