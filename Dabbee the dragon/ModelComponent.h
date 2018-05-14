#pragma once
#include "ObjModel.h"
#include "DrawComponent.h"

#ifndef HMODELCOMPONENT
#define HMODELCOMPONENT

class ModelComponent : public DrawComponent
{
public:
	ModelComponent(const string filenameAndDir);
	~ModelComponent();
	void draw();
private :
	ObjModel *model;
};

#endif // !HMODELCOMPONENT




void initModels();
	