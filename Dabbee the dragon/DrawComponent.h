#pragma once

#include "Component.h"

class DrawComponent : public Component
{
public:
	DrawComponent();
	virtual ~DrawComponent() = 0;
	virtual void draw() = 0;
};

