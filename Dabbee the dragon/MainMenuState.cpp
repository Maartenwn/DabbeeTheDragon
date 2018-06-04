#include "MainMenuState.h"
#include "GameStateManager.h"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "stb_image.h"
#include "GLShader.h"
#include "Texture.h"
#include "Vec.h"
#include "MagicHands.h"
#include <time.h>

GLuint FramebufferName;
GLuint depthrenderbuffer;
GLuint renderedTexture;
GLuint program;
Texture *logo;


extern int width;
extern int height;

extern Vec3f cameraOffset;

extern bool keys[256];

static void generateRenderTexture() {
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// The texture we're going to render to
	glGenTextures(1, &renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" means "empty" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Poor filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// The depth buffer
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);


	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

								   // Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		cout << "Error" << endl;
	}
}


MainMenuState::MainMenuState(GameStateManager* manager)
{
	this->manager = manager;
	game = new Game(manager);
	program = LoadShader("vertexBlurShader.txt", "fragmentBlurShader.txt");
}

MainMenuState::~MainMenuState()
{
	deInit();
}

void MainMenuState::resize(int w, int h) {
	glDeleteFramebuffers(1, &FramebufferName);
	glDeleteTextures(1, &renderedTexture);
	glDeleteBuffers(1, &depthrenderbuffer);
	generateRenderTexture();
}

void MainMenuState::draw()
{

	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glViewport(0, 0, width, height);

	glPushMatrix();
	game->draw();

	glPopMatrix();


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width, height);


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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1.0f, 1.0f, 1.0f);
	

	glUseProgram(program);

	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glBegin(GL_QUADS);  // front face
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0, height);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(width, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(width, height);
	glEnd();


	glUseProgram(0);

	logo->bind();
	glBegin(GL_QUADS);  // front face
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0, height);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(width, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(width, height);
	glEnd();

	hand_draw();


	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
}

extern bool hasCollided;
float updateTime;

void MainMenuState::update(float deltaTime)
{
	hand_update();
	game->autoInput();


	game->update(deltaTime);
	/*if (hasCollided) {
		game->deInit();
		game->init();
	}*/

	if (keys['s']) {
		manager->changeState(1);
	}
}

void MainMenuState::init()
{
	updateTime = 0;
	srand(time(NULL));
	generateRenderTexture();
	logo = new Texture("mainmenu.png");
	cameraOffset = { -4, 0, -1 };
	game->init();
}

void MainMenuState::deInit()
{
	delete logo;
	game->deInit();
}
