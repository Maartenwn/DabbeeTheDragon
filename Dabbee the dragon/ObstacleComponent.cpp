#include "ObstacleComponent.h"
#include <GL/freeglut.h>
#include "GameObject.h"


ObstacleComponent::ObstacleComponent()
{
	gapY = 0;

	this->width = 2;
	this->height = 2;
	this->depth = 0.75;
}

ObstacleComponent::~ObstacleComponent()
{

}

void ObstacleComponent::draw() {
	if (gameObject->position.z < 0) {
		return;
	}

	glPushMatrix();
	glTranslatef(0, gapY, 0);
	//glTranslatef(0, 0, 20);
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
