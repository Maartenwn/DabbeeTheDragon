#include "MotionInput.h"

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/ocl.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace cv;
using namespace std;

Ptr<BackgroundSubtractor> pMOG2;

double dWidth, dHeight;
double sWidth;
Mat frame;

bool up, down, inFlappingMotion = false;
clock_t flapclock;

std::thread runThread;

cv::Point MotionInput::FirstPix(const Mat& input, bool left) {

	if (left) {
		for (int col = 0; col < input.size().width; col++)
		{
			for (int row = 0; row < input.size().height; row++)
			{
				if (input.at<uchar>(row, col) != 0) {
					return Point(row, col);
				}
			}
		}
	}
	else {
		for (int col = input.size().width - 1; col >= 0; col--)
		{
			for (int row = 0; row < input.size().height; row++)
			{
				if (input.at<uchar>(row, col) != 0) {
					return Point(row, col);
				}
			}
		}
	}

	return Point(-1, -1);
}

void MotionInput::LocateHands(const Mat& input, double dWidth, double dHeight) {
	Mat left = cv::Mat(input, cv::Rect(0, 0, (int)sWidth, (int)dHeight));
	Mat right = cv::Mat(input, cv::Rect((int)(dWidth - sWidth), 0, (int)sWidth, (int)dHeight));

	Point lp = FirstPix(left, true);
	Point rp = FirstPix(right, false);

	// y = hor, x = vert;
	rp.y += (int)(dWidth - sWidth);

	movementFun(lp, rp, Point(dWidth, dHeight));

	if (lp.x != -1 && lp.y != -1 && rp.x != -1 && rp.y != -1) {
		if (lp.x < (dHeight / 3) && rp.x < (dHeight / 3)) {
			up = true; inFlappingMotion = true;
			down = false;
		}
		else if (lp.x > dHeight - (dHeight / 3) && rp.x > dHeight - (dHeight / 3)) {
			up = false;
			down = true;
		}
		else {
			up = false;
			down = false;
		}

		if (up) {
			flapclock = clock();
		}

		if (down) {
			if (inFlappingMotion) {
				double diffticks = clock() - flapclock;
				double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);

				if (diffms > MAX_FLAP_SPEED)
					diffms = MAX_FLAP_SPEED;

				motionFun((MAX_FLAP_SPEED - diffms));

				inFlappingMotion = false;
			}
		}
	}

	cv::line(frame, Point(lp.y - 10, lp.x), Point(lp.y + 10, lp.x), Scalar(0, 255, 0), 2);
	cv::line(frame, Point(lp.y, lp.x - 10), Point(lp.y, lp.x + 10), Scalar(0, 255, 0), 2);

	cv::line(frame, Point(rp.y - 10, rp.x), Point(rp.y + 10, rp.x), Scalar(0, 255, 0), 2);
	cv::line(frame, Point(rp.y, rp.x - 10), Point(rp.y, rp.x + 10), Scalar(0, 255, 0), 2);

	cv::imshow("Body_Detect", frame);
}

MotionInput::MotionInput(onMotionReceived fun, onMovementMotionReceived fun2)
{
	motionFun = fun;
	movementFun = fun2;
}

void MotionInput::Run(cv::VideoCapture cap, cv::Mat out) {
	while (1)
	{
		bool bSuccess = cap.read(frame);

		flip(frame, frame, 1);

		if (!bSuccess)
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		pMOG2->apply(frame, out);

		cv::line(frame, Point((int)sWidth, 0), Point((int)sWidth, (int)dHeight), Scalar(0, 255, 0), 2);
		cv::line(frame, Point((int)(dWidth - sWidth), 0), Point((int)(dWidth - sWidth), (int)dHeight), Scalar(0, 255, 0), 2);

		Mat kernel = getStructuringElement(MORPH_RECT, Size((3 * 3) + 1, (3 * 3) + 1));

		Mat erodedImage, dilatedImage;
		erode(out, erodedImage, kernel);
		dilate(erodedImage, dilatedImage, kernel);

		LocateHands(dilatedImage, dWidth, dHeight);
	}

	runThread.join();
	cout << "Terminating motion input" << endl;
}


void MotionInput::Start(const int &cam)
{
	VideoCapture cap(cam);

	if (!cap.isOpened())
	{
		cout << "Cannot open the video cam" << endl;
		return;
	}

	dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	cout << "Frame size : " << dWidth << " x " << dHeight << endl;

	sWidth = (dWidth / 5) * 2;

	namedWindow("Body_Detect", CV_WINDOW_AUTOSIZE);

	pMOG2 = createBackgroundSubtractorMOG2();

	Mat fgMaskMOG2;
	runThread = thread(&MotionInput::Run, this, cap, fgMaskMOG2);
}

