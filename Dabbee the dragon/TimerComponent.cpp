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
		MoveToComponent* moveTo = gameObject->getComponent<MoveToComponent>();
		moveTo->target = Vec3f(0,- 1, 1.5f);

}
