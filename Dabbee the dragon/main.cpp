#include "GL\glew.h"
#include <GL/freeglut.h>
#include "GameStateManager.h"
#include "ModelComponent.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "MotionInput.h"
#include "AudioPlayer.h"
#define FPSFIELD 20
int height = 800;
int width = 1200;
float fpsTime = 0;
int frameCounter = 0;

int FPS;
float flapspeed;
cv::Point leftHandPoint, rightHandPoint;
bool keys[256];
GameStateManager* manager;

void reshape(int w, int h)
{
	width = w;
	height = h;
	manager->resize(w, h);
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
	glutSwapBuffers();
}

int lastTime = 0;
void idle()
{

	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	fpsTime += deltaTime;
	if (fpsTime >= .5f) {	//one second passed
		FPS = frameCounter / fpsTime;
		fpsTime = 0;
		frameCounter = 0;
	}
	frameCounter++;
	lastTime = currentTime;
	manager->update(deltaTime);
	glutPostRedisplay();
}

void motion(const double& speed) {
	flapspeed = speed;
}

void movement(const cv::Point& lp, const cv::Point& rp, const cv::Point& mp) {
	leftHandPoint = cv::Point((lp.x / (float)mp.x) * width, (lp.y / (float)mp.y) * height);
	rightHandPoint = cv::Point((rp.x / (float)mp.x) * width, (rp.y / (float)mp.y) * height);
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("Dabbee the dragon");
	glutSetIconTitle("icon1.ico");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	GLenum error = glewInit();
	if (GLEW_OK != error) {
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
	}

	//opengl init

	initModels();
	ZeroMemory(keys, sizeof(keys));
	//Init motion
	MotionInput m(&motion, &movement);
	m.Start(0, false);


	manager = new GameStateManager();
	InitAudioPlayer();
	PlaySoundInloop("DesiJourney.wav");
	glutSetIconTitle("icon1.ico");

	glutMainLoop();

	return 0;
}


