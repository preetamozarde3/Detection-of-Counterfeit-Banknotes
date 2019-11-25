#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
  Mat input, hsv_img, ycrb_img, channels[3],out1,output;

  input = imread(argv[1],CV_LOAD_IMAGE_COLOR);
  
 
  if (input.empty())
     {
              cout << "Image cannot be loaded..!!" << endl;
              return -1;
     }


 cvtColor(input,hsv_img,cv::COLOR_BGR2HSV);
// cvtColor(hsv_img,output,cv::COLOR_BGR2GRAY);

 split(hsv_img,channels);
 out1 = channels[1]; 

 GaussianBlur(hsv_img,output, Size(7,7), 1.5, 1.5);
 Canny(output,output, 0, 30, 3); 

 split(hsv_img,channels);
 out1 = channels[1];


 namedWindow( "Original Image" , WINDOW_NORMAL );
 imshow( "Original Image", input );
 
 namedWindow( "Output Image" , WINDOW_NORMAL );
 imshow( "Output Image", hsv_img ); 

 namedWindow( "channel 0" , WINDOW_NORMAL );
 imshow( "channel 0", channels[0] );
 
 namedWindow( "channel 1" , WINDOW_NORMAL );
 imshow( "channel 1", channels[1] ); 
 
 namedWindow( "channel 2" , WINDOW_NORMAL );
 imshow( "channel 2", channels[2]); 
 
 namedWindow( "Edge Image" , WINDOW_NORMAL );
 imshow( "Edge Image", output ); 
  waitKey(0);
     
 return 0;

}


/*
channel[0] = B plane / H plane
channel[1] = G plane / S plane
channel[2] = R plane / V plane  */




