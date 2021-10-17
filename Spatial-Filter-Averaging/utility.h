#ifndef UTILITY_H
#define UTILITY_H

#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>

using namespace cv;

Mat applyBoxMask(Mat input);
Mat applyWeightedAverageMask(Mat input);
Mat applyMedian(Mat f, int size);
int applyMask(Mat input, Mat mask);
void printMat(Mat input);
Mat iterateLinearMask(Mat f, Mat w);

#endif // UTILITY_H
