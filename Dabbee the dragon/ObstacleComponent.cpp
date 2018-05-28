#include "ObstacleComponent.h"
#include <GL/freeglut.h>
#include "GameObject.h"


ObstacleComponent::ObstacleComponent()
{
	gapY = 0;

	this->width = 4;
	this->height = 4;
	this->depth = 1.5;
}

ObstacleComponent::~ObstacleComponent()
{

}

GameObject * ObstacleComponent::getGameObject()
{
	return gameObject;
}

void ObstacleComponent::draw() {
	if (gameObject->position.z < 0) {
		return;
	}

	glPushMatrix();
	//glTranslatef(0, gapY, 0);
	//glTranslatef(0, 0, 20);
	glBegin(GL_LINES);
	

	glColor3f(1, 0, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, this->depth);
		glVertex3f(0, this->height, this->depth);
		glVertex3f(0, this->height, 0);

		glVertex3f(this->width, 0, 0);
		glVertex3f(this->width, 0, this->depth);
		glVertex3f(this->width, this->height, this->depth);
		glVertex3f(this->width, this->height, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, this->depth);
		glVertex3f(this->width, 0, this->depth);
		glVertex3f(this->width, 0, 0);

		glVertex3f(0, this->height, 0);
		glVertex3f(0, this->height, this->depth);
		glVertex3f(this->width, this->height, this->depth);
		glVertex3f(this->width, this->height, 0);


	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, this->height, 0);
	glVertex3f(this->width, this->height, 0);
	glVertex3f(this->width, 0, 0);

	glVertex3f(0, 0, this->depth);
	glVertex3f(0, this->height, this->depth);
	glVertex3f(this->width, this->height, this->depth);
	glVertex3f(this->width, 0, this->depth);

	glEnd();
	glPopMatrix();
}
