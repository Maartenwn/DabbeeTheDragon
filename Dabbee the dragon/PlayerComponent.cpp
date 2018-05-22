#include "PlayerComponent.h"
#include "GameObject.h"
#include "MoveToComponent.h"
#include <iostream>
extern bool keys[256];

using namespace std;

PlayerComponent::PlayerComponent()
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::update(float elapsedTime)
{
	if (keys['w']) {
		gameObject->position.y += elapsedTime * speed;

		MoveToComponent* moveto = gameObject->getComponent<MoveToComponent>();
		moveto->speedcounter = 1;
		cout << moveto->speedcounter << endl;
	}
}
