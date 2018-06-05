#include "DiveComponent.h"
#include "PlayerComponent.h"
#include "GameObject.h"
#include "MoveToComponent.h"
#include "MotionInput.h"
#include <iostream>

using namespace std;


DiveComponent::DiveComponent()
{
}

DiveComponent::~DiveComponent()
{
}

void DiveComponent::dive() {
	PlayerComponent* player = NULL;
	player = gameObject->getComponent<PlayerComponent>();
	MoveToComponent* moveTo = NULL;
	moveTo = gameObject->getComponent<MoveToComponent>();

	float rot = 90;
	float speed = moveTo->mt_speedcounter;

	float top = -(MAX_FLAP_SPEED * PLAYER_SPEED_MOD) / MAX_FLAP_SPEED;
	const float bot = PLAYER_SPEED_MOD;

	if (speed < top) {
		rot = PLAYER_ANGLE_TOP;
	}
	else if (speed >= bot) {
		rot = PLAYER_ANGLE_BOT;
	}else {
		float temp = PLAYER_ANGLE_BOT - PLAYER_ANGLE_TOP;
		rot = ((speed - top) / (bot - top) * (temp));
	}

	gameObject->rotation = { rot - 90 ,0,0 };
}

void DiveComponent::update(float elapsedTime) {
	dive();
};

