#include "SkyboxComponent.h"



SkyboxComponent::SkyboxComponent()
{
	if (textureSkybox == NULL)	textureSkybox = new Texture("skybox.jpg");

	if (vertices.empty()) {
		//front
		vertices.push_back(TextureVertex{ 0,0,0, 0,0,-1, 0.25f,1.0f / 3.0f }); //middle bl
		vertices.push_back(TextureVertex{ 0,1,0, 0,0,-1, 0.25f,2 * (1.0f / 3.0f) }); //middle tl
		vertices.push_back(TextureVertex{ 1,1,0, 0,0,-1, 0.5f,2 * (1.0f / 3.0f) }); //middle tr
		vertices.push_back(TextureVertex{ 1,0,0, 0,0,-1, 0.5f ,1.0f / 3.0f }); //middle br


																			   //back
		vertices.push_back(TextureVertex{ 1,0,-1, 0,0,1, 0.75, (1.0f / 3.0f) }); //lb
		vertices.push_back(TextureVertex{ 0,0,-1, 0,0,1, 1,  (1.0f / 3.0f) });
		vertices.push_back(TextureVertex{ 0,1,-1, 0,0,1, 1,2 * (1.0f / 3.0f) });
		vertices.push_back(TextureVertex{ 1,1,-1, 0,0,1, 0.75, 2 * (1.0f / 3.0f) });

		//bottem
		vertices.push_back(TextureVertex{ 0,0,0, 0,-1,0,	0.25f,1.0f / 3.0f });
		vertices.push_back(TextureVertex{ 0,0,-1,0,-1,0,	0.25f,0 });
		vertices.push_back(TextureVertex{ 1,0,-1,0,-1,0,	0.5f,0 });
		vertices.push_back(TextureVertex{ 1,0,0, 0,-1,0,	0.5f,1.0f / 3.0f });


		//top
		vertices.push_back(TextureVertex{ 0,1,0, 0,1,0, 0.25f,2 * (1.0f / 3.0f) }); //bl
		vertices.push_back(TextureVertex{ 0,1,-1,0,1,0, 0.25f,1 }); //tl
		vertices.push_back(TextureVertex{ 1,1,-1,0,1,0, 0.5f,1 }); //tr
		vertices.push_back(TextureVertex{ 1,1,0, 0,1,0, 0.5f,2 * (1.0f / 3.0f) }); //br


																				   //left
		vertices.push_back(TextureVertex{ 0,0,-1,		-1,0,0,		0,  (1.0f / 3.0f) });
		vertices.push_back(TextureVertex{ 0,0,0,		-1,0,0,		0.25f,  (1.0f / 3.0f) });
		vertices.push_back(TextureVertex{ 0,1,0,		-1,0,0,		0.25f , 2 * (1.0f / 3.0f) });
		vertices.push_back(TextureVertex{ 0,1,-1,		-1,0,0,		0, 2 * (1.0f / 3.0f) });

		//right
		vertices.push_back(TextureVertex{ 1,0,0,		1,0,0,		0.5f,  (1.0f / 3.0f) });
		vertices.push_back(TextureVertex{ 1,0,-1,		1,0,0,		0.75f,(1.0f / 3.0f) });
		vertices.push_back(TextureVertex{ 1,1,-1,		1,0,0,		0.75f,2 * (1.0f / 3.0f) });
		vertices.push_back(TextureVertex{ 1,1,0,		1,0,0,		0.5f,2 * (1.0f / 3.0f) });
	}
}


SkyboxComponent::~SkyboxComponent()
{
}

void SkyboxComponent::draw() {
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	//glutSolidCube(1);
	glEnable(GL_TEXTURE_2D);
	textureSkybox->bind();
	//glShadeModel(GL_SMOOTH);
	//glutSolidTeapot(2);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(TextureVertex), ((float*)vertices.data()) + 0);
	glNormalPointer(GL_FLOAT, sizeof(TextureVertex), ((float*)vertices.data()) + 3);
	glTexCoordPointer(2, GL_FLOAT, sizeof(TextureVertex), ((float*)vertices.data()) + 6);
	glDrawArrays(GL_QUADS, 0, vertices.size());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

