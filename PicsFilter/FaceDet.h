#ifndef FACE_DET_H
#define FACE_DET_H

#include<iostream>
#include<fstream>

#include "opencv2\opencv.hpp"
#include "stdio.h"
#include "stdlib.h"
#include "io.h"

using namespace std;
using namespace cv;

class FaceDet
{
private:
	CascadeClassifier _ccf;
	
	void getFileNames(string dirPath_, vector<string>& nameList_);	
	Rect scaleRect(Rect rect, float scale_x, float scale_y);
	string num2str(int n);
public:
	FaceDet();
	vector<Rect> detect(Mat img_);
	void clipFace(string dirPath_, string storePath_);

};

#endif