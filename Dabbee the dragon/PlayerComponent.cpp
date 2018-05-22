#include "PlayerComponent.h"
#include "GameObject.h"
#include "MoveToComponent.h"
#include "MotionInput.h"
#include <iostream>



extern bool keys[256];
extern float flapspeed;

using namespace std;

PlayerComponent::PlayerComponent()
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::update(float elapsedTime)
{
	if (flapspeed != 0.0f) {
		MoveToComponent* moveto = gameObject->getComponent<MoveToComponent>();
		moveto->speedcounter = -(flapspeed * 1.5) / MAX_FLAP_SPEED;
	}

	if (keys['w']) {
		MoveToComponent* moveto = gameObject->getComponent<MoveToComponent>();
		moveto->speedcounter = -0.8f;
	}


	flapspeed = 0.0f;
}
