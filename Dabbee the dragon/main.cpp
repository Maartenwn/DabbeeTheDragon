#include <GL/freeglut.h>
#include "GameStateManager.h"
#include "ModelComponent.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "MotionInput.h"

int height = 800;
int width = 1200;

float flapspeed;
bool keys[256];
GameStateManager* manager;

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


void display()
{
	manager->draw();
}


int lastTime = 0;
void idle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
	manager->update(deltaTime);
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
	ZeroMemory(keys, sizeof(keys));
	//Init motion
	MotionInput m(&motion);
	m.Start(0);

	manager = new GameStateManager();

	glutMainLoop();
	return 0;
}


