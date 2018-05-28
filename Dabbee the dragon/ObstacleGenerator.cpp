#include "ObstacleGenerator.h"
#include <stdlib.h>
#include <iostream>

int obstacleCount;

ObstacleGenerator::ObstacleGenerator()
{
	this->bottomObstacle = new ObstacleComponent();
	this->topObstacle = new ObstacleComponent();

	obstacleCount = 1;
}


ObstacleGenerator::~ObstacleGenerator()
{
}

float ObstacleGenerator::getNextObstacle() {
	ObstacleComponent* topTemp;
	ObstacleComponent* bottemTemp;
	do
	{
		int randomHeight = rand() % MAX_GAP_DISTANCE + 0; //random number between 0 and gap distance
		std::cout << randomHeight << std::endl;
		topTemp = new ObstacleComponent();
		topTemp->gapY = (MARGIN_GAP_HEIGHT / 2) + randomHeight;
		bottemTemp = new ObstacleComponent();
		bottemTemp->gapY = (-MARGIN_GAP_HEIGHT / 2) + randomHeight;
	} while (checkWithPreviousBottem(bottemTemp) && checkWithPreviousBottem(topTemp));
	
	topObstacle = topTemp;
	bottomObstacle = bottemTemp;

	obstacleCount++;
	return (obstacleCount - 1) * 7.5;
}

//float* ObstacleGenerator::getPosition() {
	//return (float)obstacleCount * 7.5;
//}

bool ObstacleGenerator::checkWithPreviousBottem(ObstacleComponent* obstacle){
	return false;
}

bool ObstacleGenerator::checkWithPreviousTop(ObstacleComponent* obstacle) {
	return false;
}
