#include "utility.h"

Mat iterateMask(Mat f, Mat w)
{

    auto m = w.cols;
    auto n = w.rows;
    auto a = (m - 1) / 2;
    auto b = (n - 1) / 2;
    auto padSize = w.rows - 1;
    Mat fPadded = Mat::zeros(f.rows + 2 * padSize, f.cols + 2 * padSize, CV_64F);
    Mat g = Mat::zeros(f.rows + 2 * padSize, f.cols + 2 * padSize, CV_64F);

    //Pad is adding
    auto roi = fPadded(Rect(w.cols - 1, w.rows - 1, f.cols, f.rows));
    f.copyTo(roi);

    //Start with some margin, because we padded the Mat
    //Iterate all the points
    for (auto y = padSize - 1; y < fPadded.rows - padSize + 1; ++y)
    {
        for (auto x = padSize - 1; x < fPadded.cols - padSize + 1; ++x)
        {
            //Get the Mat which consist of neighbours of the point
            Mat neighbourhood = fPadded(Rect(x - a, y - b, w.cols, w.cols));

            //Apply the filter
            g.at<double>(y, x) = applyFilter(neighbourhood , w);
        }
    }

    //Return unpadded Mat
    return g(Rect(padSize, padSize, f.cols, f.rows));
}

Mat iterateMaskForGradient(Mat f)
{
    //Equation: 3.6-16
    Mat gx = (Mat_<int>(3, 3) <<
        -1, -2, -1,
        0, 0, 0,
        1, 2, 1);

    //Equation: 3.6-17
    Mat gy = (Mat_<int>(3, 3) <<
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1);


    auto m = gy.cols;
    auto n = gy.rows;
    auto a = (m - 1) / 2;
    auto b = (n - 1) / 2;
    auto padSize = gy.rows - 1;
    Mat fPadded = Mat::zeros(f.rows + 2 * padSize, f.cols + 2 * padSize, CV_64F);
    Mat M = Mat::zeros(f.rows + 2 * padSize, f.cols + 2 * padSize, CV_64F);

    //Pad is adding
    auto roi = fPadded(Rect(gx.cols - 1, gx.rows - 1, f.cols, f.rows));
    f.copyTo(roi);

    //Start with some margin, because we padded the Mat
    //Iterate all the points
    for (auto y = padSize - 1; y < fPadded.rows - padSize + 1; ++y)
    {
        for (auto x = padSize - 1; x < fPadded.cols - padSize + 1; ++x)
        {
            //Get the Mat which consist of neighbours of the point
            Mat neighbourhood = fPadded(Rect(x - a, y - b, gx.cols, gx.cols));

            //Find gx, gy

            //Calculate  Eq 3.6-16
            auto gxValue = applyFilter(neighbourhood, gx);
            //Calculate Eq 3.6-17
            auto gyValue = applyFilter(neighbourhood, gy);

            //Put the outputs into the Eq 3.6-18
            M.at<double>(y, x) = dip::stayInBoundaries(std::abs(gxValue) + std::abs(gyValue) , dip::Upper(255) , dip::Lower(0));
        }
    }

    //Return unpadded Mat
    return M(Rect(padSize, padSize, f.cols, f.rows));
}

double applyFilter(Mat f, Mat w)
{
    auto result = .0;

    cv::rotate(w, w, RotateFlags::ROTATE_180);

    //w(x,y) * f(x,y) = w(s,t) * f(x + s, y + t)
    for (auto y = 0; y < f.rows; ++y)
    {
        for (auto x = 0; x < f.cols; ++x)
        {
            auto wi = w.at<int>(y, x);
            auto fi = f.at<double>(y, x);
            result += wi * fi;
        }
    }

    return result;
}
