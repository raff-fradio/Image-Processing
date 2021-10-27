#include "colorcorrect.h"

colorcorrect::colorcorrect()
{
    hmin = 0;
    hmin_Max = 360;
    hmax = 360;
    hmax_Max = 360;

    smin = 0;
    smin_Max = 255;
    smax = 255;
    smax_Max = 255;

    vmin = 106;
    vmin_Max = 255;
    vmax = 250;
    vmax_Max = 255;
}

Mat colorcorrect::colorCorrect(Mat source) {
    Mat simg;
    int filterFactor = 1;

    cvtColor(source, simg, COLOR_BGR2GRAY);

    long int N = simg.rows*simg.cols;

    int histo_b[256];
    int histo_g[256];
    int histo_r[256];

    for(int i=0; i<256; i++){
        histo_b[i] = 0;
        histo_g[i] = 0;
        histo_r[i] = 0;
    }
    Vec3b intensity;

    for(int i=0; i<simg.rows; i++){
        for(int j=0; j<simg.cols; j++){
            intensity = source.at<Vec3b>(i,j);

            histo_b[intensity.val[0]] = histo_b[intensity.val[0]] + 1;
            histo_g[intensity.val[1]] = histo_g[intensity.val[1]] + 1;
            histo_r[intensity.val[2]] = histo_r[intensity.val[2]] + 1;
        }
    }

    for(int i = 1; i<256; i++){
        histo_b[i] = histo_b[i] + filterFactor * histo_b[i-1];
        histo_g[i] = histo_g[i] + filterFactor * histo_g[i-1];
        histo_r[i] = histo_r[i] + filterFactor * histo_r[i-1];
    }

    int vmin_b=0;
    int vmin_g=0;
    int vmin_r=0;
    int s1 = 3;
    int s2 = 3;

    while(histo_b[vmin_b+1] <= N*s1/100){
        vmin_b = vmin_b +1;
    }
    while(histo_g[vmin_g+1] <= N*s1/100){
        vmin_g = vmin_g +1;
    }
    while(histo_r[vmin_r+1] <= N*s1/100){
        vmin_r = vmin_r +1;
    }

    int vmax_b = 255-1;
    int vmax_g = 255-1;
    int vmax_r = 255-1;

    while(histo_b[vmax_b-1]>(N-((N/100)*s2)))
    {
        vmax_b = vmax_b-1;
    }
    if(vmax_b < 255-1){
        vmax_b = vmax_b+1;
    }
    while(histo_g[vmax_g-1]>(N-((N/100)*s2)))
    {
        vmax_g = vmax_g-1;
    }
    if(vmax_g < 255-1){
        vmax_g = vmax_g+1;
    }
    while(histo_r[vmax_r-1]>(N-((N/100)*s2)))
    {
        vmax_r = vmax_r-1;
    }
    if(vmax_r < 255-1){
        vmax_r = vmax_r+1;
    }

    for(int i=0; i<simg.rows; i++)
    {
        for(int j=0; j<simg.cols; j++)
        {

            intensity = source.at<Vec3b>(i,j);

            if(intensity.val[0]<vmin_b){
                intensity.val[0] = vmin_b;
            }
            if(intensity.val[0]>vmax_b){
                intensity.val[0]=vmax_b;
            }


            if(intensity.val[1]<vmin_g){
                intensity.val[1] = vmin_g;
            }
            if(intensity.val[1]>vmax_g){
                intensity.val[1]=vmax_g;
            }


            if(intensity.val[2]<vmin_r){
                intensity.val[2] = vmin_r;
            }
            if(intensity.val[2]>vmax_r){
                intensity.val[2]=vmax_r;
            }

            source.at<Vec3b>(i,j) = intensity;
        }
    }

    for(int i=0; i<simg.rows; i++){
        for(int j=0; j<simg.cols; j++){

            intensity = source.at<Vec3b>(i,j);
            intensity.val[0] = (intensity.val[0] - vmin_b)*255/(vmax_b-vmin_b);
            intensity.val[1] = (intensity.val[1] - vmin_g)*255/(vmax_g-vmin_g);
            intensity.val[2] = (intensity.val[2] - vmin_r)*255/(vmax_r-vmin_r);
            source.at<Vec3b>(i,j) = intensity;
        }
    }


    // sharpen image using "unsharp mask" algorithm
    Mat blurred; double sigma = 1, threshold = 5, amount = 1;
    GaussianBlur(source, blurred, Size(), sigma, sigma);
    Mat lowContrastMask = abs(source - blurred) < threshold;
    Mat sharpened = source*(1+amount) + blurred*(-amount);
    source.copyTo(sharpened, lowContrastMask);

    return sharpened;
}

Mat colorcorrect::concat(Mat source, Mat sharpened) {
    Mat comp_img;
    Mat orig_img = source.clone();

    hconcat(orig_img, sharpened, comp_img);
    return comp_img;
}

Mat colorcorrect::callBack(Mat img, Mat bgr, Mat hsv) {
    Mat dst = Mat::zeros(img.size(), CV_32FC3);
    //掩码
    Mat mask;
    inRange(hsv, Scalar(hmin, smin / float(smin_Max), vmin / float(vmin_Max)), Scalar(hmax, smax / float(smax_Max), vmax / float(vmax_Max)), mask);
    //只保留
    for (int r = 0; r < bgr.rows; r++)
    {
        for (int c = 0; c < bgr.cols; c++)
        {
            if (mask.at<uchar>(r, c) == 255)
            {
                dst.at<Vec3f>(r, c) = bgr.at<Vec3f>(r, c);
            }
        }
    }
    dst.convertTo(dst, CV_8UC3, 255.0, 0);
    return dst;
}
