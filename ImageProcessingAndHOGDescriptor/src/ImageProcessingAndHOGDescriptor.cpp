/*
 * ImageProcessingAndHOGDescriptor.cpp
 *
 *  Created on: Dec 29, 2018
 *      Author: Hossam Abdelhamid, Ferjad Naeem, Borja
 */

#include <opencv2/opencv.hpp>
#include<iostream>
#include <string>
#include "HOG.h"

using namespace std;
using namespace cv;

// Data path
String path="data/task1/";
String image="obj1000.jpg";
// HOG Descriptor Parameters
Size WinSize= Size(128,128);
Size BlockSize= Size(32,32);
Size BlockStride= Size(16,16);
Size CellSize= Size(16,16);
int Bins= 9;
// Resize
float xfactor=2;
float yfactor=2;
// Rotate
float angle=60;
float scale=1;
//Flip
float x=0;
int main()
{ //Read Image
	Mat Original,GrayScale,Resized,Rotated,Flip;
	vector<float> featsOriginal,featsGrayScale,featsResized,featsRotated,featsFlip;
	Original = imread(path+image);
	resize(Original, Original,Size(128,128),0,0);
  HOG hog_feat(Original);
  //Original image HOG
  hog_feat.computeHOG(Original,featsOriginal,WinSize,BlockSize,BlockStride,CellSize);
  hog_feat.visualizeHOG(Original,featsOriginal,path+"Original.jpg");
  //GrayScale image HOG
  hog_feat.GrayScale(GrayScale);
  hog_feat.computeHOG(GrayScale,featsGrayScale,WinSize,BlockSize,BlockStride,CellSize);
  hog_feat.visualizeHOG(GrayScale,featsGrayScale,path+"GrayScale.jpg");

  //Resized image HOG
  hog_feat.Resized(Resized,xfactor,yfactor);
  hog_feat.computeHOG(Resized,featsResized,Size(xfactor*WinSize.width,yfactor*WinSize.height),Size(xfactor*BlockSize.width,yfactor*BlockSize.height),Size(xfactor*BlockStride.width,yfactor*BlockStride.height),Size(xfactor*CellSize.width,yfactor*CellSize.height));
  hog_feat.visualizeHOG(Resized,featsResized,path+"Resized.jpg");
  //Rotated image HOG
  hog_feat.Rotated(Rotated,angle,scale);
  hog_feat.computeHOG(Rotated,featsRotated,WinSize,BlockSize,BlockStride,CellSize);
  hog_feat.visualizeHOG(Rotated,featsRotated,path+"Rotated.jpg");
  //Flip image HOG
  hog_feat.Flip(Flip,x);
  hog_feat.computeHOG(Flip,featsFlip,WinSize,BlockSize,BlockStride,CellSize);
  hog_feat.visualizeHOG(Flip,featsFlip,path+"Flip.jpg");
//  waitKey(0);
  return 0;
}
