#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <vector>

using namespace cv;
using namespace std;
	


int main(int argc, char** argv)
{
 VideoCapture cap("video.mp4");

 namedWindow("trackbar",WINDOW_NORMAL);
 namedWindow("video",WINDOW_NORMAL);
  namedWindow("video2",WINDOW_NORMAL); 
 createTrackbar("toplane","trackbar",0,1280);
 createTrackbar("baselane","trackbar",0,1280);
 createTrackbar("hight","trackbar",0,720);
 
 
 
 while(1){
 	Mat video;
 	cap >> video;
 	int topl = getTrackbarPos("toplane", "trackbar");
 	int basel = getTrackbarPos("baselane", "trackbar");
 	int high = getTrackbarPos("hight", "trackbar");
 	double fps = cap.get(CAP_PROP_FPS);
 	double frame = cap.get(CAP_PROP_POS_MSEC);
 	
 	int x1= 640-topl/2;
 	int x2 = 640+topl/2;
 	int x3 = 640-basel/2;
 	int x4 = 640+basel/2;
 	int y1 = 710;
 	int y2 = y1-high;
 	
 	Point2f v1[4];
 	v1[0] = Point(x1,y2);
 	v1[1] = Point(x2,y2);
 	v1[2] = Point(x3,y1);
 	v1[3] = Point(x4,y1);
 
 	Point2f v2[4];
 	v2[0] = Point(0,0);
 	v2[1] = Point(640,0);
 	v2[2] = Point(0,480);
 	v2[3] = Point(640,480);
 	
 	Mat video2 = video.clone();
 	line(video2,v1[0],v1[1],Scalar(0,255,0),4);
 	line(video2,v1[2],v1[3],Scalar(0,255,0),4);
 	line(video2,v1[1],v1[3],Scalar(0,255,0),4);
 	line(video2,v1[0],v1[2],Scalar(0,255,0),4);
 	char text[100];
 	char text1[100];
 	sprintf(text, "fps = %f ", fps);
 	sprintf(text1, "frame = %f ", frame);
 	putText(video2,text,Point(100,100),FONT_HERSHEY_COMPLEX, 1 ,Scalar(0,255,0), 3, 3 );
 	putText(video2,text1,Point(100,150),FONT_HERSHEY_COMPLEX, 1 ,Scalar(0,255,0), 3, 3 ); 
 	
 	Mat transMatrix = getPerspectiveTransform(v1,v2);
 	Mat video1(480,640,CV_8UC3);
 	warpPerspective(video,video1,transMatrix,video1.size());
 	
 	


 imshow("video", video2);
 imshow("video2",video1);
 

 
 resizeWindow("video",800,800);


 char c = (char)waitKey(25);
	if(c==27)
	break; 
}

	
	destroyAllWindows();

 return 0;
}
