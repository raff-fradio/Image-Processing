#include "utility.h"
#include <iostream>

using namespace std;

Utility::Utility()
{
    pBackSub = createBackgroundSubtractorMOG2(500, 16, false);
    kernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
}

Mat Utility::getForeground(Mat frame) {

    Mat foreground, fgMask, result;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    frame.copyTo(foreground);

    GaussianBlur(foreground, foreground, Size(7,7), 0);
    pBackSub->apply(foreground, fgMask);
    dilate(fgMask, fgMask, kernel, Point(-1, -1), 3);

    cvtColor(fgMask, fgMask, COLOR_GRAY2BGR);
    bitwise_and(frame, fgMask, result);

    return result;
}
