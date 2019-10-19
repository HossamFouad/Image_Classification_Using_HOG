/*
 * RandomForest.h
 *
 *  Created on: Dec 31, 2018
 *      Author: hossam
 */

#ifndef SRC_RANDOMFOREST_H_
#define SRC_RANDOMFOREST_H_
#include "HOG.h"
#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
using namespace std;
using namespace cv;
using namespace cv::ml;


class RandomForest: public HOG {
public:
	Mat pred,predM;
	Mat float_labels;
	float acc;
	float Ratio;
	int TreesNum;
	vector<Ptr<DTrees>> model;
	Ptr<TrainData> data_set;
	RandomForest(float randomSampleRatio,int Trees,int folds ,int categories ,int depth ,int sample,Size wsize,Size blockSize,Size blockStride,Size cellSize,int bins,String s,bool _fixed_size,Size _ImSize);
	int MajorityVote(Mat& col);
	virtual ~RandomForest();
	void Train();
	void Prediction();
	void accuracy();
};

#endif /* SRC_RANDOMFOREST_H_ */
