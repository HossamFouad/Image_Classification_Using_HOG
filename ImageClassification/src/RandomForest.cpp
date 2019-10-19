/*
 * RandomForest.cpp
 *
 *  Created on: Dec 31, 2018
 *      Author: hossam
 */

#include "RandomForest.h"

RandomForest::RandomForest(float randomSampleRatio,int Trees,int folds ,int categories
		,int depth ,int sample,Size wsize,Size blockSize,Size blockStride
		,Size cellSize,int bins,String s,bool _fixed_size,Size _ImSize):HOG( wsize, blockSize, blockStride
		,cellSize,bins,s, _fixed_size,_ImSize) {
	TreesNum=Trees;
	Ratio=randomSampleRatio;
	for(int i=0;i<TreesNum;i++){
	model.push_back(DTrees::create());
	model.back()->setCVFolds(folds); // set num cross validation folds
	model.back()->setMaxCategories( categories ); // set max number of categories
	model.back()->setMaxDepth(  depth ); // set max tree depth
	model.back()->setMinSampleCount( sample ); // set min sample coun

	}
}
void RandomForest::Train(){
	cout<<"----------------Training----------------"<<endl;
	data_set=TrainData::create(train_feats, ROW_SAMPLE, train_labels);
	for(int i=0;i<TreesNum;i++){
		data_set->setTrainTestSplitRatio(Ratio,true);
		model[i]->train(data_set);

	}
}
int RandomForest::MajorityVote(Mat& col){
	int size=col.rows;
	Mat count = Mat::zeros(cv::Size(1, TreesNum), 4);
	for(int i=0;i<size;i++){
		count.at<int>(col.at<int>(i))+=1;

	}
	double min, max;
	Point min_loc, max_loc;
	minMaxLoc(count, &min, &max, &min_loc, &max_loc);
	return max_loc.y;
}
void RandomForest::Prediction(){
	cout<<"----------------Prediction----------------"<<endl;
	Mat f;
	for(int i=0;i<TreesNum;i++){
		model[i]->predict(test_feats,f);
		predM.push_back(f.reshape(1,1));
	}
	predM.convertTo(predM, 4);

	for(int i=0;i<predM.cols;i++){
		f=predM.col(i);
		pred.push_back(this->MajorityVote(f));

	}


}
void RandomForest::accuracy(){
	cout<<"----------------Accuracy----------------"<<endl;
	acc=sum((pred==test_labels))[0]/255.0;
	acc/=test_labels.rows;
	acc*=100;
	cout<<"Prediction Accuracy= "<<acc<<"%"<<endl;
}

RandomForest::~RandomForest() {
	// TODO Auto-generated destructor stub
}

