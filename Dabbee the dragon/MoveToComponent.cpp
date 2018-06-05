#include "MoveToComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include <iostream>

using namespace std;
#define G 2.0f

MoveToComponent::MoveToComponent()
{
	mt_speedcounter = 1;
}


MoveToComponent::~MoveToComponent()
{
}

void MoveToComponent::update(float elapsedTime)
{
	gameObject->position.x += mt_speed * target.x * elapsedTime;
	gameObject->position.y += mt_speed * target.y * mt_speedcounter * elapsedTime;
	gameObject->position.z += mt_speed * target.z * elapsedTime;
	mt_speedcounter += G * elapsedTime;
	
}


