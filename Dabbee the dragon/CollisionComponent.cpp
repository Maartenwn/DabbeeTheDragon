#include "CollisionComponent.h"
#include "GameObject.h"
#include <iostream>



CollisionComponent::CollisionComponent()
{
}


CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::draw()
{
	for(Cube* &hitbox : hitboxes)
	{
		hitbox->draw();
	}
}

void CollisionComponent::updateHitboxes(std::vector<Cube*> newHitboxes)
{
	//delete &hitboxes;
	this->hitboxes = newHitboxes;
}

void CollisionComponent::update()
{

}

GameObject* CollisionComponent::checkCollision(std::list<GameObject*> objects)
{
	for (auto &object : objects)
	{
		if (object != gameObject) {
			CollisionComponent* collision = object->getComponent<CollisionComponent>();
			for (Cube* &cube : hitboxes) {
				for (Cube* &cube2 : collision->hitboxes) {
					if (cube->collide(gameObject->position, object->position, *cube2)) {
						return object;
					}
				}
			}
		}
	}
	return NULL;
}
