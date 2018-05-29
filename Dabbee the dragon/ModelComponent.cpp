#include "ModelComponent.h"
#include <vector>
#include "ObjModel.h"

using namespace std;

vector<ObjModel*> models;


static ObjModel* findModel(const string input) {
	for (ObjModel* model : models)
	{
		if (model->getName() == input) return model;
	}
}

void initModels() {
	//models.push_back(new ObjModel("models/steve/steve.obj"));
	models.push_back(new ObjModel("models/dragon/dragon_body.obj"));
	models.push_back(new ObjModel("models/dragon/wing.obj"));
}

ModelComponent::ModelComponent(const string nameModel)
{
	model = findModel(nameModel);
}

ModelComponent::~ModelComponent()
{
}

void ModelComponent::draw() {
	model->draw();
}

