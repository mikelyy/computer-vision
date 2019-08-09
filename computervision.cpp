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

    
    
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;

findCounters(frameDest, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
cout << "The number of contours detected is: " << contours.size() << endl;

vector<vector<int>>hullsI(contours.size());
vector<vector<Point>>hullsP(contours.size());
vector<vector<Vec4i>>defects(contours.size());

for (int i=0; i<contours.size(); ++i)
{
	convexHull(Mat(contours[i]),hullsI[i],false);
        convexHull(Mat(contours[i]),hullsI[i],false);
	convexityDefects(contours[i],hullsI[i],defects[i]);
}

Mat contour_output = Mat::zeros(skinDest.size(),CV_8UC3);

int maxsize=0;
int maxindex=0;


###
int area;
###

Rect bound_rec;
for (int i=0; i<contours.size();i++)
{
	double area = contourArea(contours[i]);
	if (area>maxsize){
		maxsize=area;
		maxindex=i;
		bound_rec=boundingRect(contours[i]);
}
}

Mat frame1=frame;

drawContours(contour_output, contours, maxind, Scalar(255,0,0), CV_FILLED, 8, hierarchy);
drawContours(contour_output, contours, maxind, Scalar(0,0,255), 2, 8 hierarchy);
drawContours(frame1, contours, maxind, Scalar(0,0,255), 2,8, hierarchy);
rectangle(contour_output, bound_rec, Scalar(0,255,0), 1, 8, 0);
rectangle(frame1, bound_rec, Scalar(255,0,0), 1, 8, 0);

imshow("Contour", contour_output);

if (contours.size()>0)
{
	drawContours(frame1, contours, maxind, Scalar(0,0,255), 2, 8, hierarchy);
	drawContours(frame1, hullsP, maxind, Scalar(0,255,0), 2, 8, hierarcy);
}

vector<Point> maxCounter=counters[maxindex];
float radius;
Point2f handcenter;

minEnclodingCircle(maxContour, handcenter, radius)
circle(frame1, handcenter, 10, Scalar(0,0,255), 2, 8);

int countfingers=0;

### why we need maxDefects here?????
vector<Vec4i> maxDefects = defects[max_index];

for (int i=0; i<maxDefects.size(); i++){
    int startIndx = maxDefects[i].val[0];
 
    Point finerTip(maxContour[startIndx]);
    int depthh = (int) (maxDefects[i].val[3])/256;
    
    if(depth > 10 && fingerTip.y<handCenter.y){
        circle(frame1, fingerTip, 4, Scalar(125, 255,255), 2);
        countFingers++;
    }
}

if (countFingers == 0){
    putText(frame1, "Fist", Point(50, 100), 2, 4, Scalar(255,0,0),3,8);
}
else{
    if (countFingers == 5){
        putText(frame1, "High Five", Point(50,100), 2, 4, Scalar(255,0,0),3,8);
    }
    else{
        putText(frame1, "V Yeah", Point(50,100), 2, 4, Scalar(255,0,0),3,8);
    }
}
    
namedWindow("fingerVideo", CV_WINDOW_AUTOSIZE);
imshow("fingerVideo", frame1);

if (waitKey(30) == 27){
    cout << "esc key is pressed by user" << endl;
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







