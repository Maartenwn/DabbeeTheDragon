#pragma once

#include "Component.h"
#include "Vec.h"

class MoveToComponent : public Component
{
public:
	float speedcounter = 1;	//used for fall animation
	float speed = 0.005f;
	Vec3f target;

	MoveToComponent();
	~MoveToComponent();

	virtual void update(float elapsedTime) override;
};

