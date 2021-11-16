#include "morphological-operations.h"

MorphologicalOperation::MorphologicalOperation(int width, int height){
    this->kernel = cv::getStructuringElement(MORPH_CROSS, Size(width, height));
}

cv::Mat MorphologicalOperation::applyErosion(cv::Mat image){
    cv::Mat erosionImg;
    cv::morphologyEx(image, erosionImg, MORPH_ERODE, kernel);
    return erosionImg;
}

cv::Mat MorphologicalOperation::applyDilatation(cv::Mat image){
    cv::Mat dilatationImg;
    cv::morphologyEx(image, dilatationImg, MORPH_DILATE, kernel);
    return dilatationImg;
}

cv::Mat MorphologicalOperation::applyTopHat(cv::Mat image){
    cv::Mat topHatImg;
    cv::morphologyEx(image, topHatImg, MORPH_TOPHAT, kernel);
    return topHatImg;
}

cv::Mat MorphologicalOperation::applyBlackHat(cv::Mat image){
    cv::Mat blackHatImg;
    cv::morphologyEx(image, blackHatImg, MORPH_BLACKHAT, kernel);
    return blackHatImg;
}

cv::Mat MorphologicalOperation::applyEquation(cv::Mat image){
    cv::Mat retultImg = image + (applyTopHat(image) - applyBlackHat(image));
    return retultImg;
}

void MorphologicalOperation::createKernel(int size){
    if (size % 2 != 0 && size != 0)
        this->kernel = cv::getStructuringElement(MORPH_CROSS, Size(size, size));
    else
        throw int(21);
}
