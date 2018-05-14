#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <opencv2/opencv.hpp>
#include <math.h>
#include "GameObject.h"
#include "MoveToComponent.h"

int height = 800;
int width = 1200;


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
	gluLookAt(0, -5, 5,
		0, 0, 0,
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


