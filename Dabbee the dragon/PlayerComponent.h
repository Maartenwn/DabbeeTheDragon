#pragma once

#include "Component.h"

#define PLAYER_SPEED_MOD 2.5

class PlayerComponent : public Component
{
			
public:
	float pc_speed = 15;

	PlayerComponent();
	~PlayerComponent();

	virtual void update(float elapsedTime) override;
};

