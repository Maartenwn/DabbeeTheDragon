#include "ObstacleGenerator.h"
#include <stdlib.h>
#include <iostream>


ObstacleGenerator::ObstacleGenerator()
{
	this->bottomObstacle = new ObstacleComponent(0);
	this->topObstacle = new ObstacleComponent(0);
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
		topTemp = new ObstacleComponent(4);
		topTemp->y = (MARGIN / 2) + randomHeight;
		bottemTemp = new ObstacleComponent(1);
		bottemTemp->y = (-MARGIN / 2) + randomHeight;
		

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
