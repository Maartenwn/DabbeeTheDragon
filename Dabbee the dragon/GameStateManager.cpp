#include "GameStateManager.h"



GameStateManager::GameStateManager()
{
}


GameStateManager::~GameStateManager()
{
}

void GameStateManager::init()
{
	currentState = 0;
}

void GameStateManager::draw()
{
	states[currentState]->draw();
}

void GameStateManager::update(float deltaTime)
{
	states[currentState]->update(deltaTime);
}

void GameStateManager::deInit()
{
	for (auto &state : states) {
		state->deInit();
	}
}
