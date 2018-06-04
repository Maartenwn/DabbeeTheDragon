#include "MagicHands.h"
#include <GL/freeglut.h>
#include "Texture.h"
#include "vec.h"
#include <opencv2\features2d\features2d.hpp>
#define GSIZE 50

Vec2f motionO;

Texture* lefthand;
Texture* righthand;

extern cv::Point leftHandPoint, rightHandPoint;
cv::Point lhp, rhp;
extern int width, height;
void hand_draw() {

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	lefthand->bind();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 0.5);//Replace this alpha for transparency

	glPushMatrix();
	glTranslatef(lhp.x, lhp.y, 0);
	float rotationL = atan2(lhp.y - motionO.y, lhp.x - motionO.x) * 180.0f / 3.1415f;
	glRotatef(rotationL + 90, 0, 0, 1);
	glBegin(GL_QUADS);
	if (leftHandPoint.x != -1)
		lhp = leftHandPoint;
	glTexCoord2f(1, 1);		glVertex2f(-GSIZE, -GSIZE);
	glTexCoord2f(0, 1);		glVertex2f(GSIZE, -GSIZE);
	glTexCoord2f(0, 0);		glVertex2f(GSIZE, GSIZE);
	glTexCoord2f(1, 0);		glVertex2f(-GSIZE, GSIZE);
	glEnd();
	glPopMatrix();

	righthand->bind();
	glPushMatrix();
	glTranslatef(rhp.x, rhp.y, 0);
	float rotationR = atan2(rhp.y - motionO.y, rhp.x - motionO.x) * 180.0f / 3.1415f;
	glRotatef(rotationR - 270, 0, 0, 1);
	glBegin(GL_QUADS);
	if (rightHandPoint.x != -1)
		rhp = rightHandPoint;

	glTexCoord2f(1, 1);		glVertex2f(-GSIZE, -GSIZE);
	glTexCoord2f(0, 1);		glVertex2f(GSIZE, -GSIZE);
	glTexCoord2f(0, 0);		glVertex2f(GSIZE, GSIZE);
	glTexCoord2f(1, 0);		glVertex2f(-GSIZE, GSIZE);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


}
void hand_update(){

}

void hand_init() {
	motionO = Vec2f(width / 2, height / 2);
	lefthand = new Texture("mickey_mouse_PNG39R.png");
	righthand = new Texture("mickey_mouse_PNG39L.png");
}