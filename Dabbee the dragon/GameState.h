#pragma once
#ifndef HGAMESTATE
#define HGAMESTATE

class GameState
{
public:
	GameState();
	~GameState();

	virtual void resize(int w, int h) = 0;
	virtual void draw() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void init() = 0;
	virtual void deInit() = 0;
};

#endif // !HGAMESTATE



