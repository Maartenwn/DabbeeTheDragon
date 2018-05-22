#pragma once

#include "DrawComponent.h"
#include "Vec.h"

class ObstacleComponent : public DrawComponent
{
public:

	float width;
	float height;
	float depth;

	float gapY;

	ObstacleComponent();
	~ObstacleComponent();
	GameObject* getGameObject();

	void draw();
};

