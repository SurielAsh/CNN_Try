//
// Created by nagi on 19-3-2.
//

#ifndef CNNTRY_IMAGE_PROCESSING_H
#define CNNTRY_IMAGE_PROCESSING_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "toolbox.h"
using std::vector;
using namespace cv;

vector<vector<double>> getimg_grayscale(char *path)
{
	Mat image = imread(path, 0);
	vector<vector<double>> target;
	if(image.empty())
	{
		fprintf(stderr, "Can not load image %s\n", path);
	}
	int w = image.cols;
	int h = image.rows;
	w>h ? vini(target,w) : vini(target,h);
	Mat_<uchar>::iterator it = image.begin<uchar>();
	Mat_<uchar>::iterator itend = image.end<uchar>();
	for(int x=0;x<w;x++)
	{
		for(int y=0;y<h;y++)
		{
			double k=*(it + y * w + x);
			target[x][y] = k;
		}
	}
	return target;
}




#endif //CNNTRY_IMAGE_PROCESSING_H
