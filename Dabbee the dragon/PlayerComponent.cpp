#include "PlayerComponent.h"
#include "GameObject.h"
#include "MoveToComponent.h"
#include "MotionInput.h"
#include <iostream>

#define TICKS_TO_RISE 40

extern bool keys[256];
extern float flapspeed;

float cur, top, avg;

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
		top = -(flapspeed * PLAYER_SPEED_MOD) / MAX_FLAP_SPEED;
		cur = moveto->mt_speedcounter;
		avg = (top - cur) / TICKS_TO_RISE;
	}

	if (keys['w']) {
		top = -1.0f;
		cur = moveto->mt_speedcounter;
		avg = (top - cur) / TICKS_TO_RISE;
		keys['w'] = false;
	}

	if (cur > top) {
		moveto->mt_speedcounter += avg;
		cur += avg;
	}

	flapspeed = 0.0f;
}
