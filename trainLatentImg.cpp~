#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/ml/ml.hpp"
#include <iostream>
#include <stdio.h>


using namespace std;
using namespace cv;

// Function Headers
Mat MatchTemplate(Mat , Mat);
vector<float> computeHOG(Mat);
Mat deskew(Mat& );


int main( int argc, char** argv )
{
 Mat in,src_img,templ_img, Cropped_ROI,result;
 int positive_count,negative_count;
 positive_count = 40;
 negative_count = 20;
 vector<float> HOGvec;
 vector<vector<float>> trainVector;
 
  //Load the template
  const string& templ_file = "Latent_template.jpg" ;
  templ_img = imread(templ_file,1);

  for(int i=1;i<=positive_count;i++)
  {    
     //Load the image
     const String& img_file = "real"+ to_string(i) +".jpg" ;
     in = imread(img_file,1);

     if (in.empty())
     { 
	cout<<"Image cannot be loaded..!!"<<endl;
        return -1;
      }

     //Deskew the image if required
     src_img = deskew(in);
 
  Cropped_ROI = MatchTemplate(src_img,templ_img);
  //Compute HOG of ROI
  HOGvec = computeHOG(Cropped_ROI);
  trainVector.push_back(HOGvec);

 }

 for(int i=1;i<=negative_count;i++)
 {    
     const String& img_file = "fake"+ to_string(i) +".jpg" ;
     in = imread(img_file,1);

    if (in.empty())
     { 
	cout<<"Image cannot be loaded..!!"<<endl;
        return -1;
      }

     //Deskew the image if required
     src_img = deskew(in);
 
  Cropped_ROI = MatchTemplate(src_img,templ_img); 
  HOGvec = computeHOG(Cropped_ROI);
  trainVector.push_back(HOGvec);
 }
 // vector to matrix
 // trainVector.size() equals positive_count + negative_count
  int descriptor_size = trainVector[0].size();
  Mat HOGfeatMatrix(positive_count + negative_count, descriptor_size , CV_32FC1);

  Mat labels( positive_count + negative_count, 1, CV_32FC1, Scalar(-1.0) );
  labels.rowRange( 0, positive_count ) = Scalar( 1.0 );

  for (int i=0;i<labels.rows;++i)
    cout<<labels.at<float>(i,0)<<endl;
  
  for (int i = 0; i<trainVector.size(); i++) 
  {
	for (int j = 0; j<descriptor_size; j++) 
        {
          HOGfeatMatrix.at<float>(i, j) = trainVector[i][j];
	}
   }
// Set SVM parameters 
CvSVMParams params;
params.svm_type    = SVM::C_SVC;
params.C           = 0.1;
params.kernel_type = SVM::RBF;
params.term_crit   = TermCriteria(CV_TERMCRIT_ITER, (int)1e7, 1e-6);
CvSVM svm;
//Train the SVM
svm.train_auto(HOGfeatMatrix, labels, Mat(), Mat(), params);
//save the trained model
svm.save("TrainedModel.xml");

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
  // Do the Matching and Normalize
  matchTemplate( img, templ, result, CV_TM_CCOEFF );
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
  /// Localizing the best match with minMaxLoc
  double minVal; 
  double maxVal; 
  Point minLoc; 
  Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
  // the best matches are the higher the better
  matchLoc = maxLoc;  
  //Drawing ROI
  rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );  
  //Cropinng thr ROI
    roi.x = matchLoc.x+10;
    roi.y = matchLoc.y+10;
    roi.width = templ.cols-20;
    roi.height = templ.rows-20;  
    img_display(roi).copyTo(roi_cropped);
    
  return roi_cropped;
}



vector<float> computeHOG(Mat img)
{
  Mat src,hsv,channel[3];
  img.copyTo(src);
  Mat imgLatent;

 cvtColor( src, hsv, CV_BGR2HSV );
 split(hsv,channel);
 channel[1].copyTo(imgLatent);
  
 resize(imgLatent,imgLatent, Size(640,264));

 //Set the HOG class parameters
 HOGDescriptor hog( 
	Size(640,264), //winSize 
        Size(16,16), //blocksize
        Size(8,8),   //blockStride,
        Size(8,8), //cellSize,
                 9,  //nbins,
                  1, //derivAper,
                 -1, //winSigma,
                  0, //histogramNormType,
                0.2, //L2HysThresh,
                  1, //gammal correction,
                  64);//nlevels=64                  

 vector<float> descriptors;
 hog.compute(imgLatent, descriptors );

 return descriptors;

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



 











