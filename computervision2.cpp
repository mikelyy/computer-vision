#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.cpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int myMax(int a, int b, int c);
int myMin(int a, int b, int c);
void mySkinDetect(Mat& src, Mat& dst);
void myFrameDifferencing(Mat& prev, Mat& curr, Mat& dst);
void myMotionEnergy(vector<Mat> mh, Mat& dst);

int main()
{
VideoCapture cap(0);

if(!cap.isOpened())
{
	count << "Cannot open the video cam" << endl;
	return -1;
}

Mat frame0;

bool bSuccess0 = cap.read(frame0);

if(!bSuccess0)
{
	count << "Cannot read a frame from video stream" << end;
}

nameWindow("MyVideo0", WINDOW_AUTOSIZE);
imshow("MyVideo0", frame0);

namedWindow("Skin", WINDOW_AUTOSIZE);
namedWindow("Contour", WINDOW_AUTOSIZE);
namedWindow("Gesture", WINDOW_AUTOSIZE);

vector<Mat> MotionHistory;
Mat MH1, MH2, MH3;
MH1=Mat::zeros(frame0.rows, frame0.cols, CV_8UC1);
MH2=MH1.clone();
MH3=MH1.clone();
MotionHistory.push_back(MH1);
MotionHistory.push_back(MH2);
MotionHistory.push_back(MH3);

    
    
while(1)
{
	Mat frame;
        bool bSuccess=cap.read(frame);

	if (!bSuccess)
{
	cout << "Cannot read a frame from video stream" << endl;
	break;
}

    
    
Mat frameDest;
frameDest = Mat::zeros(frame.rows, frame.cols, CV_8UC1);
Mat skinDest;
skinDest=Mat::zeros(frame.rows,frame.cols,CV_8UC1);
mySkinDetect(frame,skinDest);
imshow("Skin", skinDest);


myFrameDifferencing(frame0,frame, skinDest);
imshow("MyVideo",skinDest);

myMotionHistory.erase(myMotionHistory.begin());
### delete the initial state
myMotionHistory.push_back(frameDest);
### get frameDest from the upper row
Mat myMh = Mat::zeros(frame0.rows,frame0.cols,CV_8UC1);
    
myMotionEnergy(MotionHistory, myMh);
imshow("MyVideoMh",myMh);
frame0 = frame;
    

for (int s=0; s<myMh.rows; s++){
    for (int r=0; r<myMh.cols; r++){
        int num=0;
        if (myMh.at<uchar>(s,r) == 255){
            num += 1;
        }
        if (num>300){
            putText(frame0, "Vertically Waving Hand", Point(100,100), FONT_HERSHEY_SIMPLE, 2, Scalar(255,255,255));
            ### FONT_HERSHEY_SIMPLE could be changed
            break;
        }
    }
    
if (waitKey(30)==27){
    cout << "esc key is pressed by user" <<endl;
    break;
}
}
    cap.release();
    return 0;
}


int myMax(int a, int b, int c)
{
	int m=a;
	(void)((m<b) && (m=b));
	(void)((m<c) && (m=c));
	return m;
}

int myMin(int a, int b, int c)
{
	int m=a;
	(void)((m>b) && (m=b));
	(void)((m>c) && (m=c));
	return m;
}

void mySkinDetect(Mat& src, Mat& dst)
{
	for (int i=0; i<src.rows; i++){
		for(int j=0; j<src.cols; k++){
			Vec3b intensity=src.at<Vec3b>(i, j);
			int B = intensity[0]; int G = intensity[1]; int R = intensity[2];
			if ((R>95 && G>40 && B>20) && (myMax(R,G,B)-myMin(R,G,B)>15)&&(abs(R-G)>15)&&(R>G)&&(R>B)){
				dst.at<uchar>(i,j) =255;
			}
		}
	}
}

void myFrameDifferencing(Mat& prev, Mat& curr, Mat& dst)
{
	absdiff(prev, curr, dst);
	Mat ab = dst.clone();
	cvtColor(dst, ab, CV_BGR2GRAY);
	dst=ab>50;
	Vec3b intensity=dst.at<Vec3b>(100,100);
}

void myMotionEnergy(vector<Mat> mh, Mat& dst)
{
	Mat mh0=mh[0];
	Mat mh1=mh[1];
	Mat mh2=mh[2];

	for(int i=0; i<dst.rows; i++){
		for (int j=0; j<dst.cols; j++){
			if (mh0.at<uchar>(i,j) == 255 || mh1.at<uchar>(i,j) == 255 || mh2.at<uchar>()i,j) == 255){
				dst.at<uchar>(i,j) =255;
			}
		}
	}
}
    

###Done!###


    
    
    
