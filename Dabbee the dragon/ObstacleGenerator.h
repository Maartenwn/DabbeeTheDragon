#pragma once

#include "ObstacleComponent.h"

class ObstacleGenerator
{
	static const int MARGIN = 5;
	
public:
	ObstacleComponent * topObstacle;
	ObstacleComponent *bottomObstacle;

	ObstacleGenerator();
	~ObstacleGenerator();

	void getNextObstacle();

private:
	bool checkWithPreviousBottem(ObstacleComponent* obstacle);
	bool checkWithPreviousTop(ObstacleComponent* obstacle);
};

