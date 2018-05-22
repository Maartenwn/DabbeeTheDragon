#pragma once
#include "DrawComponent.h"
#include <vector>
#include "Texture.h"
#include "TextureVertex.h"

using namespace std;
class SkyboxComponent :
	public DrawComponent
{
public:
	SkyboxComponent();
	~SkyboxComponent();
	void draw();
};

static Texture *textureSkybox;
static vector<TextureVertex> vertices;

