#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/**
 * @function main
 */
int main(int argc, char** argv)
{
  Mat src, dst,output;

  src = imread( argv[1], IMREAD_COLOR );

  if( src.empty() )
    { return -1; }
 

 // cvtColor(src,src,cv::COLOR_BGR2HSV);
 // cvtColor(src,output,cv::COLOR_BGR2GRAY);

  
 cvtColor(src,src,cv::COLOR_BGR2YCrCb);

  vector<Mat> planes;
  split( src, planes );

  /// Establish the number of bins
  int histSize = 256;

  /// Set the ranges ( for B,G,R) )
  float range[] = { 0, 256 } ;
  const float* histRange = { range };

  bool uniform = true; bool accumulate = false;

  Mat img_hist;

  /// Compute the histograms:
  calcHist( &planes[1], 1, 0, Mat(), img_hist, 1, &histSize, &histRange, uniform, accumulate );

  // Draw the histograms 
  int hist_w = 512; int hist_h = 400;
  int bin_w = cvRound( (double) hist_w/histSize );

  Mat histImage( hist_h, hist_w, CV_8UC1, Scalar(0) );

  /// Normalize the result to [ 0, histImage.rows ]
  normalize(img_hist, img_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );


  /// Draw for each channel
  for( int i = 1; i < histSize; i++ )
  {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(img_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(img_hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
  }

  /// Display
  namedWindow("calcHist Demo", WINDOW_AUTOSIZE );
  imshow("calcHist Demo", histImage );

  waitKey(0);

  return 0;

}
