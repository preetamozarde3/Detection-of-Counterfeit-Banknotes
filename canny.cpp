#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "auto_canny.h"



int main(int argc,char *argv[])
{
    cv::Mat src=cv::imread(argv[1]),dst;
    cv::cvtColor(src,src,cv::COLOR_BGR2HSV);
    auto_canny(src,dst,0.33);
    cv::namedWindow("auto_canny",CV_WINDOW_NORMAL);
    cv::imshow("auto_canny",dst);
    cv::waitKey(0);
    return 0;
}

