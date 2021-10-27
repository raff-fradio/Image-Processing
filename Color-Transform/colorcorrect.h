#ifndef COLORCORRECT_H
#define COLORCORRECT_H

#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;


class colorcorrect
{
public:
    colorcorrect();
    Mat colorCorrect(Mat);
    Mat concat(Mat, Mat);
    Mat callBack(Mat, Mat, Mat);

    int hmin = 0;
    int hmin_Max = 360;
    int hmax = 360;
    int hmax_Max = 360;

    int smin = 0;
    int smin_Max = 255;
    int smax = 255;
    int smax_Max = 255;

    int vmin = 106;
    int vmin_Max = 255;
    int vmax = 250;
    int vmax_Max = 255;

private:

};

#endif // COLORCORRECT_H
