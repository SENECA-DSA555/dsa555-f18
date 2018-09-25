#include "pixmap.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
/*this tester will call the fill function once and
  create an output file.  You can look at the result using
  a program like gimp
	
  to use the program, you must supply the name of the input file
  the name of the output file and the fill location (x, y coordinate).  The fill colour
  will be red (255,0,0).  If you want a different colour you will
  need to modify the code below

  Write your fill() function in a1q1.cpp

  To compile:

  c++ a1q1.cpp pixmap.cpp a1q1simpletest.cpp

  */
bool fill(PixMap& image,const Pixel& fillColour,int x, int y);

int main(int argc, char* argv[]){
	if(argc!=5){
		cout << "usage: a.out <inputfilename> <outputfilename> <x> <y>" << endl;
	}
	else{
		int x = atoi(argv[3]);
		int y = atoi(argv[4]);
		PixMap image(argv[1]);
		Pixel red;
		red.red_=255;
		fill(image,red,x,y);
		image.write(argv[2]);
	}
	return 0;
}