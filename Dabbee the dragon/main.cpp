#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <opencv2/opencv.hpp>
#include <math.h>

#include "GameObject.h"
#include "MoveToComponent.h"
#include "ObstacleComponent.h"
#include "ObstacleGenerator.h"
#include "ModelComponent.h"
#include "CubeComponent.h"
#include "PlayerComponent.h"
#include "TimerComponent.h"
#include "MotionInput.h"
#include "SkyboxComponent.h"


int height = 800;
int width = 1200;
GameObject* player;
GameObject* skybox;

float flapspeed;
bool keys[256];

std::list<GameObject*> objects;

void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int  y)
{
	keys[key] = true;
	if (key == 27)
		exit(0);
}

void keyboardup(unsigned char key, int x, int y)
{
	keys[key] = false;
}


void init()
{
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	ZeroMemory(keys, sizeof(keys));
	GameObject *o = new GameObject();
	o->addComponent(new ModelComponent("models/steve/steve.obj"));
	o->addComponent(new PlayerComponent());
	o->addComponent(new TimerComponent());
	o->addComponent(new MoveToComponent());
	o->rotation = { 90,270,0 };
	objects.push_back(o);
	player = o;
	ObstacleGenerator* obstacleGenerator = new ObstacleGenerator();
	for (int i = 0; i < 10; i++)
	{
		
		obstacleGenerator->getNextObstacle();
		GameObject* o = new GameObject();
		o->addComponent(obstacleGenerator->bottomObstacle);
		o->position = Vec3f(0, 0, i * 5);
		objects.push_back(o);

		GameObject* o2 = new GameObject();
		o2->addComponent(obstacleGenerator->topObstacle);
		o2->position = Vec3f(0, 0, i * 5);
		objects.push_back(o2);
	}

	skybox = new GameObject();
	skybox->addComponent(new SkyboxComponent());

}

void display()
{

	glClearColor(0.9f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, width / (float)height, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(player->position.x , player->position.y + 2, player->position.z - 3,
		player->position.x, player->position.y + 0.5, player->position.z,
		0, 1, 0);


	glPushMatrix();
	//GLfloat diffuse[] = { 1, 1, 1, 1 };
	//glLightfv(GL_LIGHT0, GL_POSITION, diffuse);
	glTranslatef(-5,0,0);
	GLfloat pos[] = { 0, 0, 1, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	skybox->draw();
	
	glEnable(GL_LIGHT0);


	for (auto &o : objects)
		o->draw();



	glutSwapBuffers();
}


int lastTime = 0;
void idle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	


	for (auto &o : objects)
		o->update(deltaTime);

	skybox->position = { player->position.x - 0.5f, player->position.y + 1.5f,
		player->position.z - 2.5f };

	glutPostRedisplay();
}

void motion(const double& speed) {
	flapspeed = speed;
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("Dabbee the dragon");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);

	//opengl init
	initModels();
	init();

	//Init motion
	MotionInput m(&motion);
	m.Start(0);

	glutMainLoop();

	return 0;
}


