#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace std;

class Image {
    public:
        Image();
        Image(cv::Mat, string, int, int);
        cv::Mat image;
        string title;
        int r;
        int c;
};

#endif // IMAGE_H
