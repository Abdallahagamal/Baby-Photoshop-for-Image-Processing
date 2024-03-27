#include <iostream>
#include "Image_Class.h"
using namespace std;
void menu1(){
    cout << "=========== welcome ===========\n{1} GrayScale \n{2} Black And White \n{3} Invert Image \n{4} Lighten Image Or Darken Image \n5}welcome \n" ;
}
void invert_image() {
	string filename,filename2;
    cout << "Pls enter colored image name to turn to Gray scale: ";
	cin >> filename;
	Image image1(filename);
	for (int i = 0; i < image1.width; i++) {
		for (int j = 0; j < image1.height; j++) {
			for (int k = 0; k < image1.channels; k++) {
				image1(i, j, k) = 255 - image1(i, j, k);

			}

		}

	}
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
	cin >> filename2;
	image1.saveImage(filename2);
	system(filename2.c_str());
	return;
}
void Gray_Scale() {
    string filename;
    cout << "Pls enter colored image name to turn to Gray scale: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int avg = 0 ; 
            for (int k = 0; k < 3; ++k) {
                avg+= image(i,j,k) ;
            }
            avg = avg /3 ;
            for (int k = 0; k < 3; ++k) {
                image(i,j,k) = avg ;
            }

        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);
    system(filename.c_str());
}
void Black_White() {
    string filename;
    cout << "Pls enter colored image name to turn to Gray scale: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int avg = 0 ; 
            for (int k = 0; k < 3; ++k) {
                avg+= image(i,j,k) ;
            }
            avg = avg /3 ;
            for (int k = 0; k < 3; ++k) {
                if (avg <=125){
                    image(i,j,k) = 0;
                }
                else{
                    image(i,j,k) = 255;
                }
            }
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);
    system(filename.c_str());
}
void Darken_Image() {
    string filename;
    cout << "Pls enter colored image name to turn to Darken Image: ";
    cin >> filename;

    Image image(filename);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i,j,k) -= (image(i,j,k)/2) ;
            }
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);
    system(filename.c_str());
}
void Lighten_Image() {
    string filename;
    cout << "Please enter the image name to turn it to Lighten Image: ";
    cin >> filename;

    Image image(filename);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int pixelValue = image.getPixel(i, j, k);
                int newPixelValue =  pixelValue * 1.5;
                if (newPixelValue>255)
                {
                    newPixelValue = 255 ;
                }
                image.setPixel(i, j, k, newPixelValue);
            }
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    image.saveImage(filename);
    system(filename.c_str());
}
int main() {
    menu1() ;
    string choice ;
    while (true){
       cout << "enter your choice : " ;
       cin >> choice ;
        if (choice=="1"){
            Gray_Scale();
            cout << "thanks tor using app " ;
            break;
        }
        else if (choice=="2"){
            Black_White();
            cout << "thanks tor using app " ;
            break;
        }
        else if (choice=="3"){
            invert_image();
            cout << "thanks tor using app " ;
            break;
        }
        else if (choice=="4"){
            cout << "{1} Lighten Image \n" ;
            cout << "{2} Darken Image \n" ;
            string choice2 ;
            while (true){
                cout << "enter your choice2 : " ;
                cin >> choice2 ;
                if (choice2 == "1"){
                    Lighten_Image();
                    cout << "thanks tor using app " ;
                    return 0 ;
                }
                else if (choice2 == "2"){
                    Darken_Image();
                    cout << "thanks tor using app " ;
                    return 0 ;
                }
            }
            
        }
        else if (choice=="5"){
            //
            break;
        }
        else{
            cout << "wrong choice, try again : " ;
        }  
    } 
}