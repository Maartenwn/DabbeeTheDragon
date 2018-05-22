#pragma once

#include "Component.h"
#include "Vec.h"
#define FALLINGTIMER 7

class MoveToComponent : public Component
{
public:

	float mt_speedcounter = 1;	//used for fall animation
	float mt_speed = 0.008f;
	int	  mt_amountLeftToRotate = 45;

	Vec3f target;

	MoveToComponent();
	~MoveToComponent();

	virtual void update(float elapsedTime) override;
	void rotate(void);

};

