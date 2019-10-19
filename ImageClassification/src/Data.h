/*
 * Data.h
 *
 *  Created on: Dec 31, 2018
 *      Author: hossam
 */

#ifndef SRC_DATA_H_
#define SRC_DATA_H_
#include <opencv2/opencv.hpp>
#include<iostream>
#include <string>
#include <stdio.h>
using namespace std;
using namespace cv;

class Data{
public:
	String data_path; //data path
	// HOG Descriptor Parameters

	bool fixed_size;
	Size ImSize;
	vector<Mat> train_images,test_images;
	Mat train_labels,test_labels;
	Data(String s,bool _fixed_size,Size _ImSize);
	virtual ~Data();
	void DataRead(int color=0);
};

#endif /* SRC_DATA_H_ */
