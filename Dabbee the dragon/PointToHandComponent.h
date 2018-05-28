#pragma once

#include "Component.h"

class PointToHandComponent : public Component {
public:
	
	bool leftHand;

	PointToHandComponent(bool);
	~PointToHandComponent();

	virtual void update(float elapsedTime) override;

};