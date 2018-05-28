#include "Game.h"
#include <GL/freeglut.h>
#include "GameObject.h"
#include "ObstacleGenerator.h"
#include "Cube.h"
#include "CollisionComponent.h"
#include "MoveToComponent.h"
#include "ObstacleComponent.h"
#include "ObstacleGenerator.h"
#include "ModelComponent.h"
#include "CubeComponent.h"
#include "PlayerComponent.h"
#include "TimerComponent.h"
#include "SkyboxComponent.h"
#include "DiveComponent.h"
#include "FollowComponent.h"
#include "PointToHandComponent.h"

GameObject* player;
GameObject* skybox;

ObstacleGenerator* obstacleGenerator;

Vec3f fpsCamOff;
Vec3f cameraOffset;
std::list<GameObject*> objects;


extern int width;
extern int height;
extern bool keys[256];


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

Game::Game(GameStateManager* manager)
{
	this->manager = manager;
}


Game::~Game()
{
}

void Game::draw() {
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

	for (auto &o : objects) {
		o->draw();
	}

}

extern bool hasCollided;


void Game::autoInput() {
	if (player->position.z < 10) keys[' '] = true;
	for (auto &o : objects) {
		if (o->getComponent<ObstacleComponent>() != nullptr) {
			if (o->position.z > player->position.z  && o->position.z < player->position.z + 8) {
				if (player->position.y < o->position.y - 5) {
					keys[' '] = true;
				}
				else keys[' '] = false;
			}
		}
	}
}

float Game::update(float deltaTime) {
	float point = 0;
	for (auto &o : objects)
		o->update(deltaTime);

	auto collision = player->getComponent<CollisionComponent>();
	if (collision->checkCollision(objects)) {
		hasCollided = true;
	}
	else hasCollided = false;

	std::list<GameObject*> removableObjects;
	for (auto &o : objects) {
		if (o->getComponent<ObstacleComponent>() != nullptr) {
			if (o->position.z < player->position.z - 2) {

				point += .5f;
				removableObjects.push_back(o);
				continue;
			}
		}
	}

	if (removableObjects.size() > 0) {
		for (auto &o : removableObjects)
			objects.remove(o);
		addObstacle();
	}


	//sets the skybox to the player pos
	skybox->position = { player->position.x - 0.5f + cameraOffset.x, player->position.y + .5f + cameraOffset.y,
		player->position.z - 2.5f + cameraOffset.z };
	return point;
}
void Game::init() {
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

	/*GameObject *lw = new GameObject();
	lw->addComponent(new FollowComponent(o, { 0, .55f, 0 }));
	lw->addComponent(new PointToHandComponent(true));
	lw->addComponent(new ModelComponent("models/dragon/wing.obj"));
	lw->scale = { .04f, .04f, .04f };
	lw->position.x = 0;
	lw->position.z = -10;
	lw->position.y = .55f;
	GameObject *rw = new GameObject();

	rw->addComponent(new FollowComponent(o, { .01f, .55f, 0 }));
	rw->addComponent(new PointToHandComponent(false));
	rw->addComponent(new ModelComponent("models/dragon/wing.obj"));
	rw->scale = { -.04f, .04f, .04f };
	rw->position.x = .01f;
	rw->position.y = .55f;
	rw->position.z = -10;
	objects.push_back(rw);
	objects.push_back(lw);*/


	for (int i = 0; i < 5; i++)
		addObstacle();

	skybox = new GameObject();
	skybox->addComponent(new SkyboxComponent());

	//sets the skybox to the player pos
	skybox->position = { player->position.x - 0.5f + cameraOffset.x, player->position.y + .5f + cameraOffset.y,
		player->position.z - 2.5f + cameraOffset.z };

}
void Game::deInit() {
	objects.clear();
	delete skybox;
	delete obstacleGenerator;
}
