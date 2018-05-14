#include "TimerComponent.h"
#include "GameObject.h"
#include "MoveToComponent.h"



TimerComponent::TimerComponent()
{
}


TimerComponent::~TimerComponent()
{
}

void TimerComponent::update(float elapsedTime)
{
	timer -= elapsedTime;
	if (timer <= 0)
	{
		MoveToComponent* moveTo = gameObject->getComponent<MoveToComponent>();
		moveTo->target = Vec3f(gameObject->position.y, 0, 0);

		timer = 1;
	}

}
