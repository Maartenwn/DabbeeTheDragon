#pragma once

#include "Component.h"


#define PLAYER_ANGLE_TOP  10;
#define PLAYER_ANGLE_BOT  135;

class DiveComponent : public Component{
public:

	DiveComponent();
	~DiveComponent();

	void dive();

	virtual void update(float elapsedTime) override;

};