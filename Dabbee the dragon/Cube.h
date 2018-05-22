#pragma once
#include "Vec.h"
#include <GL\freeglut.h>
class Cube
{
public:
	Cube(Vec3f position, Vec3f size);
	~Cube();
	Vec3f position;
	Vec3f maxPosition;
	void draw();
	bool collide(Vec3f pos1, Vec3f pos2, Cube toCheckCube);
};

