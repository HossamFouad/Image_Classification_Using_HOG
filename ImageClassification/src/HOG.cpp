/*
 * HOG.cpp
 *
 *  Created on: Dec 31, 2018
 *      Author: hossam
 */

#include "HOG.h"

HOG::HOG(Size wsize,Size blockSize,Size blockStride,Size cellSize,int bins,String s,bool _fixed_size,Size _ImSize):Data(s, _fixed_size,_ImSize) {
	// TODO Auto-generated constructor stub

	hog_detector.winSize = wsize;
	hog_detector.blockSize=blockSize;
	hog_detector.blockStride=blockStride;
	hog_detector.cellSize=cellSize;
	hog_detector.nbins=bins;

}

void HOG::computeHOG(){
	cout<<"-------Extracting HOG Features--------"<<endl;
    vector<float> feats;
    Mat im;
	for(unsigned int i=0;i<train_images.size();i++){
	hog_detector.compute( train_images[i], feats,Size(8,8),Size(0,0));
	   im =Mat(feats);
	    im=im.reshape(1,1); // flatten to a single row
	    im.convertTo(im, CV_32F);     // ml needs float data
	    train_feats.push_back(im);         // append at bottom

	}
	for(unsigned int i=0;i<test_images.size();i++){
	hog_detector.compute( test_images[i], feats,Size(8,8),Size(0,0));
	   im =Mat(feats);
	    im=im.reshape(1,1); // flatten to a single row
	    im.convertTo(im, CV_32F);     // ml needs float data
	    test_feats.push_back(im);         // append at bottom

	}
    }

HOG::~HOG() {
	// TODO Auto-generated destructor stub
}

