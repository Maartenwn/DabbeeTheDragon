#include "Cube.h"


Cube::Cube(Vec3f newPosition,Vec3f size)
{
	this->position = newPosition;
	this->maxPosition = { position.x + size.x , position.y + size.y ,
	position.z + size.z };
	this->size = size;
}


Cube::~Cube()
{
	//delete &position;
	//delete &maxPosition;
}

void Cube::draw()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // this tells it to only render lines
	glBegin(GL_LINES);


	//bottem
	glVertex3f(position.x,position.y,position.z);
	glVertex3f(maxPosition.x, position.y, position.z);

	glVertex3f(maxPosition.x, position.y, position.z);
	glVertex3f(maxPosition.x, position.y, maxPosition.z);

	glVertex3f(maxPosition.x, position.y, maxPosition.z);
	glVertex3f(position.x, position.y, maxPosition.z);

	glVertex3f(position.x, position.y, maxPosition.z);
	glVertex3f(position.x, position.y, position.z);

	//up
	glVertex3f(position.x, maxPosition.y, position.z);
	glVertex3f(maxPosition.x, maxPosition.y, position.z);

	glVertex3f(maxPosition.x, maxPosition.y, position.z);
	glVertex3f(maxPosition.x, maxPosition.y, maxPosition.z);

	glVertex3f(maxPosition.x, maxPosition.y, maxPosition.z);
	glVertex3f(position.x, maxPosition.y, maxPosition.z);

	glVertex3f(position.x, maxPosition.y, maxPosition.z);
	glVertex3f(position.x, maxPosition.y, position.z);

	//sides
	glVertex3f(position.x, position.y, position.z);
	glVertex3f(position.x, maxPosition.y, position.z);

	glVertex3f(maxPosition.x, position.y, position.z);
	glVertex3f(maxPosition.x, maxPosition.y, position.z);

	glVertex3f(maxPosition.x, position.y, maxPosition.z);
	glVertex3f(maxPosition.x, maxPosition.y, maxPosition.z);

	glVertex3f(position.x, position.y, maxPosition.z);
	glVertex3f(position.x, maxPosition.y, maxPosition.z);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

bool Cube::collide(Vec3f pos1, Vec3f pos2, Cube toCheckCube)
{
	return(pos1.x + maxPosition.x >		pos2.x + toCheckCube.position.x &&
		pos1.x + position.x <			pos2.x + toCheckCube.maxPosition.x &&
		pos1.y + maxPosition.y >		pos2.y + toCheckCube.position.y &&
		pos1.y + position.y <			pos2.y + toCheckCube.maxPosition.y &&
		pos1.z + maxPosition.z >		pos2.z + toCheckCube.position.z &&
		pos1.z + position.z <			pos2.z + toCheckCube.maxPosition.z);
}
