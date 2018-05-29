#include "GameObject.h"
#include "DrawComponent.h"
#include "CollisionComponent.h"
#include <GL/freeglut.h>

extern bool debugon;

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::addComponent(Component * component)
{
	component->setGameObject(this);
	components.push_back(component);

	if (!collisionComponent) {
		collisionComponent = dynamic_cast<CollisionComponent*>(component);
	}
	if (!drawComponent)
		drawComponent = dynamic_cast<DrawComponent*>(component);
}

std::list<Component*> GameObject::getComponents()
{
	return components;
}


void GameObject::draw()
{
	if (!drawComponent)
		return;
	
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	if (collisionComponent && debugon) {
		collisionComponent->draw();
	}
	glScalef(scale.x, scale.y, scale.z);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	drawComponent->draw();
	glPopMatrix();
}

void GameObject::update(float elapsedTime)
{
	for (auto &c : components)
		c->update(elapsedTime);
}