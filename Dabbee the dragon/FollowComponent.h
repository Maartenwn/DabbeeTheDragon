#pragma once

#include "Component.h"
#include "GameObject.h"


#define PLAYER_ANGLE_TOP  10;
#define PLAYER_ANGLE_BOT  145;

class FollowComponent : public Component {
public:

	GameObject *followObject;
	Vec3f followOffset;

	FollowComponent(GameObject *o, Vec3f);
	~FollowComponent();

	virtual void update(float elapsedTime) override;

};