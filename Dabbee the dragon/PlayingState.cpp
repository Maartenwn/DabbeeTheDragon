#include <GL/freeglut.h>
#include  "PlayingState.h"
#include <iostream>
#include <string>
#include <opencv2\features2d\features2d.hpp>
#include "Debuginfo.h"
#include "MagicHands.h"
#include "Vec.h"
#include "Texture.h"
#include "Game.h"


bool debugon = false;
bool butreleased = true;
extern bool keys[256];
extern Vec3f cameraOffset;


extern cv::Point leftHandPoint, rightHandPoint;

bool hasFlapped;
float total_score;
bool isDead;

extern int width;
extern int height;

int imgWidth, imgHeight;

GLuint list_base;
int bpp;

static Texture* font;

PlayingState::PlayingState(GameStateManager* manager)
{
	this->playingGame = new Game(manager);
	this->manager = manager;
	font = new Texture("ExportedFont1.png");

	list_base = glGenLists(256);
	glEnable(GL_TEXTURE_2D);
	font->bind();
	for (int i = 0; i < 256; i++) {
		float cx = (float)(15 - i % 16) / 16.0f;
		float cy = (float)(i / 16) / 16.0f;

		float size = 1 / 16.0f;

		glNewList(list_base + 255 - i, GL_COMPILE);

		glBegin(GL_QUADS);

		glTexCoord2f(cx, cy);					glVertex2d(0, 1);	
		glTexCoord2f(cx, cy + size);			glVertex2i(0, 0);
		glTexCoord2f(cx + size, cy + size);		glVertex2i(1, 0);
		glTexCoord2f(cx + size, cy);			glVertex2i(1, 1);

		glEnd();
		glTranslated(1, 0, 0);
		glEndList();
	}
}


PlayingState::~PlayingState()
{
	total_score = 0;
	delete playingGame;
}

void PlayingState::drawScore()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);


	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();
	glScalef(50, 50, 50);
	font->bind();
	glListBase(list_base);
	string score = "Score: ";
	score += to_string((int) total_score);
	glCallLists(score.length(), GL_UNSIGNED_BYTE, score.c_str());
	glPopMatrix();


	if (isDead) {
		glPushMatrix();

		glListBase(list_base);
		string deathString = "Game over";
		glTranslated(width / 2 - 70 * (deathString.length() / 2), height / 2  - 70/2, 0);
		glScalef(70, 70, 70);
		glCallLists(deathString.length(), GL_UNSIGNED_BYTE, deathString.c_str());
		glPopMatrix();
	}

} 

void PlayingState::resize(int w, int h) {

}


void PlayingState::drawHUD()
{

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);
	glColor4f(1.0f, 1.0f, 1.0f,0.0f);
	hand_draw();

	glPushMatrix();
	glTranslatef(30, 40 ,0);	//translate and scale
	glScalef(.3f,-.3f,1);

	/*unsigned char scoreLabel[15] = " ";
	std::string s = "Score " + std::to_string((int)total_score);
	std::copy(s.begin(), s.end(), scoreLabel);
	glutStrokeString(GLUT_STROKE_ROMAN, scoreLabel);*/


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
	drawScore();

}

extern float flapspeed;

bool hasCollided;
float timeSinceDeath;
void PlayingState::update(float deltaTime)
{
	if (isDead) {
		timeSinceDeath += deltaTime;
		if (timeSinceDeath > 3) {
			manager->changeState(0);
		}
		return;
	}


	hand_update(deltaTime,false);
	if (flapspeed != 0.0 || keys[' ']) hasFlapped = true;
	if (hasFlapped) {
		total_score += playingGame->update(deltaTime);
	}
	if (hasCollided && !isDead) {
		isDead = true;
		timeSinceDeath = 0;
	}
	
	
}

void PlayingState::init()
{
	keys['s'] = false;
	hasFlapped = false;
	isDead = false;
	hasCollided = false;
	cameraOffset = { 0,0,0 };
	playingGame->init();
}

void PlayingState::deInit()
{
	debugon = false;
	butreleased = true;	
	playingGame->deInit();
	total_score = 0;
}