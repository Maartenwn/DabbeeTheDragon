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
		int randomHeight = rand() % 3 + 0; //random number between 1 and 10
		std::cout << randomHeight << std::endl;
		topTemp = new ObstacleComponent();
		topTemp->gapY = (MARGIN / 2) + randomHeight;
		bottemTemp = new ObstacleComponent();
		bottemTemp->gapY = (-MARGIN / 2) + randomHeight;
		

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
