/*--------------------------------------------------------------------------------------------*\
CSI 4133 Computer methods for picture processing and analysis
Winter, 2015
\*--------------------------------------------------------------------------------------------*/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#if !defined LAB2
#define LAB2

using namespace std;
using namespace cv;

class lab02
{
public:
	int readVideo();
	void ImageThresholding();// Part A
	void VideoThresholding();// Part B

private:
	vector<Mat> vidOriginal;
	vector<Mat> vidProcessed;
};

#endif