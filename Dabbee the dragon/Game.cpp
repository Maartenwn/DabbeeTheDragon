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
#include "TerreinGenerator.h"
#include <time.h>


GameObject* player;
GameObject* skybox;

ObstacleGenerator* obstacleGenerator;

TerreinGenerator* tg;

Vec3f fpsCamOff;
Vec3f cameraOffset;
std::list<GameObject*> objects;


extern int width;
extern int height;
extern bool keys[256];


static void addObstacle(void) {
	float position = obstacleGenerator->getNextObstacle();
	GameObject* o = new GameObject();
	o->addComponent(new ModelComponent("models/TestRoper/crystal.obj"));
	o->addComponent(obstacleGenerator->bottomObstacle);
	auto collision = new CollisionComponent();

	vector<Cube*> hitboxes;
	ObstacleComponent* obstacle = o->getComponent<ObstacleComponent>();

	o->position = Vec3f(0, obstacle->gapY, position);
	o->rotation = { -90,0,(float)(rand() % 360) };
	o->scale = { 0.4f, 0.4f, 0.4f };

	hitboxes.push_back(new Cube({-obstacle->width / 2,0,-obstacle->depth/2}, { obstacle->width + 0.01f,obstacle->height + 0.01f,obstacle->depth + 0.01f }));
	collision->updateHitboxes(hitboxes);
	o->addComponent(collision);

	objects.push_back(o);

	GameObject* o2 = new GameObject();
	o2->addComponent(new ModelComponent("models/TestRoper/crystal.obj"));
	o2->addComponent(obstacleGenerator->topObstacle);
	auto collision2 = new CollisionComponent();


	vector<Cube*> hitboxes2;
	ObstacleComponent* obstacle2 = o2->getComponent<ObstacleComponent>();
	hitboxes2.push_back(new Cube({ -obstacle2->width / 2, -obstacle2->height,-obstacle2->depth / 2 }, { obstacle2->width + 0.01f,obstacle2->height + 0.01f,obstacle2->depth + 0.01f }));
	collision2->updateHitboxes(hitboxes2);
	o2->addComponent(collision2);
	o2->position = Vec3f(0, obstacle2->gapY + obstacle2->height, position);
	o2->rotation = { 90,0,0 };
	o2->scale = { 0.4f, 0.4f, 0.4f };
	objects.push_back(o2);
}

Game::Game(GameStateManager* manager)
{
	this->manager = manager;
	srand(time(NULL));
}


Game::~Game()
{
}

void Game::draw() {
	glClearColor(0.9f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, width / (float)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_FOG);

	float fogColor[3] = { 0.8f,0.8f,0.8f };
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 2.f);
	glFogf(GL_FOG_END, 40.f);
	glFogf(GL_FOG_DENSITY, 5.f);


	/*gluLookAt(-10, player->position.y, player->position.z,
	0, player->position.y, player->position.z,
	0, 1, 0);*/

	gluLookAt(player->position.x + cameraOffset.x, player->position.y + 1 + cameraOffset.y, player->position.z - 3 + cameraOffset.z,
		player->position.x + fpsCamOff.x, player->position.y + 0.5 + fpsCamOff.y, player->position.z + fpsCamOff.z,
		0, 1, 0);

	glPushMatrix();
	GLfloat diffuse[] = { 1, 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, diffuse);
	glTranslatef(player->position.x - 5, player->position.y + 5, player->position.z - 3);
	GLfloat pos[] = { 0, 0, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	skybox->draw();

	glEnable(GL_LIGHT0);

	tg->draw();

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
	for (auto &o : objects) {
		o->update(deltaTime);
	}

	auto collision = player->getComponent<CollisionComponent>();
	if (collision->checkCollision(objects)) {
		hasCollided = true;
	}
	else hasCollided = false;

	//if (player->position.y <= tg->currentHeight(player->position.z)) {
//		hasCollided = true;
//	}
	
	std::list<GameObject*> removableObjects;
	for (auto &o : objects) {
		if (o->getComponent<ObstacleComponent>() != nullptr) {
			if (o->position.z < player->position.z - 6) {

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

		
		std::vector<GameObject*> vobjs{ std::begin(objects), std::end(objects) };
		std::vector<GameObject*> v;

		v.push_back(vobjs.at(vobjs.size() - 4));
		v.push_back(vobjs.at(vobjs.size() - 3));
		v.push_back(vobjs.at(vobjs.size() - 2));
		v.push_back(vobjs.at(vobjs.size() - 1));


		tg->addTerreinBetweenObjs(v);
		tg->removeTerreinFromFront();
	}


	//sets the skybox to the player pos
	skybox->position = { player->position.x - 0.5f + cameraOffset.x, player->position.y + .5f + cameraOffset.y,
		player->position.z - 2.5f + cameraOffset.z };
	return point;
}
void Game::init() {
	obstacleGenerator = new ObstacleGenerator();
	tg = new TerreinGenerator();

	glEnable(GL_DEPTH_TEST);
	GameObject *o = new GameObject();
	o->scale = { .04f, .04f, .04f };
	o->addComponent(new PlayerComponent());
	o->addComponent(new TimerComponent());
	o->addComponent(new DiveComponent());
	o->addComponent(new MoveToComponent());
	o->addComponent(new ModelComponent("models/dragon/dragon_body.obj"));
	auto collision = new CollisionComponent();
	vector<Cube*> cubes;
	cubes.push_back(new Cube({ -0.35f,-0.8f,1.5 }, { 0.7f, 0.4f,0.7f }));
	collision->updateHitboxes(cubes);
	o->addComponent(collision);
	o->position.z = -10;
	o->position.y = 0;
	objects.push_back(o);
	player = o;

	GameObject *lw = new GameObject();
	lw->addComponent(new FollowComponent(o, { 0, .55f, 0 }));
	lw->addComponent(new PointToHandComponent(true));
	lw->addComponent(new ModelComponent("models/dragon/n_wing.obj"));
	lw->scale = { .04f, .04f, .04f };
	lw->position.x = 0;
	lw->position.z = -10;
	lw->position.y = .55f;
	GameObject *rw = new GameObject();

	rw->addComponent(new FollowComponent(o, { .01f, .55f, 0 }));
	rw->addComponent(new PointToHandComponent(false));
	rw->addComponent(new ModelComponent("models/dragon/n_wing.obj"));
	rw->scale = { -.04f, .04f, .04f };
	rw->position.x = .01f;
	rw->position.y = .55f;
	rw->position.z = -10;
	objects.push_back(rw);
	objects.push_back(lw);


	for (int i = 0; i < 20;i++)
		addObstacle();

	vector<GameObject*> obstacleObjs;
	for (GameObject* obj : objects)
		if (obj->getComponent<ObstacleComponent>() != nullptr)
			obstacleObjs.push_back(obj);

	tg->addTerreinBetweenObjs(obstacleObjs);

	
	skybox = new GameObject();
	skybox->addComponent(new SkyboxComponent());

	//sets the skybox to the player pos
	skybox->position = { player->position.x - 0.5f + cameraOffset.x, player->position.y + .5f + cameraOffset.y,
		player->position.z - 2.5f + cameraOffset.z };

}
void Game::deInit() {
	//delete player;
	delete skybox;
	delete obstacleGenerator;
	delete tg;


	for (auto it = objects.begin();it != objects.end();) {
		GameObject* toBeDeleted = *it;
		it = objects.erase(it);
		delete toBeDeleted;
	}
}
