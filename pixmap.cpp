#include "pixmap.h"
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

PixMap::PixMap(){
	width_=height_=0;
	image_=NULL;
}
PixMap::PixMap(const char* fname){
	image_=NULL;
	read(fname);
}
void PixMap::write(const char* fname){

	if(image_!=NULL){
		ofstream fs(fname,ios::out|ios::binary);
		for(int i=0;i<4;i++){
			fs << header_[i] << endl;
		}
		for(int i=0;i<height_;i++){
			fs.write((char*)image_[i],3*width_);
		}
		fs.close();
	}	
}
void PixMap::read(const char* fname){
	if(image_!=NULL){
		clear();
	}
	fstream fs(fname,ios::in|ios::binary);	
	for(int i=0;i<4;i++){
		fs.getline(header_[i],99,'\n');
	}
	sscanf(header_[2],"%d %d",&width_,&height_);
	image_=new Pixel*[height_];
	for(int i=0;i<height_;i++){
		image_[i]=new Pixel[width_];
	}
	for(int i=0;i<height_;i++){
		fs.read((char*)image_[i],3*width_);
	}	
	fs.close();
}
void PixMap::clear(){
	for(int i=0;i<height_;i++){
		delete [] image_[i];
	}
	delete [] image_;
	image_=NULL;
}

PixMap::~PixMap(){
	clear();
}

bool operator==(const Pixel& left, const Pixel& right){
	bool rc=false;
	if(left.red_ == right.red_ && left.green_==right.green_ && 
		left.blue_==right.blue_){
		rc=true;
	}
	return rc;
}

bool operator!=(const Pixel& left, const Pixel& right){
	bool rc=true;
	if(left.red_ == right.red_ && left.green_==right.green_ && 
		left.blue_==right.blue_){
		rc=false;
	}
	return rc;
}
