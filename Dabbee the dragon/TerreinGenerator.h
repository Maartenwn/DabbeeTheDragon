#pragma once

#include <vector>
#include "GameObject.h"
#include <opencv2\features2d\features2d.hpp>
#include "Texture.h"

class TerreinGenerator {

public:

	struct hPoint {
		float y;
		float z;
	};

	std::vector<hPoint> points;

	TerreinGenerator();
	~TerreinGenerator();

	void recalculateTerrein(const std::vector<GameObject*>&);
	void draw(void);

};