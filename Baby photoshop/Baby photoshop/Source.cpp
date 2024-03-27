#include <iostream>
#include "Image_Class.h"
using namespace std;
void invertimage() {
	string filename,filename2;
	cin >> filename;
	Image image1(filename);
	for (int i = 0; i < image1.width; i++) {
		for (int j = 0; j < image1.height; j++) {
			for (int k = 0; k < image1.channels; k++) {
				image1(i, j, k) = 255 - image1(i, j, k);

			}

		}

	}
	cin >> filename2;
	image1.saveImage(filename2);
	system(filename2.c_str());
	return;
}

int main() {
	
}