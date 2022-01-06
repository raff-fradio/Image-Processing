#ifndef MATTOQIMAGE_H
#define MATTOQIMAGE_H

// Qt header files
#include <QtGui>
#include <QDebug>
// OpenCV header files
#include <opencv2/cvconfig.h>
#include <opencv2/highgui.hpp>

using namespace cv;

QImage MatToQImage(const Mat&);

#endif // MATTOQIMAGE_H
