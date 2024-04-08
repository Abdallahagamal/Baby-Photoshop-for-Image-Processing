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
    cout << "1- Save a new file \n2- Save in current file\n";
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
        else cout << "wrong choice , try again\b";


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
            cout << "ALERT: Please Enter right name for the image and make sure that the image with the source file.\a " << endl;
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
void filter_colors(int&R ,int&G,int&B) {
    string choice;
    cout << "\n1) Black\n2) White\n3) Blue\n4) Red\n5) Yellow\n6) Green\nChoose the color of frame: ";
    while (true) {
        cin >> choice;
        if (choice == "1") {
            R = 0;
            G = 0;
            B = 0;
            break;
        }
        else if (choice == "2") {
            R = 255;
            G = 255;
            B = 255;
            break;
        }
        else if (choice == "3") {
            R = 16;
            G = 17;
            B = 180;
            break;
        }
        else if (choice == "4") {
            R = 188;
            G = 0;
            B = 0;
            break;
        }
        else if (choice == "5") {
            R = 252;
            G = 211;
            B = 19;
            break;
        }
        else if (choice == "6") {
            R = 43;
            G = 152;
            B = 35;
            break;
        }
        else {
            cout << "\nPlease choose right Choice:\a ";
        }
    }
}
void filter_simpleframe(Image&image,int R,int G,int B) {
    //Draw The left side
    for (int i = 0; i < image.width/50; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = R;
                image(i, j, 1) = G;
                image(i, j, 2) = B;
            }
        }
    }
   
    //Draw The upper side
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height/30; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = R;
                image(i, j, 1) = G;
                image(i, j, 2) = B;
            }
        }
    }
    //Draw The down side
    for (int i = 0; i < image.width; i++) {
        for (int j = image.height*29/30; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = R;
                image(i, j, 1) = G;
                image(i, j, 2) = B;
            }
        }
    }
    //Draw The right side
    for (int i = image.width*39/40; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = R;
                image(i, j, 1) = G;
                image(i, j, 2) = B;
            }
        }
    }
    return;

}
void filter_fancyframe(Image& image, int R, int G, int B) {
    // Main frame
    //Draw The left side
    for (int i = 0; i < image.width / 65; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = R;
                image(i, j, 1) = G;
                image(i, j, 2) = B;
            }
        }
    }
   
    //Draw The upper side
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height / 40; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = R;
                image(i, j, 1) = G;
                image(i, j, 2) = B;
            }
        }
    }
    //Draw The down side
    for (int i = 0; i < image.width; i++) {
        for (int j = image.height * 39 / 40; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = R;
                image(i, j, 1) = G;
                image(i, j, 2) = B;
            }
        }
    }
    //Draw The right side
    for (int i = image.width * 64 / 65; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = R;
                image(i, j, 1) = G;
                image(i, j, 2) = B;
            }
        }
    }
    ////////////////////////////////
    //outside frame
    //Draw left side
    for (int i = image.width / 65; i < image.width / 50; i++) {
        for (int j = image.height / 40; j < image.height * 39 / 40; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    //Draw right side
    for (int i = image.width *51/ 52; i < image.width*69/70; i++) {
        for (int j = image.height / 40; j < image.height * 39 / 40; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    //Draw The upper side
    for (int i = image.width / 65; i < image.width*64/65; i++) {
        for (int j = image.height/40; j < image.height/32.5; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    //Draw The down side
    for (int i = image.width / 65; i < image.width *64/65; i++) {
        for (int j = image.height* 31/ 32; j < image.height * 39 / 40; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    ///////////////////////////////
    //inside frame
    //draw left side
    for (int i = image.width / 40; i < image.width / 35; i++) {
        for (int j = image.height / 20; j < image.height * 19 / 20; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    // draw right side
    for (int i = image.width * 35 / 36; i < image.width * 40.5 / 41.5; i++) {
        for (int j = image.height / 20; j < image.height * 19 / 20; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    //draw upper side
    for (int i = image.width / 40; i < image.width*41/42; i++) {
        for (int j = image.height /22.5; j < image.height /20; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    //draw down side
    for (int i = image.width / 40; i < image.width * 41 / 42; i++) {
        for (int j = image.height *19/20; j < image.height*21.5/22.5; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    
    
    return;
}
void filter_rotate(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                
            }
        }
    }
}
int main() {
    int R=0, G=0, B=0;
    cout << "=============== Welcome to Baby-Photoshop ===============\nPlease load the image, enter name of the image: ";
    load(image);
    bool x = false;
    string choice,choice2 ;
    while (true){
       cout << "\n{1} load new image\n{2} GrayScale \n{3} Black And White \n{4} Invert Image \n{5} Lighten Image Or Darken Image \n{6} Flip Image\n{7} Frame\n{8}  \n{9}  \n{10}  \n{11}  \n{12}  \n{13}   \n{14}  \n{15}   \n{16} Save the image\n{17} Exit \n";
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
                       cout << "Please enter right choice:\a ";
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
            string z;    //choice enter
            cout << "1) Fancy frame\n2) Simple frame\nChoose your choice: ";
            while(true){
                cin >> z;
                if(z=="1") {
                    filter_colors(R,G,B);
                    filter_fancyframe(image,R,G,B);
                    break;
                }
                else if (z=="2") {
                    filter_colors(R, G, B);
                    filter_simpleframe(image, R, G, B);
                    break;
                }
                else {
                    cout << "please Enter right choice!\a";
                }
            }
            x = true;
        }
        else if (choice == "8") {
            
            x = true;
        }
        else if (choice == "9") {

            x = true;
        }
        else if (choice == "10") {

            x = true;
        }
        else if (choice == "11") {

            x = true;
        }
        else if (choice == "12") {

            x = true;
        }
        else if (choice == "13") {

            x = true;
        }
        else if (choice == "14") {

            x = true;
        }
        else if (choice == "15") {

            x = true;
        }
        else if (choice == "16") {
            save();
            x = false;
        }
        else if (choice == "17") {
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
            cout << "Wrong choice, try again:\a " ;
        }  
    } 
}