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

	TerreinGenerator();
	~TerreinGenerator();

	void recalculateTerrein(const std::vector<GameObject*>&, bool);
	void addTerreinBetweenObjs(const std::vector<GameObject*>&);
	void removeTerreinFromFront();
	void draw(void);

	float currentHeight(float);

private:
	vector<hPoint> points;
};