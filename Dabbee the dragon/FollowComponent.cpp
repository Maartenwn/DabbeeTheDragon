#include "FollowComponent.h"


FollowComponent::FollowComponent(GameObject * o, Vec3f offset)
{
	followObject = o;
	followOffset = offset;
}

FollowComponent::~FollowComponent()
{
	followObject = NULL;
	
}

void FollowComponent::update(float elapsedTime)
{
	gameObject->position.x = followObject->position.x + followOffset.x;
	gameObject->position.y = followObject->position.y + followOffset.y;
	gameObject->position.z = followObject->position.z + followOffset.z;

	gameObject->rotation.x = followObject->rotation.x;

	gameObject->rotation.z = 60;

}
