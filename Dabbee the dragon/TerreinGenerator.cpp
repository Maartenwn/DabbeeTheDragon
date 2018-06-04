#include "TerreinGenerator.h"
#include "Texture.h"
#include "ObstacleComponent.h"
#include "ObjModel.h"
#include <iostream>
#include <windows.h>
#include <gl/GL.h>
#include "Vec.h"
#include <math.h>


#define FLOOR_STEP 5
#define FLOOR_WIDTH 50.0f
#define FLOOR_NOICE 4

using namespace std;

vector<ObjModel::ModelVertex> verts;
Texture* terreinTexture;

TerreinGenerator::TerreinGenerator()
{
	terreinTexture = new Texture("text/rock.png");
}

TerreinGenerator::~TerreinGenerator()
{
}

void TerreinGenerator::recalculateTerrein(const std::vector<GameObject*>& objs, bool clear)
{
	if (objs.empty())
		return;

	vector<hPoint> objPoints;

	vector<GameObject*> obstacleObjs;
	for (GameObject* obj : objs)
		if (obj->getComponent<ObstacleComponent>() != nullptr)
			obstacleObjs.push_back(obj);

	verts.clear();

	if (clear)
		points.clear();

	int n = 0;
	for (GameObject* obj : obstacleObjs) {
		if (n % 2 == 0) {
			hPoint p;
			p.y = obj->position.y;
			p.z = obj->position.z;
			objPoints.push_back(p);
		}
		n++;
	}



	for (int i = 1; i < objPoints.size(); i++) {

		float avgy = (objPoints.at(i).y - objPoints.at(i - 1).y) / (float)FLOOR_STEP;
		float avgz = (objPoints.at(i).z - objPoints.at(i - 1).z) / (float)FLOOR_STEP;


		float y = objPoints.at(i - 1).y;
		float z = objPoints.at(i - 1).z;

		for (int j = 0; j < FLOOR_STEP; j++) {
			if (j != 0) {
				z += avgz;
				y += avgy;
			}

			hPoint p;
			p.y = y + ((rand() % (FLOOR_NOICE - (-FLOOR_NOICE) + 1) - FLOOR_NOICE) / (float) 10.0f);
			p.z = z;

			points.push_back(p);
		}
	}

	//Duplicate upside down, mirrored vert

	float to = 12;
	float objModelOffset = -.3f;
	float xOffset = 2.6f;

	float prevCurve = (-pow((to * to) - pow(-FLOOR_WIDTH, 2), .5f) + to) + objModelOffset;
	bool topLight = true;
	float step = (FLOOR_WIDTH / 25.0f);
	for (int x = -FLOOR_WIDTH; x < FLOOR_WIDTH; x += step) {

		float curve = (-pow((to * to) - pow(x, 2), .5f) + to) + objModelOffset;
		for (int i = 1; i < points.size(); i++) {

			Vec3f a(x - xOffset, points.at(i).y + (prevCurve), points.at(i).z);
			Vec3f b(x - xOffset + step, points.at(i).y + (curve), points.at(i).z);
			Vec3f c(x - xOffset + step, points.at(i - 1).y + (curve), points.at(i - 1).z);
			Vec3f d(x - xOffset, points.at(i - 1).y + (prevCurve), points.at(i - 1).z);

			Vec3f n;
			if (topLight)
				n = (b - a).cross(c - a).normalize();
			else
				n = (c - a).cross(b - a).normalize();

			verts.push_back(
				ObjModel::ModelVertex{
					a.x, a.y, a.z,
					n.x, n.y, n.z,
					0, 0
			});

			verts.push_back(
				ObjModel::ModelVertex{
					b.x, b.y, b.z,
					n.x, n.y, n.z,
					1, 0
			});

			verts.push_back(
				ObjModel::ModelVertex{
					c.x, c.y, c.z,
					n.x, n.y, n.z,
					1, 1
			});

			// second
			verts.push_back(
				ObjModel::ModelVertex{
				a.x, a.y, a.z,
				n.x, n.y, n.z,
				0, 0
			});

			verts.push_back(
				ObjModel::ModelVertex{
				c.x, c.y, c.z,
				n.x, n.y, n.z,
				1, 1
			});

			verts.push_back(
				ObjModel::ModelVertex{
				d.x, d.y, d.z,
				n.x, n.y, n.z,
				0, 1
			});
		}
		prevCurve = curve;
	}
}

void TerreinGenerator::addTerreinBetweenObjs(const std::vector<GameObject*>& objs)
{
	recalculateTerrein(objs, false);
}

void TerreinGenerator::removeTerreinFromFront()
{
	if (points.empty())
		return;

	vector<hPoint>::const_iterator first = points.begin() + FLOOR_STEP;
	vector<hPoint>::const_iterator last = points.end();

	vector<hPoint> newp(first, last);

	points = newp;
}

void TerreinGenerator::draw(void)
{
	if (verts.empty())
		return;

	glEnable(GL_TEXTURE_2D);

	terreinTexture->bind();

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(ObjModel::ModelVertex), ((float*)verts.data()) + 0);
	glNormalPointer(GL_FLOAT, sizeof(ObjModel::ModelVertex), ((float*)verts.data()) + 3);
	glTexCoordPointer(2, GL_FLOAT, sizeof(ObjModel::ModelVertex), ((float*)verts.data()) + 6);

	glDrawArrays(GL_TRIANGLES, 0, verts.size());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

float TerreinGenerator::currentHeight(float z)
{
	float t = 1.1f;
	for (hPoint p : points) {
		if (p.z - t <= z && z < p.z + t) {
			return p.y;
		}
	}

	return -999.0f;
}
