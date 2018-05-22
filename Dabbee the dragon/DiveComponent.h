#pragma once

#include "Component.h"

class DiveComponent : public Component{
public:

	DiveComponent();
	~DiveComponent();

	void dive();

	virtual void update(float elapsedTime) override;

};