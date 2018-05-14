#include "ObstacleGenerator.h"
#include <stdlib.h>


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
	ObstacleComponent* bottomTemp;
	do
	{
		int randomHeight = rand() % 10 + 1; //random number between 1 and 10
		topTemp = new ObstacleComponent(randomHeight);
		topTemp->y = -MARGIN;
		bottomTemp = new ObstacleComponent(randomHeight);
		bottomTemp->y = MARGIN;
		

	} while (checkWithPreviousBottem(bottomTemp) && checkWithPreviousBottem(topTemp));
	
	topObstacle = topTemp;
	bottomObstacle = bottomTemp;

}

bool ObstacleGenerator::checkWithPreviousBottem(ObstacleComponent* obstacle){
	return false;
}

bool ObstacleGenerator::checkWithPreviousTop(ObstacleComponent* obstacle) {
	return false;
}
