#pragma once
#include "GameState.h"
class PlayingState :
	public GameState
{
public:
	PlayingState();
	~PlayingState();
	void draw();
	void update(float deltaTime);
	void init();
	void deInit();
};

