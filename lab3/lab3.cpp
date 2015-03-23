/*--------------------------------------------------------------------------------------------*\
CSI 4133 Computer methods for picture processing and analysis
Winter, 2015
\*--------------------------------------------------------------------------------------------*/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "lab03.h"

using namespace std;
using namespace cv;

int main()
{
	// Create assignment1 object
	lab03 sfinn038; // your user name

	// Reading an image
//	sfinn038.readImage();

	// The rest of processing
    sfinn038.edgeDetection();
    sfinn038.saltPepperNoise();
    sfinn038.denoise();
}

