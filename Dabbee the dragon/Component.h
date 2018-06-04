#pragma once
#include <iostream>
class GameObject;

class Component
{
protected:
	GameObject* gameObject;
public:
	Component();
	virtual ~Component() {};

	virtual void update(float elapsedTime) {};

	inline void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
};

