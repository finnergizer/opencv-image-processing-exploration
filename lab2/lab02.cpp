/*--------------------------------------------------------------------------------------------*\
CSI 4133 Computer methods for picture processing and analysis
Winter, 2015
\*--------------------------------------------------------------------------------------------*/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "lab02.h"

using namespace std;
using namespace cv;
string videoDir = "";
string imageDir = "";
int lab02::readVideo()
{
	cv::VideoCapture vid(videoDir + "park.avi"); // open the default camera
	if(!vid.isOpened()) // check if we succeeded
		return -1;

	int NoF = vid.get(CV_CAP_PROP_FRAME_COUNT); // Number of frames

	for (size_t i = 0;i != NoF; ++i)
	{
		Mat frame;
		vid >> frame; // get a new frame from camera
		imshow("processed video", frame);
		if(waitKey(30) >= 0) break;
	}
	return 0;
}

void lab02::ImageThresholding()
{
    Mat imgOriginal1 = imread(imageDir + "park466.bmp");
    Mat imgOriginal2 = imread(imageDir + "park467.bmp");
    
    Mat imgGray1;
    Mat imgGray2;
    Mat imgDiff;
    Mat imgThreshold;
    
    cvtColor(imgOriginal1, imgGray1, CV_RGB2GRAY);
    cvtColor(imgOriginal2, imgGray2, CV_RGB2GRAY);
    
    absdiff(imgGray1, imgGray2, imgDiff);
    threshold(imgDiff, imgThreshold, 25, 255, 0);
    
    imwrite(imageDir + "park-diff-threshold.bmp", imgThreshold);
}

void lab02::VideoThresholding()
{
    cv::VideoCapture vid(videoDir+ "park.avi");
    
    int NoF = vid.get(CV_CAP_PROP_FRAME_COUNT); // Number of frames
    
    vector<Mat> vidOriginal;
    vector<Mat> vidProcessed;
    
    //Create the original vector of images
    for (size_t i = 0;i != NoF; ++i)
    {
        Mat frame;
        vid >> frame; // get a new frame from video
        vidOriginal.push_back(frame);
    }
    
    //Create the processed vector of images
    for(std::vector<Mat>::size_type i = 0; i != vidOriginal.size()-1; i++){
        Mat imgOriginal1 = vidOriginal[i];
        Mat imgOriginal2 = vidOriginal[i+1];
        
        Mat imgGray1;
        Mat imgGray2;
        Mat imgDiff;
        Mat imgThreshold;
        
        cvtColor(imgOriginal1, imgGray1, CV_RGB2GRAY);
        cvtColor(imgOriginal2, imgGray2, CV_RGB2GRAY);
        
        absdiff(imgGray1, imgGray2, imgDiff);
        
        threshold(imgDiff, imgThreshold, 25, 255, 0);
        vidProcessed.push_back(imgThreshold);
    }
    
    //Putting -1 as the fourcc codec is not supported (i.e. a prompt asking for codec selection is not supported), therefore the mp4v codec is used as it works on my OSX machine.
    VideoWriter vwriter = VideoWriter(videoDir + "parkdiff.mp4", CV_FOURCC('m', 'p', '4', 'v'), vid.get(CV_CAP_PROP_FPS), Size(vid.get(CV_CAP_PROP_FRAME_WIDTH), vid.get(CV_CAP_PROP_FRAME_HEIGHT)), true);
    for(std::vector<Mat>::size_type i = 0; i != vidProcessed.size(); i++){
        Mat gray3channel;
        //Since the isColor=false is not supported on Mac OSX (Windows only in Documentation) for VideoWriter, I have created a 3 channel image so that an exception will not be raised when saving;
        Mat imageArr[] = {vidProcessed[i], vidProcessed[i], vidProcessed[i]};
        merge(imageArr, 3, gray3channel);
        vwriter.write(gray3channel);
    }

}
