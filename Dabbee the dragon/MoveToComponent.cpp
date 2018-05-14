#include "MoveToComponent.h"
#include "GameObject.h"


MoveToComponent::MoveToComponent()
{
}


MoveToComponent::~MoveToComponent()
{
}

void MoveToComponent::update(float elapsedTime)
{
	gameObject->position.x = (1 - speed) * gameObject->position.x + speed * target.x;
	gameObject->position.y = (1 - speed) * gameObject->position.y + speed * target.y;
	gameObject->position.z = (1 - speed) * gameObject->position.z + speed * target.z;
}
