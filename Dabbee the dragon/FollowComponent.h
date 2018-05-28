#pragma once

#include "Component.h"
#include "GameObject.h"

class FollowComponent : public Component {
public:

	GameObject *followObject;
	Vec3f followOffset;

	FollowComponent(GameObject *o, Vec3f);
	~FollowComponent();

	virtual void update(float elapsedTime) override;

};