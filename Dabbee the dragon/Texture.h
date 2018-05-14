#pragma once
#include <string>
#include <GL/freeglut.h>

	
using namespace std;
class Texture
{
public:
	Texture(std::string input);
	void bind();
	GLuint getId();
	int getWidth();
	int getHeigth();
private:
	GLuint id;
	int width;
	int height;
};

