#pragma once

#include "Component.h"
#include "Vec.h"

class MoveToComponent : public Component
{
public:
	float speed = 0.025f;
	Vec3f target;

	MoveToComponent();
	~MoveToComponent();

	virtual void update(float elapsedTime) override;
};

