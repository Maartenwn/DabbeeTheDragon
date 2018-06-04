#pragma once

#include <opencv2\features2d\features2d.hpp>
#include "Component.h"

class PointToHandComponent : public Component {
private:
	cv::Point clhp, crhp;
public:
	
	bool leftHand;

	PointToHandComponent(bool);
	~PointToHandComponent();

	virtual void update(float elapsedTime) override;

};