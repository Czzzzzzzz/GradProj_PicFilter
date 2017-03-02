//#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"

#include "FaceDet.h"
//#include <iostream>
//#include <stdio.h>

int main()
{
	FaceDet faceDet;
	//faceDet.clipFace("D:\\cz\\graduationPro\\c\\pics_woman", "D:\\cz\\graduationPro\\c\\pics_woman_clip\\");
	faceDet.clipFace("D:\\cz\\graduationPro\\data_female\\keyword_高清女", "D:\\cz\\graduationPro\\data_female\\data_高清女\\");

	waitKey(0);
	system("pause");
	return 1;
}