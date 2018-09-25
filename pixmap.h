#ifndef PIXMAP_H
#define PIXMAP_H

struct Pixel{
	unsigned char red_;
	unsigned char green_;
	unsigned char blue_;
	Pixel(){
		red_=green_=blue_=0;
	}
};

class PixMap{
	Pixel** image_;
	int width_;
	int height_;
	char header_[4][100];
	void clear();
public:

	PixMap(const char* fname);
	PixMap();
	void read(const char* fname);
	void write(const char* fname);
	const Pixel& getPixel(int x,int y){
		return image_[y][x];
	}
	void setPixel(const Pixel& p,int x, int y){
		image_[y][x]=p;
	}
	int width() const{return width_;}
	int height() const{return height_;}
		~PixMap();
};
bool operator==(const Pixel& left, const Pixel& right);
bool operator!=(const Pixel& left, const Pixel& right);
#endif
