#include "MagicHands.h"
#include <GL/freeglut.h>
#include "Texture.h"
#include "vec.h"
#include "AudioPlayer.h"
#include <opencv2\features2d\features2d.hpp>
#include <math.h>
#include <iostream>
#define GSIZE 50
#define PI 3.14159265359

Vec2f motionO;

Texture* lefthand;
Texture* righthand;

float rotationR;
float rotationL;

extern bool keys[256];
extern cv::Point leftHandPoint, rightHandPoint;
cv::Point lhp, rhp;
extern int width, height;

double angle = 0;
float angleInPiesL;
float angleInPiesR;
int onLcircleDraw = 0;
int onRcircleDraw = 0;



void hand_drawLoadingcircle(float angleInPies, float r, float t) {
	glBegin(GL_QUAD_STRIP);
	for (float i = 0; i <= (angleInPies)* PI; i += 0.001f)
	{
		glVertex2f(r * sin(i), r * cos(i));
		glVertex2f((r - t) * sin(i), (r - t) * cos(i));
	}
	glEnd();
}

void hand_draw()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	lefthand->bind();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 0.5);//Replace this alpha for transparency

	glPushMatrix();
	glTranslatef(lhp.x, lhp.y, 0);
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
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);

	if (1 == onLcircleDraw) {
		glTranslatef(lhp.x, lhp.y, 0);
		glScalef(1, -1, 1);
		glColor3f(1.0f, 1.0f, 1.0f);
		hand_drawLoadingcircle(angleInPiesL, 71.6f, 30.0f);		//white circle
		glColor3f(0.0f, 0.0f, 0.0f);
		hand_drawLoadingcircle(angleInPiesL, 66.6f, 20.0f);		//black circle
	}
	if (1 == onRcircleDraw) {
		glTranslatef(rhp.x, rhp.y, 0);
		glScalef(1, -1, 1);
		glColor3f(1.0f, 1.0f, 1.0f);
		hand_drawLoadingcircle(angleInPiesR, 71.6f, 30.0f);		//white circle
		glColor3f(0.0f, 0.0f, 0.0f);
		hand_drawLoadingcircle(angleInPiesR, 66.6f, 20.0f);		//black circle
	}

	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void hand_update(float ellapesdTime, bool circle) {
	
	rotationL = atan2(lhp.y - motionO.y, lhp.x - motionO.x) * 180.0f / 3.1415f;
	rotationR = atan2(rhp.y - motionO.y, rhp.x - motionO.x) * 180.0f / 3.1415f;
	if (circle) {
		cout << angleInPiesL << endl;
		if (lhp.y > height - height / 6 && lhp.x < width / 2) {
			onLcircleDraw = 1; onRcircleDraw = 0;
			if (angleInPiesL == 0) {
				PlayChargingSound();
			}

			if (ellapesdTime < 1.0f) {
				angleInPiesR += 1.2f * ellapesdTime;
				angleInPiesL += 1.2f * ellapesdTime;
			}if (angleInPiesR > 2.2f) {
				angleInPiesR = 0;
				onRcircleDraw = 0;
				KillChargingSound();
				PlaySoundOnce("ButtonClick.wav");

				//do *plunk*
			}
			if (angleInPiesL > 2.2f) {
				angleInPiesL = 0;
				onLcircleDraw = 0;
				keys['s'] = true;
				KillChargingSound();
				PlaySoundOnce("ButtonClick.wav");

				//do *plunk*
			}
		
		} 	//lefthand presses somthing
			//if (rhp.y > height - height / 6 && rhp.x > width / 2) { onRcircleDraw = 1; onLcircleDraw = 0; } 	//lefthand presses somthing
		if (lhp.y < height - height / 6 || lhp.x > width / 2) { onLcircleDraw = 0; angleInPiesL = 0; KillChargingSound(); }		//lefthand release			
		//if (rhp.y < height - height / 6 || rhp.x < width / 2) { onRcircleDraw = 0; angleInPiesR = 0; }		//righthand release
	
	
	}
}

void hand_init() {
	angleInPiesL = 0;
	angleInPiesR = 0;
	motionO = Vec2f(width / 2, height / 2);
	lefthand = new Texture("mickey_mouse_PNG39R.png");
	righthand = new Texture("mickey_mouse_PNG39L.png");
	//Sleep(1000);
}