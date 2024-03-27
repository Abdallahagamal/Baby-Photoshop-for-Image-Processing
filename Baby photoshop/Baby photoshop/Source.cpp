#include <iostream>
#include "Image_Class.h"
using namespace std;
Image image;

void invert_image(Image&image) {
        cout << "Please enter image name to apply invert filter: ";
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < image.channels; k++) {
                    image(i, j, k) = 255 - image(i, j, k);

                }

            }

        }
	return;
}
void Gray_Scale(Image& image) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                int avg = 0;
                for (int k = 0; k < 3; ++k) {
                    avg += image(i, j, k);
                }
                avg = avg / 3;
                for (int k = 0; k < 3; ++k) {
                    image(i, j, k) = avg;
                }

            }
        }
}
void Black_White(Image& image) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                int avg = 0;
                for (int k = 0; k < 3; ++k) {
                    avg += image(i, j, k);
                }
                avg = avg / 3;
                for (int k = 0; k < 3; ++k) {
                    if (avg <= 125) {
                        image(i, j, k) = 0;
                    }
                    else {
                        image(i, j, k) = 255;
                    }
                }
            }
        }
}
void Darken_Image(Image& image) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image(i, j, k) -= (image(i, j, k) / 2);
                }
            }
        }
}
void Lighten_Image(Image& image) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int pixelValue = image.getPixel(i, j, k);
                    int newPixelValue = pixelValue * 1.5;
                    if (newPixelValue > 255)
                    {
                        newPixelValue = 255;
                    }
                    image.setPixel(i, j, k, newPixelValue);
                }
            }
        }
}
void save() {
    string filename2;
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename2;
    image.saveImage(filename2);
    cout << "Photo Has been save successfully";
    system(filename2.c_str());
}
void load(Image&image) {
    string filename;
    while (true) {
        try {
            cin >> filename;
            image.loadNewImage(filename);
            break;
        }
        catch (...) {
            cout << "ALERT: Please Enter right name for the image and make sure that the image with the source file. " << endl;
            cout << "Enter the name of image with format: ";
        }
    }

}
int main() {
    cout << "=============== Welcome to Baby-Photoshop ===============\nPlease load the image, enter name of the image: ";
    load(image);
    bool x = false;
    string choice,choice2 ;
    while (true){
       cout << "\n{1}load new image\n{2} GrayScale \n{3} Black And White \n{4} Invert Image \n{5} Lighten Image Or Darken Image \n{6}gad \n{7}Save the image \n{8}Exit \n";
       cout << "enter your choice : " ;
       cin >> choice ;
        if (choice=="1") {
            if (x == false) {
                cout << "Please load the new image, enter name of the image: ";
                load(image);
            }
            else {
               cout << "\nDo you want to save the current image before loading a new one?\n1)Yes\n2)No\nEnter your choice: ";
               while (true) {
                   cin >> choice2;
                   if (choice2 == "1") {
                       save();
                       cout << "Please load the new image, enter name of the image: ";
                       load(image);
                       break;
                   }
                   else if (choice2 == "2") {
                       cout << "Please load the new image, enter name of the image: ";
                       load(image);
                       break;
                   }
                   else {
                       cout << "Please enter right choice: ";
                   }
               }
            }  

        }
        else if (choice=="2"){
            Gray_Scale(image);
            x = true;
        }
        else if (choice=="3"){
            Black_White(image);
            x = true;
        }
        else if (choice=="4"){
            invert_image(image);
            x = true;
        }
        else if (choice=="5"){
            cout << "{1} Lighten Image \n" ;
            cout << "{2} Darken Image \n" ;
            string choice2 ;
            while (true){
                cout << "enter your choice2 : " ;
                cin >> choice2 ;
                if (choice2 == "1"){
                    Lighten_Image(image);
                    x = true;
                    return 0 ;
                }
                else if (choice2 == "2"){
                    Darken_Image(image);
                    x = true;
                    return 0 ;
                }
            }
            
        }
        else if (choice=="6"){
            //
            break;
        }
        else if (choice == "7") {
            save();
            x = false;
        }
        else if (choice == "8") {
            if (x == true) {
                cout << "Do you want to save the current image before exit?\n1)yes\n2)no\nEnter your choice: ";
                cin >> choice2;
                if (choice2=="1") {
                    save();
                    
                }
                else if (choice2=="2") {
                    cout << "Thanks for using app";
                    break;
                }
            }
            else {
                cout << "Thanks for using app";
                break;
            }
        }
        else{
            cout << "Wrong choice, try again : " ;
        }  
    } 
}