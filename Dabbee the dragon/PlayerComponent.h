#pragma once

#include "Component.h"

class PlayerComponent : public Component
{
			
public:
	float pc_speed = 15;
	int   pc_rotation = 0;

	PlayerComponent();
	~PlayerComponent();

	virtual void update(float elapsedTime) override;
};

