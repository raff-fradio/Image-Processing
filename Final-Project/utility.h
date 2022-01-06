#ifndef UTILITY_H
#define UTILITY_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace cv;

class Utility
{
private:
    int FRAMES_TO_LEARN = 200;
    int learnedFrames;
    Mat model, mask, kernel;
    Ptr<BackgroundSubtractor> pBackSub;

public:
    static const int FRAME_HEIGHT = 320;
    static const int FRAME_WIDTH = 640;

    Utility();
    Mat getForeground(Mat frame);
};

#endif // UTILITY_H
