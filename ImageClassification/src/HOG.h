/*
 * HOG.h
 *
 *  Created on: Dec 31, 2018
 *      Author: hossam
 */

#ifndef SRC_HOG_H_
#define SRC_HOG_H_
#include "Data.h"
#include<iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class HOG: public Data{
public:
	HOGDescriptor hog_detector;
	Mat train_feats;
	Mat test_feats;
	HOG(Size wsize,Size blockSize,Size blockStride,Size cellSize,int bins,String s,bool _fixed_size,Size _ImSize);
	virtual ~HOG();
	void computeHOG();
};

#endif /* SRC_HOG_H_ */
