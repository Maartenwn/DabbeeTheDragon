#pragma once

#include "Component.h"

class PlayerComponent : public Component
{
	float speed = 15;
	float rotation = 0;
public:
	PlayerComponent();
	~PlayerComponent();

	virtual void update(float elapsedTime) override;
};

