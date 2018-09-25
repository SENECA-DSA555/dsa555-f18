#include "pixmap.h"
/*this fill function is currently a stub (function that compiles and operates
  in some expected manner but doesn't actually work).  It only fills in the top left 10x10 pixel
area with the fill colour passed in and its return value is always true
*/
bool fill(PixMap& image,const Pixel& fillColour,int x, int y){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			image.setPixel(fillColour,i,j);
		}
	}
	return true;
}
