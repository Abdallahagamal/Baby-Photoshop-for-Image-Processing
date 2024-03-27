#include <iostream>
#include "Image_Class.h"
using namespace std;
Image image;
string filename;

void invert_image(Image&image) {
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
   
    string choice;
    cout << "1- save a new file \n2-save in current file\n";
    cout << "enter your choice : ";
    while (true)
    {
        cin >> choice;
        if (choice == "1")
        {
            cout << "Pls enter image name to store new image\n";
            cout << "and specify extension .jpg, .bmp, .png, .tga: ";
            cin >> filename2;
            image.saveImage(filename2);
            cout << "Photo Has been save successfully";
            system(filename2.c_str());
            break;

        }
        else if (choice == "2")
        {
            image.saveImage(filename);
            cout << "Photo Has been save successfully";
            system(filename.c_str());
            break;
        }
        else cout << "wrong choice , try again";


    }
    
}
void load(Image&image) {
   
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
void filter_55(Image&image) {
    string filename;
    cout << "Please choose from 1 or 2\n1-flip horizontally\n2-flip vertically\n";
    int n;
    cin >> n;

    if (n == 1) {
        cout << "Please enter the name of the image to flip horizontally: ";
        cin >> filename;

        int width = image.width;
        int height = image.height;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width / 2; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    swap(image(j, i, k), image(width - j - 1, i, k));
                }
            }
        }

        
        
    }
    else if (n == 2) {
        int width = image.width;
        int height = image.height;

        for (int i = 0; i < height / 2; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    swap(image(j, i, k), image(j, height - i - 1, k));
                }
            }
        }

    }
}

int main() {
    cout << "=============== Welcome to Baby-Photoshop ===============\nPlease load the image, enter name of the image: ";
    load(image);
    bool x = false;
    string choice,choice2 ;
    while (true){
       cout << "\n{1} load new image\n{2} GrayScale \n{3} Black And White \n{4} Invert Image \n{5} Lighten Image Or Darken Image \n{6} Flip Image \n{7} Save the image\n{8} Exit \n";
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
                    break;
                    
                }
                else if (choice2 == "2"){
                    Darken_Image(image);
                    x = true;
                    break;
                  
                }
            }
            
        }
        else if (choice=="6"){
            filter_55(image);
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
                    break;
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