#include "pixmap.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
#define VERBOSE 0

/*this tester will test your fill function.
  You will need the following image files (found in course repo).
  You can pull from repo then copy over to your folder or
  you can run the submitter once and it will copy all the files you need 
  into your folder.
	
  To compile:

  c++ a1q3.cpp pixmap.cpp a1q3main.cpp

  Run the program.  If you have an error and want to see what your image 
  looks like, switch VERBOSE to 1

  If you want to see results of your fill function even when you dont have
  error, set VERBOSE to 2

  the output will be called yourresult#.ppm. (# is replaced with test number)

  */
bool comparePixMap(PixMap& img1,PixMap& img2);
bool fill(PixMap& image, const Pixel& fillColour, int x, int y);

int main(int argc, char* argv[]){
	PixMap image("a1q3img1.ppm");
	PixMap image2("a1q3img2.ppm");
	PixMap correct;
	int numPassed=0;

	Pixel fillColours[7];

	int coords[7][2]={{302,191}, {117,282}, {305,170}, {0,0},
						{247,238}, {307,177}, {639,399}};
	fillColours[0].red_=255;
	fillColours[1].green_=255;
	fillColours[2].blue_=255;
	fillColours[3].blue_=255;
	fillColours[3].red_=255;
	fillColours[4]=fillColours[3];
	fillColours[5].blue_=255;
	fillColours[6]=fillColours[5];
	char fname[20]="a1q3a.ppm";

	for(int i=0;i<4;i++){
		fname[4]='a'+i;
		correct.read(fname);
		fill(image,fillColours[i],coords[i][0],coords[i][1]);
		if(comparePixMap(image,correct)){
			cout << "Test #" << i+1 << " passed." << endl;
			numPassed++;
			#if VERBOSE==2
			char outfilename[20]="yourresult1.ppm";
			outfilename[10]='0'+(i+1);
			image.write(outfilename);
			#endif
		}
		else{
			cout << "Test #" << i+1 << " failed" << endl;
			#if VERBOSE>=1
			char outfilename[20]="yourresult1.ppm";
			outfilename[10]='0'+(i+1);
			image.write(outfilename);
			#endif
		}
	}

	for(int i=4;i<7;i++){
		fname[4]='a'+i;
		correct.read(fname);
		fill(image2,fillColours[i],coords[i][0],coords[i][1]);
		if(comparePixMap(image2,correct)){
			cout << "Test #" << i+1 << " passed." << endl;
			numPassed++;
			#if VERBOSE==2
			char outfilename[20]="yourresult1.ppm";
			outfilename[10]='0'+(i+1);
			image.write(outfilename);
			#endif

		}
		else{
			cout << "Test #" << i+1 << " failed" << endl;
			#if VERBOSE>=1
			char outfilename[20]="yourresult1.ppm";
			outfilename[10]='0'+(i+1);
			image2.write(outfilename);
			#endif
		}
	}
	if(numPassed == 7){
		cout << "7/7 tests passed for A1 Part 3" << endl;		
		cout << "Your program has passed testing" << endl;
	}
	else{
		cout << numPassed << "/7 tests passed for A1 Part 3" << endl;
		cout << "Looks like you still have some work to do" << endl;
	}
	return 0;
}
bool comparePixMap(PixMap& img1,PixMap& img2){
	bool rc=true;
	if(img1.height() != img2.height() || img1.width() != img2.width()){
		rc=false;
	}
	for(int i=0;rc && i<img1.width();i++){
		for(int j=0; rc && j < img2.height();j++){
			if(img1.getPixel(i,j) != img2.getPixel(i,j)){
				rc=false;
			}
		}
	}
	return rc;
}
