#pragma once

#include "ObstacleComponent.h"

class ObstacleGenerator
{
	static const int MARGIN_GAP_HEIGHT = 8;
	static const int MARGIN_GAP_DISTANCE = 3;
	
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

