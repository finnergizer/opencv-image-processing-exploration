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

string image2Dir = "/Users/shaughnfinnerty/code/school/csi4133/csi4133sandbox/images/";

void lab03::readImage()
{
	imgOriginal = imread("field.jpg"); 
	imshow("Original Image", imgOriginal);
	waitKey(0);
}

void lab03::edgeDetection()
{
    Mat img = imread(image2Dir + "boldt.jpg");
    Mat imgGrayScale;
    cvtColor(img, imgGrayScale, CV_RGB2GRAY);
    
    signed char xfilter[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
    signed char yfilter[3][3] = {{1,2,1}, {0,0,0}, {-1,-2,-1}};
    Mat xfilterMat = Mat(3,3, CV_8SC1, xfilter);
    Mat yfilterMat = Mat(3,3, CV_8SC1, yfilter);
    
    Mat sobelX;
    Mat sobelY;
    Mat magnitudeSobel;
    
    int ddepth = CV_16S;
    
    //NOTE! we should change this to 16S so as to avoid overfloew
//    filter2D(imgGrayScale,sobelX,imgGrayScale.depth(),xfilterMat);
//    filter2D(imgGrayScale,sobelY,imgGrayScale.depth(),yfilterMat);
    
    filter2D(imgGrayScale,sobelX,ddepth,xfilterMat);
    filter2D(imgGrayScale,sobelY,ddepth,yfilterMat);
    

    Mat sobelX8Bit;
    Mat sobelY8Bit;
    convertScaleAbs(sobelX, sobelX8Bit);
    convertScaleAbs(sobelY, sobelY8Bit);
    imshow("SobelX", sobelX8Bit);
    waitKey();
    imshow("SobelY", sobelY8Bit);
    waitKey();
    Mat customSobel;
    add(sobelX8Bit, sobelY8Bit, customSobel);
//    addWeighted( abs(sobelX), 0.5, abs(sobelY), 0.5, 0, customSobel );
    imshow("Custom Sobel", customSobel);
    waitKey();
    
    Mat grad_x, grad_y, abs_grad_x, abs_grad_y;

    int scale = 1;
    int delta = 0;
    Mat grad;
    /// Gradient X
    Sobel( imgGrayScale, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );
    
    /// Gradient Y
    Sobel( imgGrayScale, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );
    
//  Total Gradient (approximate)
//    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
    add(abs_grad_x, abs_grad_y, grad);
    
    imshow("Using CV Sobel", grad);
    waitKey();
    
}

void lab03::saltPepperNoise()
{
	//Add your modification code here
    Mat img = imread(image2Dir + "boldt.jpg");
    int positionX, positionY;
    int portion = img.rows * img.cols * 0.3;
    cout << img.rows;
    cout << img.cols;
    imshow("Original",img);
    waitKey();
    for(int i=0; i<portion; i++){

        int randomChannel = rand()%3;
        positionX = rand()%img.rows;
        positionY = rand()%img.cols;
        //Should the noise be a random value or should it be a function of the original
        img.at<Vec3b>(positionX, positionY)[randomChannel] = 255-img.at<Vec3b>(positionX, positionY)[randomChannel];
//        img.at<Vec3b>(positionX, positionY)[randomChannel] = 255-img.at<Vec3b>(positionX, positionY)[randomChannel];
    }
    imwrite(image2Dir + "boldt-noise.jpg", img);
    imshow("Modified", img);
    waitKey();
    
}

void lab03::denoise()
{
	//Add your modification code here
    Mat img = imread(image2Dir + "boldt-noise.jpg");
    imshow("Noisy Image", img);
    waitKey();
    float averageFilter[3][3] = {{1,1,1},{1,1,1}, {1,1,1}};
    int sum = 0;
    
    //Calculate the sum of the kernel entries, for averaging
    for(int i = 0; i < sizeof(*averageFilter) / sizeof(**averageFilter); i++){
        for(int j=0; j < sizeof(averageFilter)  / sizeof(*averageFilter); j++){
            sum += averageFilter[i][j];
        }
    }

    //Average the kernel entries before applying
    for(int i = 0; i < sizeof(*averageFilter) / sizeof(**averageFilter); i++){
        for(int j=0; j < sizeof(averageFilter)  / sizeof(*averageFilter); j++){
            averageFilter[i][j] = averageFilter[i][j]/sum;
        }
    }
    
    Mat averageFilterMat = Mat(3,3, CV_32F, averageFilter);
    Mat imgAverage, imgMedian, imgGaussian;
    filter2D(img,imgAverage,img.depth(),averageFilterMat);
    imshow("Average Blur", imgAverage);
    waitKey();
    
    //Best results from denoising as salt and pepper noise is not used in an average calculation, rather it is not selected as the median value.
    medianBlur(img, imgMedian, 3);
    imshow("Median Blur", imgMedian);
    waitKey();
    
    GaussianBlur(img, imgGaussian, Size(9,9), 1.0);
    imshow("Gaussian Blur", imgGaussian);
    waitKey();
    
}

