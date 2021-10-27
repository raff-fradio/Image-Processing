#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "NamedType.h"

using namespace cv;

Mat iterateMask(Mat f, Mat w);
Mat iterateMaskForGradient(Mat f);
double applyFilter(Mat f, Mat w);

#endif // UTILITY_H
