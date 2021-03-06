#pragma once

#include "ObstacleComponent.h"

class ObstacleGenerator
{
	static const int MARGIN_GAP_HEIGHT = 10;
	static const int MAX_GAP_DISTANCE = 8;
	
public:
	ObstacleComponent * topObstacle;
	ObstacleComponent *bottomObstacle;

	ObstacleGenerator();
	~ObstacleGenerator();

	float getNextObstacle();

private:
	bool checkWithPreviousBottem(ObstacleComponent* obstacle);
	bool checkWithPreviousTop(ObstacleComponent* obstacle);
};

