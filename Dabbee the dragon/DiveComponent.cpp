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
	PlayerComponent* player = gameObject->getComponent<PlayerComponent>();
	MoveToComponent* moveTo = gameObject->getComponent<MoveToComponent>();

	float rot = 90;
	float speed = moveTo->mt_speedcounter;

	float top = -(MAX_FLAP_SPEED * 1.25) / MAX_FLAP_SPEED; // -1.25
	const float bot = 2; 

	if (speed < top) {
		rot = PLAYER_ANGLE_TOP;
	}
	else if (speed > bot) {
		rot = PLAYER_ANGLE_BOT;
	}else {
		float temp = PLAYER_ANGLE_BOT - PLAYER_ANGLE_TOP;
		rot = ((speed - top) / (bot - top) * (temp)) + PLAYER_ANGLE_TOP;
	}

	gameObject->rotation = { rot ,270,0 };
}

void DiveComponent::update(float elapsedTime) {
	dive();
};