#pragma once

#include "DrawComponent.h"
#include "Vec.h"

class ObstacleComponent : public DrawComponent
{

	float width;
	float height;
	float depth;
	

public:

	float gapY;

	ObstacleComponent();
	~ObstacleComponent();

	virtual void draw() override;
};

