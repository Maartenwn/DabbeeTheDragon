#include "ObstacleGenerator.h"
#include <stdlib.h>
#include <iostream>


ObstacleGenerator::ObstacleGenerator()
{
	this->bottomObstacle = new ObstacleComponent();
	this->topObstacle = new ObstacleComponent();
}


ObstacleGenerator::~ObstacleGenerator()
{
}

void ObstacleGenerator::getNextObstacle() {
	ObstacleComponent* topTemp;
	ObstacleComponent* bottemTemp;
	do
	{
		int randomHeight = rand() % MARGIN_GAP_DISTANCE + 0; //random number between 0 and gap distance
		std::cout << randomHeight << std::endl;
		topTemp = new ObstacleComponent();
		topTemp->gapY = (MARGIN_GAP_HEIGHT / 2) + randomHeight;
		bottemTemp = new ObstacleComponent();
		bottemTemp->gapY = (-MARGIN_GAP_HEIGHT / 2) + randomHeight;
		

	} while (checkWithPreviousBottem(bottemTemp) && checkWithPreviousBottem(topTemp));
	
	topObstacle = topTemp;
	bottomObstacle = bottemTemp;

}

bool ObstacleGenerator::checkWithPreviousBottem(ObstacleComponent* obstacle){
	return false;
}

bool ObstacleGenerator::checkWithPreviousTop(ObstacleComponent* obstacle) {
	return false;
}
