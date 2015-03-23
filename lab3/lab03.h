/*--------------------------------------------------------------------------------------------*\
CSI 4133 Computer methods for picture processing and analysis
Winter, 2015
\*--------------------------------------------------------------------------------------------*/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#if !defined LAB3
#define LAB3

using namespace std;
using namespace cv;

class lab03
{
public:
	void readImage();
	void edgeDetection();
	void saltPepperNoise();
	void denoise();
    string imageDir;

private:
	Mat imgOriginal;

	Mat SobelXkernel;
	Mat SobelYkernel;

	Mat saltPepperNoiseImage;
	Mat Averagekernel;

};

#endif