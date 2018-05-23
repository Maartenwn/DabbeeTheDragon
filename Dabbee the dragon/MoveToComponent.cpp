#include "MoveToComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include <iostream>

using namespace std;
#define G 0.005f

MoveToComponent::MoveToComponent()
{
}


MoveToComponent::~MoveToComponent()
{
}

void MoveToComponent::update(float elapsedTime)
{
	//gravitation
	gameObject->position.x += mt_speed * target.x * mt_speedcounter * elapsedTime;
	gameObject->position.y += mt_speed * target.y *mt_speedcounter * elapsedTime;
	gameObject->position.z += mt_speed * target.z * elapsedTime;// *mt_speedcounter;
	mt_speedcounter += G;	
}


