#include "PlayerComponent.h"
#include "GameObject.h"
#include "MoveToComponent.h"
#include <iostream>
extern bool keys[256];

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
	if (keys['w']) {
		gameObject->position.y += elapsedTime * pc_speed;

		MoveToComponent* moveto = gameObject->getComponent<MoveToComponent>();
		moveto->mt_speedcounter = 1;		//gravitation reset
		//cout << moveto->mt_speedcounter << endl;

		if (0 == pc_timer) {
			PlayerComponent* player = gameObject->getComponent<PlayerComponent>();
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

	}
}
