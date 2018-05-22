#pragma once
class GameState
{
public:
	 GameState();
	~GameState();
	virtual void draw() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void init() = 0;
	virtual void deInit() = 0;
};

