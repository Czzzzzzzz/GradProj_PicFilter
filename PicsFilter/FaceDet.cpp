#include "FaceDet.h"

FaceDet::FaceDet()
{
	string xmlPath = "D:\\cz\\resource\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
	//string xmlPath = "D:\\cz\\resource\\opencv\\build\\share\\OpenCV\\haarcascades\\haarcascade_frontalface_alt.xml";
	if (!_ccf.load(xmlPath))
	{
		cout << "xml cannot be loaded";
	}

}

vector<Rect> FaceDet::detect(Mat img_)
{
	vector<Rect> faces;
	Mat gray;
	cvtColor(img_, gray, CV_BGR2GRAY);
	equalizeHist(gray, gray);

	_ccf.detectMultiScale(gray, faces, 1.1, 3, 0, Size(100, 100), Size(400, 400));
	return faces;
}

void FaceDet::clipFace(string dirPath_,string storePath_)
{
	vector<string> names;
	getFileNames(dirPath_, names);
	cout << names.size() << endl;

	int index = 1;

	for (int i = 0; i < names.size(); i++)
	{
		cout << i << " " << names.at(i) << endl;

		Mat img = imread(names.at(i));
		vector<Rect> faces;
		try{
			faces = detect(img);
		}
		catch (Exception e)
		{
			continue;
		};

		for (vector<Rect>::const_iterator iter = faces.begin(); iter != faces.end(); iter++)
		{
			
			Rect r = scaleRect(*iter, 1.2, 1.7);

			if (r.x < 0)
			{
				r.x = 0;
			}
			if (r.y < 0)
			{
				r.y = 0;
			}
			if (r.x + r.width > img.size().width)
			{
				r.width = img.size().width - r.x;
			}
			if (r.y + r.height > img.size().height)
			{
				r.height = img.size().height - r.y;
			}
			
			//rectangle(img, r, Scalar(0, 0, 255), 2, 8); //画出脸部矩形
			//imshow("faces", img);

			Mat clip_img = img(r);
			string path = storePath_ + num2str(index) + ".jpg";
			imwrite(path, clip_img);

			index++;
		}
		
	}

}

// scale the rectangle by the center of it.
Rect FaceDet::scaleRect(Rect rect, float scale_x, float scale_y)
{
	Rect dst;
	dst.x = rect.x - (scale_x - 1) * rect.width / 2;
	dst.y = rect.y - (scale_y - 1) * rect.height / 2;
	dst.width = rect.width * scale_x;
	dst.height = rect.height * scale_y;
	
	//Rect r = dst & rect;
	//return r;

	return dst;
}

/*
this function cannot be executed in Win64.
*/
void FaceDet::getFileNames(string dirPath_, vector<string>& nameList_)
{	
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(dirPath_).append("\\*").c_str(), &fileinfo)) != -1)
	{
		
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFileNames(p.assign(dirPath_).append("\\").append(fileinfo.name), nameList_);
			}
			else
			{
				nameList_.push_back(p.assign(dirPath_).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

string FaceDet::num2str(int n)
{
	char s[10];
	sprintf(s, "%d", n);
	string str(s);
	return str;
}