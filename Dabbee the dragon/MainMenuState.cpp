	#include "MainMenuState.h"
	#include "GameStateManager.h"
	#include "GL\glew.h"
	#include "GL\freeglut.h"
#include "stb_image.h"
#include "GLShader.h"

GLuint FramebufferName;
GLuint depthrenderbuffer;
GLuint renderedTexture;
GLuint blurredTexture;
GLuint program;
GLuint program2;

extern int width;
extern int height;
	

	MainMenuState::MainMenuState(GameStateManager* manager)
	{
		this->manager = manager;
		game = new PlayingState(manager);
		program = LoadShader("vertexBlurShader.txt", "fragmentBlurShader.txt");
		init();

	}

	MainMenuState::~MainMenuState()
	{
		deInit();
	}

	void MainMenuState::draw()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glViewport(0, 0, width, height);

		game->draw();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);
		glUseProgram(program);


		glClearColor(0.9f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_LIGHTING);
		glColor3f(1.0f, 1.0f, 1.0f);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glBindTexture(GL_TEXTURE_2D, renderedTexture);
		

		glBegin(GL_QUADS);  // front face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0);
		glEnd();
	}

	void MainMenuState::update(float deltaTime)
	{
		game->update(deltaTime);
	}

	void MainMenuState::init()
	{
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

		game->init();
	}

	void MainMenuState::deInit()
	{
		game->deInit();
	}
