#include "PlayerComponent.h"
#include "GameObject.h"
#include "MoveToComponent.h"
#include "MotionInput.h"
#include <iostream>

#define TICKS_TO_RISE 40

#include "CollisionComponent.h"
#include <iostream>
#define _USE_MATH_DEFINES

#include <math.h>

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

	float z = sin(gameObject->rotation.x * (M_PI/180)) * 1.85;
	float y = cos(gameObject->rotation.x * (M_PI / 180)) * 1.85;
	auto collision = gameObject->getComponent<CollisionComponent>();
	for (Cube* &hitbox : collision->hitboxes) {
		hitbox->maxPosition.z = z + 0.5 * hitbox->size.z;
		hitbox->maxPosition.y = y + 0.5 * hitbox->size.y;
		hitbox->position.z = z - hitbox->size.z/2;
		hitbox->position.y = y - hitbox->size.y/2;
	}


	flapspeed = 0.0f;
}
