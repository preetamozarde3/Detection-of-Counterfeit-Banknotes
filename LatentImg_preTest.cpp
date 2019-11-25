#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

// Function Headers
Mat MatchTemplate(Mat , Mat);
Mat deskew(Mat& );


int main( int, char** argv )
{
 Mat src_img,templ_img, Cropped_ROI,in;
  
  //Load the template
  const string& templ_file = "Latent_template.jpg" ;
  templ_img = imread(templ_file,1);
 // Load image and template
  in = imread( argv[1],1);
  src_img = deskew(in);

  /// Create windows
  namedWindow( "Source Image", WINDOW_NORMAL );
  namedWindow( "Result window", WINDOW_NORMAL );
  Mat channels[3],out;
  Cropped_ROI = MatchTemplate(src_img,templ_img);
  imwrite("paper_roi_f.jpg",Cropped_ROI);

  cvtColor(Cropped_ROI,Cropped_ROI,cv::COLOR_BGR2HSV);
  split(Cropped_ROI,channels);
  
   
  out = channels[1];

  Mat  kernel = (Mat_<int>(3,3) << -1, -2, -1, 0, 0, 0, 1,2,1);
 
 Point anchor = Point(-1,-1);
 double delta= 0;
 int ddepth=-1;
 int kernel_size=3;

 Mat edges;
 channels[1].copyTo(edges);
 resize(edges,edges, Size(640,264));
 cout<<"rows: "<<edges.rows<<" cols:"<<edges.cols;

 filter2D(edges,edges, ddepth , kernel, anchor, delta, BORDER_DEFAULT ); 

  imshow( "Result window", out );
  imwrite("paper_splane_f.jpg",out);
  
  namedWindow( "Result ", WINDOW_NORMAL );
  imshow( "Result ", edges );
  imwrite("paper_splane_hog_f.jpg",edges);
  
  waitKey(0);
  return 0;
}



// Function Definition

Mat MatchTemplate(Mat img, Mat templ)
{
  Rect roi;
  Mat roi_cropped;
   
  // Source image to display
  Mat img_display,result;
  img.copyTo( img_display );

  // Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_cols, result_rows, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( img, templ, result, CV_TM_CCOEFF_NORMED );
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
  
  matchLoc = maxLoc;  // the best matches are the higher the better


  //Drawing ROI
  rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  
 //Cropinng thr ROI
    
    roi.x = matchLoc.x;
    roi.y = matchLoc.y;
    roi.width = templ.cols;
    roi.height = templ.rows;  
    img_display(roi).copyTo(roi_cropped);

    imshow( "Source Image", img_display );
   
    

  return roi_cropped;
}


Mat deskew(Mat& img)
{   Mat img1;
    int SZ = img.rows;
    float affineFlags = WARP_INVERSE_MAP|INTER_LINEAR;
   
    cvtColor(img,img1,cv::COLOR_BGR2GRAY);

    Moments m = moments(img1);
    if(abs(m.mu02) < 1e-2)
    {
        // No deskewing needed. 
        return img.clone();
    }
    // Calculate skew based on central momemts. 
    double skew = m.mu11/m.mu02;
    // Calculate affine transform to correct skewness. 
    Mat warpMat = (Mat_<double>(2,3) << 1, skew, -0.5*SZ*skew, 0, 1 , 0);
     
    Mat imgOut = Mat::zeros(img.rows, img.cols, img.type());
    warpAffine(img, imgOut, warpMat, imgOut.size(),affineFlags);

    return imgOut;
} 











