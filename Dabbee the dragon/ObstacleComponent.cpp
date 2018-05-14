#include "ObstacleComponent.h"
#include <GL/freeglut.h>


ObstacleComponent::ObstacleComponent()
{
	//this->size = 10;

}

ObstacleComponent::ObstacleComponent(float height)
{
	y = 0;

	this->width = 2;
	this->height = 4;
	this->depth = 2;
}

ObstacleComponent::~ObstacleComponent()
{

}

void ObstacleComponent::draw() {
	
	glPushMatrix();
	glTranslatef(0, y, 0);
	glBegin(GL_QUADS);
	

	glColor3f(1, 0, 0);

		glVertex3f(-this->width, -this->height, -this->depth);
		glVertex3f(-this->width, -this->height, this->depth);
		glVertex3f(-this->width, this->height, this->depth);
		glVertex3f(-this->width, this->height, -this->depth);

		glVertex3f(this->width, -this->height, -this->depth);
		glVertex3f(this->width, -this->height, this->depth);
		glVertex3f(this->width, this->height, this->depth);
		glVertex3f(this->width, this->height, -this->depth);

		glColor3f(0, 1, 0);
		glVertex3f(-this->width, -this->height, -this->depth);
		glVertex3f(-this->width, -this->height, this->depth);
		glVertex3f(this->width, -this->height, this->depth);
		glVertex3f(this->width, -this->height, -this->depth);

		glVertex3f(-this->width, this->height, -this->depth);
		glVertex3f(-this->width, this->height, this->depth);
		glVertex3f(this->width, this->height, this->depth);
		glVertex3f(this->width, this->height, -this->depth);


	glColor3f(0, 0, 1);
	glVertex3f(-this->width, -this->height, -this->depth);
	glVertex3f(-this->width, this->height, -this->depth);
	glVertex3f(this->width, this->height, -this->depth);
	glVertex3f(this->width, -this->height, -this->depth);

	glVertex3f(-this->width, -this->height, this->depth);
	glVertex3f(-this->width, this->height, this->depth);
	glVertex3f(this->width, this->height, this->depth);
	glVertex3f(this->width, -this->height, this->depth);

	glEnd();
	glPopMatrix();
}