#include "PointToHandComponent.h"
#include "GameObject.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

extern cv::Point leftHandPoint, rightHandPoint;


extern int width;
extern int height;

PointToHandComponent::PointToHandComponent(bool isLeft)
{
	leftHand = isLeft;
}

PointToHandComponent::~PointToHandComponent()
{
}

void PointToHandComponent::update(float elapsedTime)
{
	float x = width / 2;
	float y = height / 2;

	if (leftHandPoint.x != -1)
		clhp = leftHandPoint;

	if (rightHandPoint.x != -1)
		crhp = rightHandPoint;

	if (leftHand) {
		float disx = clhp.x - x;
		float disy = clhp.y - y;
		float angle = (atan2(disy, disx)) * 180 / M_PI;

		gameObject->rotation.z = angle - 180;
	}
	else {
		float disx = crhp.x - x;
		float disy = crhp.y - y;
		float angle = (atan2(disx, disy)) * 180 / M_PI;

		gameObject->rotation.z = angle - 90;
	}

}
