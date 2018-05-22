#include "MoveToComponent.h"
#include "GameObject.h"

MoveToComponent::MoveToComponent()
{
}


MoveToComponent::~MoveToComponent()
{
}

void MoveToComponent::update(float elapsedTime)
{
	gameObject->position.x += speed * target.x * speedcounter;
	gameObject->position.y += speed * target.y * speedcounter;
	gameObject->position.z += speed * target.z * speedcounter;
	speedcounter += 0.003f;	//speedcounter schould be set to 0 when w(or flap detected) is pressed 
}
