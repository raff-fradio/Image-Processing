#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "utility.h"

class Histogram
{
public:
    Histogram();
    static void fillZero(double* arr, int size);
    static cv::Mat equalizeHistogram(cv::Mat input);
    static double* calculateHistogram(cv::Mat input);
    static double* calculatePdf(double* histogram, int totalPixelSize);
    static double* calculateCdf(double* pdf);
};

#endif // HISTOGRAM_H
