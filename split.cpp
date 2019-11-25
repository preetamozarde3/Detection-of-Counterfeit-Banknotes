#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
  Mat input, split_img, channels[3],output;

  input = imread(argv[1],CV_LOAD_IMAGE_COLOR);
  
 
  if (input.empty())
     {
              cout << "Image cannot be loaded..!!" << endl;
              return -1;
     }


// cvtColor(input,split_img,cv::COLOR_BGR2HSV);
// cvtColor(input,split_img,cv::COLOR_BGR2XYZ);
// cvtColor(input,split_img,cv::COLOR_BGR2YCrCb);
// cvtColor(input,split_img,cv::COLOR_BGR2Lab);
 cvtColor(input,split_img,cv::COLOR_BGR2Luv);
 imwrite("paper_Luv_f.jpg",split_img);
 
 split(split_img,channels);
 output = channels[1];

 //output  = channels[2] - channels[1];

 namedWindow( "Original Image" , WINDOW_NORMAL );
 imshow( "Original Image", input );
 
 namedWindow( "Output Image" , WINDOW_NORMAL );
 imshow( "Output Image", split_img ); 

 namedWindow( "channel 0" , WINDOW_NORMAL );
 imshow( "channel 0", channels[0] );
 
 namedWindow( "channel 1" , WINDOW_NORMAL );
 imshow( "channel 1", channels[1] ); 
 
 
 namedWindow( "channel 2" , WINDOW_NORMAL );
 imshow( "channel 2", channels[2]); 
 
 namedWindow( "output plane" , WINDOW_NORMAL );
 imshow( "output plane", output );
 imwrite("paper_Luv_u_f.jpg",output); 

  waitKey(0);
     
 return 0;

}


/*
channel[0] = B plane / H plane 
channel[1] = G plane / S plane
channel[2] = R plane / V plane  */

/*
channel[0] = B plane / H plane
channel[1] = G plane / S plane
channel[2] = R plane / V plane  */

/*Mat  kernel = (Mat_<int>(3,3) << -1, -1, -1, -1, 9, -1, -1, -1,-1);
 Point anchor = Point(-1,-1);
 double delta= 0;
 int ddepth=-1;
 int kernel_size=3;

 cout << "kernel = " << endl << " " << kernel << endl << endl;

 filter2D(input, output, ddepth , kernel, anchor, delta, BORDER_DEFAULT ); */


	  
 /*int threshval = 190;
 int threshtype = 0;//truncate to zero
 int threshmax = 255;
 //blur( output, output, Size(3,3) );
 threshold(out1,output,threshval,threshmax,threshtype); */




