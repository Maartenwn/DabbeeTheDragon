#include "PlayerComponent.h"
#include "GameObject.h"
#include "MoveToComponent.h"
#include "MotionInput.h"
#include <iostream>



extern bool keys[256];
extern float flapspeed;

using namespace std;
#define MAXROTATE 45
int pc_timer = FALLINGTIMER/2;


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
	}

	if (keys['w']) {
		moveto->mt_speedcounter = -0.8f;
	}

	if (0 == pc_timer) {
		PlayerComponent* player = this;
		if (player->pc_rotation >= 45) { 
			if (player->pc_rotation < 90)
				player->pc_rotation--;
			else
				player->pc_rotation -= 3;
		}
		gameObject->rotation = { (float)player->pc_rotation,270,0 };
		pc_timer = FALLINGTIMER/2;
	}

	pc_timer--;
	flapspeed = 0.0f;
}
