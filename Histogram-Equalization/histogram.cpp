#include "histogram.h"

#define L 256

Histogram::Histogram()
{

}
void Histogram::fillZero(double* arr, int size)
{
    for (auto i = 0; i < size; ++i)
    {
        arr[i] = 0;
    }
}

double* Histogram::calculateHistogram(cv::Mat input)
{
    double* inputHistogram = new double[L];
    fillZero(inputHistogram, L);

    for (auto y = 0; y < input.rows; ++y)
    {
        for (auto x = 0; x < input.cols; ++x)
        {
            inputHistogram[input.at<uchar>(y, x)]++;
        }
    }

    return inputHistogram;
}

double* Histogram::calculatePdf(double* histogram, int totalPixelSize)
{
    double* pdf = new double[L];
    fillZero(pdf, L);

    for (auto i = 0; i < L; ++i)
    {
        pdf[i] = histogram[i] / totalPixelSize;
    }

    return pdf;
}

double* Histogram::calculateCdf(double* pdf)
{
    double* cdf = new double[L];
    fillZero(cdf, L);
    cdf[0] = pdf[0];

    for (auto i = 1; i < L; ++i)
    {
        cdf[i] = cdf[i - 1] + pdf[i];
    }

    return cdf;
}

cv::Mat Histogram::equalizeHistogram(cv::Mat input)
{

    //Firstly calculate histogram
    double* inputHistogram = calculateHistogram(input);
    //Secondly extract probability density function(PDF) from the histogram
    double* inputPdf = calculatePdf(inputHistogram, input.rows * input.cols);
    //Thirdly cumulative probability function(CDF) from PDF
    double* inputCdf = calculateCdf(inputPdf);

    cv::Mat output(input.rows, input.cols, CV_8U);

    //As last, map old image intensity values
    for (auto y = 0; y < input.rows; ++y)
    {
        for (auto x = 0; x < input.cols; ++x)
        {
            auto oldIntensity = input.at<uchar>(y, x);

            //Full implementation of Equation 3.3-8
            output.at<uchar>(y, x) = std::round((L - 1) * inputCdf[oldIntensity]);
        }
    }

    //Calculate output histogram and pdf
//    double* outputHistogram = calculateHistogram(output);
//    double* outputPdf = calculatePdf(outputHistogram, output.rows * output.cols);

//    imshow("input histogram", dip::drawHistogram(inputPdf, L));
//    imshow("output histogram", dip::drawHistogram(outputPdf, L));

    return output;
}
