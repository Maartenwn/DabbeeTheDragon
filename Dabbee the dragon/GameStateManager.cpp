#include "GameStateManager.h"
#include "PlayingState.h" 
#include "MainMenuState.h"
#include "GameState.h"
#include "MagicHands.h"

GameStateManager::GameStateManager()
{
	hand_init();
	init();
}


GameStateManager::~GameStateManager()
{
	deInit();
}

void GameStateManager::init()
{
	currentState = 0;
	states.push_back(new MainMenuState(this));
	states.push_back(new PlayingState(this));


	states[currentState]->init();
}

void GameStateManager::resize(int w, int h) {
	states[currentState]->resize(w, h);
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
	for (auto &state : states) {
		delete state;
	}
}

void GameStateManager::changeState(int state)
{
	cout << "Deinit state" << currentState << endl;
	states[currentState]->deInit();
	cout << "Deinit state done" << endl;

	currentState = state;

	cout << "init state" << state << endl;
	states[currentState]->init();
	cout << "init state done" << endl;
}
