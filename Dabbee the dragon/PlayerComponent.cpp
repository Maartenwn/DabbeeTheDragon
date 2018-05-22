#include "PlayerComponent.h"
#include "GameObject.h"
#include "MoveToComponent.h"
#include "CollisionComponent.h"
#include <iostream>
#define _USE_MATH_DEFINES

#include <math.h>
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
	float z = sin(gameObject->rotation.x * (M_PI/180)) * 1.85;
	float y = cos(gameObject->rotation.x * (M_PI / 180)) * 1.85;
	auto collision = gameObject->getComponent<CollisionComponent>();
	for (Cube* &hitbox : collision->hitboxes) {
		hitbox->maxPosition.z = z + 0.5 * hitbox->size.z;
		hitbox->maxPosition.y = y + 0.5 * hitbox->size.y;
		hitbox->position.z = z - hitbox->size.z/2;
		hitbox->position.y = y - hitbox->size.y/2;
	}
	if (keys['w']) {
		gameObject->position.y += elapsedTime * pc_speed;

		MoveToComponent* moveto = gameObject->getComponent<MoveToComponent>();
		moveto->mt_speedcounter = 1;		//gravitation reset

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
