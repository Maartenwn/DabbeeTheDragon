#include "PlayerComponent.h"
#include "GameObject.h"
#include "MoveToComponent.h"
#include <iostream>
extern bool keys[256];

using namespace std;
#define MAXROTATE 45

PlayerComponent::PlayerComponent()
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::update(float elapsedTime)
{
	if (keys['w']) {
		gameObject->position.y += elapsedTime * pc_speed;

		MoveToComponent* moveto = gameObject->getComponent<MoveToComponent>();
		moveto->mt_speedcounter = 1;		//gravitation reset
		//cout << moveto->mt_speedcounter << endl;

		//rotate player and camera with MAXROTATE - mt_amountLeftToRotate here
		moveto->mt_amountLeftToRotate = MAXROTATE;			//degree is back to normal
		pc_rotation = 0;
	}
}
