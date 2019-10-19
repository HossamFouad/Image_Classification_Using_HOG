// Project 5
// Authers: Hossam, Ferjad, Borja

#include<iostream>
#include <string>
#include "Data.h"
#include "RandomForest.h"
#include "HOG.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
using namespace std;
using namespace cv;
String path="/home/hossam/eclipse-workspace/ImageClassification/task2/";
//HOG features
Size WinSize= Size(128,128); //Window size of HOG
Size BlockSize= Size(32,32); //block size
Size BlockStride= Size(16,16); // stride
Size CellSize= Size(16,16); // cell size
int Bins= 9; // angle bins
bool fixed_size=true; // fix all image size
Size ImSize= Size(128,128); // size of all images if being fixed
// Random Forest
int TreesNum=10; // Decision Trees Number
float randSampleRatio=0.9; // Ratio of random sub-sample
int foldNum=1;// cross validation folds
int catNum=6; // No. of classes
int depthNum=10; // Decision Trees depth
int samplesNum=10; //  min number of samples in a node

int main(){
	//config Config(path);

	RandomForest RF(randSampleRatio,TreesNum,foldNum,catNum,depthNum,samplesNum,WinSize,BlockSize,BlockStride,CellSize,Bins,path,fixed_size,ImSize);
	RF.DataRead();
	RF.computeHOG();
	RF.Train();
	RF.Prediction();
	RF.accuracy();

	return 0;
}
