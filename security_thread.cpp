#include <iostream>
#include <string.h>
 #include <ctime>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/ml/ml.hpp"


using namespace std;
using namespace cv;

double apply_kmeans(Mat);

int main(int argc, char** argv)
{
  Mat input, split_img, ycrb_img, channels[3],out1,output;
  double dist_s,dist_cr,dist_u;
  vector<double> distances;
 
  
//int start_s=clock(); ///time start

for(int i=1;i<=30;i++)
{
     const String& img_file = "fake"+ to_string(i) +".jpg" ;
     input = imread(img_file,1);
 
  if (input.empty())
     {
              cout << "Image cannot be loaded..!!" << endl;
              return -1;
     }


//input = imread(argv[1],CV_LOAD_IMAGE_COLOR);
//const String& img_file = argv[1] ;

 cout<<"\n "<<img_file<<"\n Details:\n";


 cvtColor(input,split_img,cv::COLOR_BGR2HSV);
 split(split_img,channels);
 output = channels[1];
 dist_s = apply_kmeans(output);

 cvtColor(input,split_img,cv::COLOR_BGR2YCrCb);
 split(split_img,channels);
 output = channels[1];
 dist_cr = apply_kmeans(output);

 cvtColor(input,split_img,cv::COLOR_BGR2Luv);
 split(split_img,channels);
 output = channels[1];
 dist_u = apply_kmeans(output);

 cout<<"Distances:\n Dist_s : "<<dist_s<<"\n Dist_cr : "<<dist_cr<<"\n Dist_u : "<<dist_u; 

 double dis;
 dis = (dist_s/255 + dist_cr/255 + dist_s/255)/3;
 cout<<"\n combined distance : "<<dis<<"\n";

//int stop_s=clock();  ///time end
//cout << "\t time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC) << endl;

distances.push_back(dis);
}

   for(int i = 0; i < distances.size(); i++) 
   cout<<"\n for "<<i+1<<" : "<<distances[i];
     
 return 0;

}



double apply_kmeans(Mat image)
{

  Mat dataimg=image;
 // image.copyTo(dataimg);
  
  double result;
  Mat labels,centers;
  int k=2;
  int attempts= 5;
  int flags = KMEANS_PP_CENTERS;
  long sampleCount  = dataimg.rows*dataimg.cols;
  
  Mat points;
  dataimg.convertTo(points,CV_32FC1);
  points = points.reshape(0,sampleCount);
  
  result=kmeans(points, k, labels, TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 0.01),attempts, flags,centers);  
 
  double distance = abs(centers.at<float>(0,0)-centers.at<float>(1,0));
 
return distance;

 }














