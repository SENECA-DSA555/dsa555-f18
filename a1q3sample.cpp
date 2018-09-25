/*
  this file shows you how to use PixMap and access individual
  pixels, read/write the image to a file.  Make sure
  sample.ppm is in the same directory

  Individual Pixels can be compared with both == and !=

  Note, you will need to ensure the image file is in the
  current directory or program will crash.

  To compile:
  c++ pixmap.cpp a1q1sample.cpp


*/

#include "pixmap.h"
#include <iostream>
using namespace std;

int main(void){
	PixMap image1("sample.ppm");
	PixMap image2;
	PixMap image3("sample.ppm");
	Pixel red;
	red.red_=255;
	/*loop sets changes the upper left corner to red*/
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			image1.setPixel(red,i,j);
		}
	}
	//create output file.  Note sample.ppm is not changed
	//but the internally stored image in image1 is changed
	image1.write("sampleredcorner.ppm");

	//read newly created image into image2
	image2.read("sampleredcorner.ppm");
	for(int i=0;i<image1.width();i++){
		for(int j=0;j<image1.height();j++){

			//image3 is sample.ppm (unchanged) so the top left corner
			//will be different
			if(image3.getPixel(i,j)!=image2.getPixel(i,j)){
				cout << "pixel " << i << ", " << j << " is not the same"  << endl;
			}
			//image2's top left corner is red, so output should only apply
			//to top left
			if(image2.getPixel(i,j) == red){
				cout << "pixel " << i << ", " << j << " is red " << endl;
			}

		}
	}
}