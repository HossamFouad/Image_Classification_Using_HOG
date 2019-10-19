/*
 * Data.cpp
 *
 *  Created on: Dec 31, 2018
 *      Author: hossam
 */

#include "Data.h"

Data::Data(String s,bool _fixed_size,Size _ImSize){
	// TODO Auto-generated constructor stub
	data_path=s; //data path
	 fixed_size=_fixed_size;
	 ImSize=_ImSize;
}
 void Data::DataRead(int color){
	 cout<<"----------------Reading Data----------------"<<endl;

	 	 vector<String> fn;
	 	glob(data_path,fn,true);
	 	Mat img;
	 	size_t Pos;
	 	String substr,str;
	 	int label;
	 	for(int i=0;i<fn.size();i++)
	 	{if(fn[i].find(".jpg") ==string::npos)
	 		{continue;}
	 	img = imread(fn[i],color);
	 	if(fixed_size){
	 	resize(img, img,ImSize,0,0);
	 	}
	 	Pos=fn[i].find_last_of("/");
	 	str=fn[i].substr(0,Pos);
		Pos=str.find_last_of("/");
		substr	=str.substr(Pos+1);
		label=static_cast<int>(substr[1])-48;
		str=str.substr(0,Pos);
		Pos=str.find_last_of("/");
		substr	=str.substr(Pos+1);
		if(substr=="train"){
		train_images.push_back(img.clone());
		train_labels.push_back(label);
		}
		else{
		test_images.push_back(img.clone());
		test_labels.push_back(label);
		}

	}
 }
Data::~Data() {
	// TODO Auto-generated destructor stub
}
