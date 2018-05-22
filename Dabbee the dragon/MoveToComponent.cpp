#include "MoveToComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include <iostream>

using namespace std;

#define G 0.02f

int timer = 100;
MoveToComponent::MoveToComponent()
{
}


MoveToComponent::~MoveToComponent()
{
}

void MoveToComponent::update(float elapsedTime)
{
	//gravitation
	gameObject->position.x += mt_speed * target.x * mt_speedcounter;
	gameObject->position.y += mt_speed * target.y * mt_speedcounter;
	gameObject->position.z += mt_speed * target.z * mt_speedcounter;
	mt_speedcounter += G;	

	rotate();
}


void MoveToComponent::rotate() {
	if (0 == timer) {
		PlayerComponent* player = gameObject->getComponent<PlayerComponent>();
		if (mt_amountLeftToRotate <= 0) { player->pc_rotation = mt_amountLeftToRotate; }	  //if player rotated more than 45 degree set it to 45 degree 
		else { mt_amountLeftToRotate -= ++player->pc_rotation; }
		if (mt_amountLeftToRotate != 0) { cout << mt_amountLeftToRotate << endl; }
		timer = 100;

		//rotate player and camera with mt_amountLeftToRotate if(player->pc_rotation <0) set flag and rotate once
	}
	timer--;
}