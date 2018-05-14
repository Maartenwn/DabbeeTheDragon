#include "PlayerComponent.h"
#include "GameObject.h"

extern bool keys[256];



PlayerComponent::PlayerComponent()
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::update(float elapsedTime)
{
	if (keys['w'])
		gameObject->position.y += elapsedTime * speed;


}
