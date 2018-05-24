#pragma once

#define MAX_FLAP_SPEED 500
#include <opencv2/opencv.hpp>


class MotionInput {
public:
	typedef void(*onMotionReceived)(const double&);
	typedef void(*onMovementMotionReceived)(const cv::Point&, const cv::Point&, const cv::Point&);

	bool display;

	onMotionReceived motionFun;
	onMovementMotionReceived movementFun;
	MotionInput(onMotionReceived, onMovementMotionReceived);
	void Start(const int&, const bool&);
private:
	cv::Point FirstPix(const cv::Mat&, bool);
	void LocateHands(const cv::Mat&, double, double);
	void Run(cv::VideoCapture, cv::Mat);
};
