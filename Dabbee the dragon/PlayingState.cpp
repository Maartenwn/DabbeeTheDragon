#include <GL/freeglut.h>
#include "stb_image.h"
#include <math.h>
#include "GameObject.h"
#include "MoveToComponent.h"
#include "ObstacleComponent.h"
#include "ObstacleGenerator.h"
#include "ModelComponent.h"
#include "CubeComponent.h"
#include "PlayerComponent.h"
#include "TimerComponent.h"
#include "SkyboxComponent.h"
#include "DiveComponent.h"
#include "CollisionComponent.h"
#include  "PlayingState.h"
#include <iostream>
#include <string>
#include <opencv2\features2d\features2d.hpp>
#include "Debuginfo.h"

#include "Game.h"


bool debugon = false;
bool butreleased = true;
extern bool keys[256];
extern Vec3f cameraOffset;


extern cv::Point leftHandPoint, rightHandPoint;
cv::Point lhp, rhp;

bool hasFlapped;
float total_score;


extern int width;
extern int height;




PlayingState::PlayingState(GameStateManager* manager)
{
	this->playingGame = new Game(manager);
	this->manager = manager;
}


PlayingState::~PlayingState()
{
	total_score = 0;
	delete playingGame;
}

void PlayingState::resize(int w, int h) {

}


void PlayingState::drawHUD()
{
	float gsize = 10;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);

	if (leftHandPoint.x != -1)
		lhp = leftHandPoint;

	glVertex2f(lhp.x - gsize, lhp.y - gsize);
	glVertex2f(lhp.x + gsize, lhp.y - gsize);
	glVertex2f(lhp.x + gsize, lhp.y + gsize);
	glVertex2f(lhp.x - gsize, lhp.y + gsize);

	glVertex2f(20, 40);
	glVertex2f(40,40);
	glVertex2f(40,80);
	glVertex2f(20,80);

	if (rightHandPoint.x != -1)
		rhp = rightHandPoint;

	glVertex2f(rhp.x - gsize, rhp.y - gsize);
	glVertex2f(rhp.x + gsize, rhp.y - gsize);
	glVertex2f(rhp.x + gsize, rhp.y + gsize);
	glVertex2f(rhp.x - gsize, rhp.y + gsize);

	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPushMatrix();
	glTranslatef(30, 40 ,0);	//translate and scale
	glScalef(.3f,-.3f,1);

	unsigned char scoreLabel[15] = " ";
	std::string s = "Score " + std::to_string((int)total_score);
	std::copy(s.begin(), s.end(), scoreLabel);
	glutStrokeString(GLUT_STROKE_ROMAN, scoreLabel);


	glTranslatef(-30, -40, 0);
	glScalef(1/.3f, 1/-.3f, 1);	//back to O

	if (butreleased) {
		bool dab = false;
		dab ^= keys['d'] && keys['a'] && keys['b'];
		if (dab) {
			debugon = debugon ^ dab;
			butreleased = false;
		}
	}
	if (!(keys['d'] && keys['a'] && keys['b'])) { butreleased = true; }
    draw_debug_display(debugon);
	
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void PlayingState::draw()
{
	playingGame->draw();
	drawHUD();
}

extern float flapspeed;

bool hasCollided;

void PlayingState::update(float deltaTime)
{
	if (flapspeed != 0.0 || keys[' ']) hasFlapped = true;
	if (hasFlapped) {
		total_score += playingGame->update(deltaTime);
	}
	if (hasCollided) {
		manager->changeState(0);
	}

}

void PlayingState::init()
{
	hasFlapped = false;
	hasCollided = false;
	cameraOffset = { 0,0,0 };
	playingGame->init();

}

void PlayingState::deInit()
{
	playingGame->deInit();
	total_score = 0;
}