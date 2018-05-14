#pragma once

#include "Component.h"

class TimerComponent : public Component
{
	float timer = 0;
	float targetX = -5;
public:
	TimerComponent();
	~TimerComponent();

	virtual void update(float elapsedTime) override;
};

#pragma once
