#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <opencv2/opencv.hpp>
#include <math.h>
#include "GameObject.h"
#include "MoveToComponent.h"
#include "ObstacleComponent.h"
#include "ObstacleGenerator.h"
#include "CubeComponent.h"
#include "PlayerComponent.h"
#include "TimerComponent.h"


int height = 800;
int width = 1200;
GameObject* player;


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
	ZeroMemory(keys, sizeof(keys));
	ObstacleGenerator* obstacleGenerator = new ObstacleGenerator();
	for (int i = -10; i < 10; i++)
	{
		
		obstacleGenerator->getNextObstacle();
		GameObject* o = new GameObject();
		o->addComponent(obstacleGenerator->bottomObstacle);
		o->position = Vec3f(i * 10, 0, 0);
		objects.push_back(o);

		GameObject* o2 = new GameObject();
		o2->addComponent(obstacleGenerator->topObstacle);
		o2->position = Vec3f(i * 10, 0, 0);
		objects.push_back(o2);
	}

	

	{
		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(0.5));
		o->position = Vec3f(2, 0, 5);
		objects.push_back(o);
	}
	{
		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(0.5));
		o->position = Vec3f(-3, 0, 5);
		objects.push_back(o);
	}

	{
		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(0.5));
		o->addComponent(new PlayerComponent());
		o->addComponent(new TimerComponent());
		o->addComponent(new MoveToComponent());

		o->position = Vec3f(0, 0, 0);
		objects.push_back(o);

		player = o;
	}

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
	gluLookAt(player->position.x, player->position.y + 1, player->position.z + 0.125,
		player->position.x, player->position.y + 0.5, player->position.z + 1.5,
		0, 1, 0);


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

	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("Dabbe the dragon");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);

	//opengl init
	init();

	glutMainLoop();

	return 0;
}


