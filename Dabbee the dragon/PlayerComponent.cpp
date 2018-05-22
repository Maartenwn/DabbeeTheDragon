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
	MoveToComponent* moveto = gameObject->getComponent<MoveToComponent>();

	if (flapspeed != 0.0f) {
		moveto->mt_speedcounter = -(flapspeed * 1.25) / MAX_FLAP_SPEED;
		cout << "human flap" << endl;
	}

	if (keys['w']) {
		moveto->mt_speedcounter = -0.8f;
		keys['w'] = false;
		cout << "computer flap" << endl;
	}

	flapspeed = 0.0f;
}
