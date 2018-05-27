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

GameObject* player;
GameObject* skybox;

ObstacleGenerator* obstacleGenerator;

Vec3f fpsCamOff = Vec3f(0,0,0);
Vec3f cameraOffset = Vec3f(0,0,0);
std::list<GameObject*> objects;
bool debugon = false;
bool butreleased = true;
extern bool keys[256];
extern int width;
extern int height;

extern cv::Point leftHandPoint, rightHandPoint;
cv::Point lhp, rhp;

float total_score;

static void addObstacle(void) {
	float position = obstacleGenerator->getNextObstacle();
	GameObject* o = new GameObject();
	o->addComponent(obstacleGenerator->bottomObstacle);
	auto collision = new CollisionComponent();

	vector<Cube*> hitboxes;
	ObstacleComponent* obstacle = o->getComponent<ObstacleComponent>();
	hitboxes.push_back(new Cube(o->position, { obstacle->width + 0.01f,obstacle->height + 0.01f,obstacle->depth + 0.01f }));
	collision->updateHitboxes(hitboxes);
	o->addComponent(collision);
	o->position = Vec3f(-obstacle->width / 2, obstacle->gapY, position);

	objects.push_back(o);

	GameObject* o2 = new GameObject();
	o2->addComponent(obstacleGenerator->topObstacle);

	vector<Cube*> hitboxes2;
	ObstacleComponent* obstacle2 = o2->getComponent<ObstacleComponent>();
	hitboxes2.push_back(new Cube(o2->position, { obstacle2->width + 0.01f,obstacle2->height + 0.01f,obstacle2->depth + 0.01f }));
	collision->updateHitboxes(hitboxes2);
	o2->addComponent(collision);
	o2->position = Vec3f(-obstacle2->width / 2, obstacle2->gapY, position);

	objects.push_back(o2);
}


PlayingState::PlayingState(GameStateManager* manager)
{
	this->manager = manager;
}


PlayingState::~PlayingState()
{
	total_score = 0;
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
	glClearColor(0.9f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, width / (float)height, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*gluLookAt(-10, player->position.y, player->position.z,
	0, player->position.y, player->position.z,
	0, 1, 0);*/

	gluLookAt(player->position.x + cameraOffset.x, player->position.y + 1 + cameraOffset.y, player->position.z - 3 + cameraOffset.z,
		player->position.x + fpsCamOff.x, player->position.y + 0.5 + fpsCamOff.y, player->position.z + fpsCamOff.z,
		0, 1, 0);


	glPushMatrix();
	GLfloat diffuse[] = { 1, 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, diffuse);
	glTranslatef(player->position.x - 3, player->position.y + 1, player->position.z);
	GLfloat pos[] = { 1, 0, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	skybox->draw();

	glEnable(GL_LIGHT0);

	std::list<GameObject*> removableObjects;
	for (auto &o : objects) {
		if (o->getComponent<ObstacleComponent>() != nullptr) {
			if (o->position.z < player->position.z - 1) {
				total_score+=.5f;
				removableObjects.push_back(o);
				continue;
			}
		}
		o->draw();
	}

	if (removableObjects.size() > 0) {
		for (auto &o : removableObjects)
			objects.remove(o);

		addObstacle();
	}

	drawHUD();

	glutSwapBuffers();
}

void PlayingState::update(float deltaTime)
{
	for (auto &o : objects)
		o->update(deltaTime);

	auto collision = player->getComponent<CollisionComponent>();
	if (collision->checkCollision(objects)) {
		manager->changeState(1);
	}

	//sets the skybox to the player pos
	skybox->position = { player->position.x - 0.5f + cameraOffset.x, player->position.y + .5f + cameraOffset.y,
		player->position.z - 2.5f + cameraOffset.z};

	glutPostRedisplay();
}

void PlayingState::init()
{
	obstacleGenerator = new ObstacleGenerator();
	glEnable(GL_DEPTH_TEST);
	GameObject *o = new GameObject();
	o->addComponent(new PlayerComponent());
	o->addComponent(new TimerComponent());
	o->addComponent(new DiveComponent());
	o->addComponent(new MoveToComponent());
	o->addComponent(new ModelComponent("models/steve/steve.obj"));
	auto collision = new CollisionComponent();
	vector<Cube*> cubes;
	cubes.push_back(new Cube({ -0.35f,-0.5,1.5 }, { 0.7f,0.7f,0.7f }));
	collision->updateHitboxes(cubes);
	o->addComponent(collision);
	o->rotation = { 90,270,0 };
	o->position.z = -10;
	objects.push_back(o);
	player = o;

	for (int i = 0; i < 5; i++)
		addObstacle();

	skybox = new GameObject();
	skybox->addComponent(new SkyboxComponent());

	
}

void PlayingState::deInit()
{
	objects.clear();
	delete skybox;
	delete obstacleGenerator;

	total_score = 0;
}

