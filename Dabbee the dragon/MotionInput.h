#pragma once

#include <opencv2/opencv.hpp>

class MotionInput {
public:
	typedef void(*onMotionReceived)(const double&);

	onMotionReceived motionFun;
	MotionInput(onMotionReceived fun);
	void Start(const int&);
private:
	cv::Point FirstPix(const cv::Mat&, bool);
	void LocateHands(const cv::Mat&, double, double);
	void Run(cv::VideoCapture, cv::Mat);
};
