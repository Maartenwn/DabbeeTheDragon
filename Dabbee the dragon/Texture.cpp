#include "Texture.h"
#include "stb_image.h"


Texture::Texture(std::string input){
	//texures
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	int bbp;
	stbi_set_flip_vertically_on_load(TRUE);
	const char* inputChar = input.c_str();
	stbi_uc* imgData = stbi_load(inputChar, &width, &height, &bbp, 4);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		imgData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}

GLuint Texture::getId() {
	return id;
}
int Texture::getWidth() {
	return width;
}
int Texture::getHeigth() {
	return height;
}