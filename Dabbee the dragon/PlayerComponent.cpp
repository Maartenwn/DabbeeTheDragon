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
		cout << "Human flap" << endl;
		
		//float pos = elapsedTime * (((flapspeed * speed) / MAX_FLAP_SPEED));
		//gameObject->position.y += pos;

		MoveToComponent* moveto = gameObject->getComponent<MoveToComponent>();
		moveto->speedcounter = -(flapspeed * 2) / MAX_FLAP_SPEED;
	}

	flapspeed = 0.0f;
}
