#include "Camera.h"
#include <ostream>

bool Camera::init() {
	nPixels = 1;
	Pixel* screen = Pixel[nPixels];
	std::cout << "camera initialized successfully"<< std::endl;
}

bool Camera::print(const char* ofn){
	std::cout << "printed on file " << ofn << std::endl;
}

