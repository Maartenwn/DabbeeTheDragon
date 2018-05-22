#pragma once
#include "Component.h"
#include "Cube.h"
#include <vector>
#include <list>

using namespace std;

class CollisionComponent :
	public Component
{
public:
	std::vector<Cube*> hitboxes;
	CollisionComponent();
	~CollisionComponent();
	void draw();
	void updateHitboxes(std::vector<Cube*> newHitboxes);
	void update();
	GameObject* checkCollision(std::list<GameObject*>);
};

