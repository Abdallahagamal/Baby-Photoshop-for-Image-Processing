#include <iostream>
#include <algorithm>
#include "Image_Class.h"
#include <cstdlib>
using namespace std;
Image image;
string filename;
Image resize(Image& image) {
    //mmmm

    int originalWidth = image.width;
    int originalHeight = image.height;

    int neewWidth, neewHeight;

    cout << "Enter the new width: ";
    cin >> neewWidth;
    cout << "Enter the new height: ";
    cin >> neewHeight;


    Image resizedImage(neewWidth, neewHeight);

    for (int i = 0; i < neewWidth; ++i) {
        for (int j = 0; j < neewHeight; ++j) {
            int originalX = i * originalWidth / neewWidth;
            int originalY = j * originalHeight / neewHeight;

            unsigned int redv = image.getPixel(originalX, originalY, 0);
            unsigned int greenV = image.getPixel(originalX, originalY, 1);
            unsigned int blueV = image.getPixel(originalX, originalY, 2);

            resizedImage.setPixel(i, j, 0, redv);
            resizedImage.setPixel(i, j, 1, greenV);
            resizedImage.setPixel(i, j, 2, blueV);
        }
    }

    return resizedImage;
}
Image cropfunction(Image& image) {
    string filename2;
    int imageewidth = image.width;
    int imageeheight = image.height;

    int x, y, width, height;
    cout << "Enter the starting point (x , y ) of the area to crop:  ";
    cin >> x >> y;
    cout << "Enter the new width and the Height of the image in this format 'H W': ";
    cin >> width >> height;

    if (x < 0 || y < 0 || width <= 0 || height <= 0 ||
        x + width > imageewidth || y + height > imageeheight) {
        cerr << "Error: Cropping dimensions are out of bounds.\n";

    }

    Image croppedImage(width, height);


    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {

            unsigned int redV = image.getPixel(x + i, y + j, 0);
            unsigned int greenV = image.getPixel(x + i, y + j, 1);
            unsigned int blueV = image.getPixel(x + i, y + j, 2);
            croppedImage.setPixel(i, j, 0, redV);
            croppedImage.setPixel(i, j, 1, greenV);
            croppedImage.setPixel(i, j, 2, blueV);
        }
    }

    return croppedImage;
}

void invert_image(Image& image) {
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
            while (true) {
                try {
                    cin >> filename2;
                    image.saveImage(filename2);
                    cout << "Photo Has been save successfully";
                    system(filename2.c_str());

                }
                catch (...) {
                    cout << "Please Enter Right Format:\a ";
                }
                break;
            }
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
void load(Image& image) {

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
void filter_55(Image& image) {
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
void filter_colors(int& R, int& G, int& B) {
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
void filter_simpleframe(Image& image, int R, int G, int B) {
    //Draw The left side
    for (int i = 0; i < image.width / 50; i++) {
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
        for (int j = 0; j < image.height / 30; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = R;
                image(i, j, 1) = G;
                image(i, j, 2) = B;
            }
        }
    }
    //Draw The down side
    for (int i = 0; i < image.width; i++) {
        for (int j = image.height * 29 / 30; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = R;
                image(i, j, 1) = G;
                image(i, j, 2) = B;
            }
        }
    }
    //Draw The right side
    for (int i = image.width * 39 / 40; i < image.width; i++) {
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
    for (int i = image.width * 51 / 52; i < image.width * 69 / 70; i++) {
        for (int j = image.height / 40; j < image.height * 39 / 40; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    //Draw The upper side
    for (int i = image.width / 65; i < image.width * 64 / 65; i++) {
        for (int j = image.height / 40; j < image.height / 32.5; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    //Draw The down side
    for (int i = image.width / 65; i < image.width * 64 / 65; i++) {
        for (int j = image.height * 31 / 32; j < image.height * 39 / 40; j++) {
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
    for (int i = image.width / 40; i < image.width * 41 / 42; i++) {
        for (int j = image.height / 22.5; j < image.height / 20; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
    //draw down side
    for (int i = image.width / 40; i < image.width * 41 / 42; i++) {
        for (int j = image.height * 19 / 20; j < image.height * 21.5 / 22.5; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }


    return;
}
Image rotate_180(Image& image) {
    int originalWidth = image.width;
    int originalHeight = image.height;

    // to hold the rotated image
    Image rotatedImage2(originalWidth, originalHeight);


    for (int i = 0; i < originalWidth; ++i) {
        for (int j = 0; j < originalHeight; ++j) {
            int newX = originalHeight - j - 1;
            int newY = originalWidth - i - 1;

            // get pixel values from original image
            unsigned char red = image(i, j, 0);
            unsigned char green = image(i, j, 1);
            unsigned char blue = image(i, j, 2);

            // put the new values in new location in rotated image
            rotatedImage2(newY, newX, 0) = red;
            rotatedImage2(newY, newX, 1) = green;
            rotatedImage2(newY, newX, 2) = blue;
        }
    }
    return rotatedImage2;
}
Image filter_rotate(Image& image, string ch) {
    int originalWidth = image.width;
    int originalHeight = image.height;
    int newY;
    int newX;
    //to hold the rotated image
    Image rotatedImage(originalHeight, originalWidth);
    for (int i = 0; i < originalWidth; ++i) {
        for (int j = 0; j < originalHeight; ++j) {
            if (ch == "1") {
                // the rotated image 90 degrees clockwise
                newX = i;
                newY = originalHeight - 1 - j;
            }
            else if (ch == "3") {
                // the rotated image 270 degrees clockwise
                newX = originalWidth - 1 - i;
                newY = j;
            }
            // get pixel values from original image
            unsigned char red = image(i, j, 0);
            unsigned char green = image(i, j, 1);
            unsigned char blue = image(i, j, 2);

            // put the new values in new location in rotated image
            rotatedImage(newY, newX, 0) = red;
            rotatedImage(newY, newX, 1) = green;
            rotatedImage(newY, newX, 2) = blue;
        }
    }
    return rotatedImage;
}
void BlurFilter(Image& image, int kernelSize) {
    for (int j = 0; j < image.height; ++j) {
        for (int i = 0; i < image.width; ++i) {
            float totalRed = 0, totalGreen = 0, totalBlue = 0;
            for (int ky = -kernelSize / 2; ky <= kernelSize / 2; ++ky) {
                for (int kx = -kernelSize / 2; kx <= kernelSize / 2; ++kx) {
                    int pixelX = i + kx;
                    int pixelY = j + ky;
                    if (pixelX >= 0 && pixelX < image.width && pixelY >= 0 && pixelY < image.height) {
                        totalRed += image(pixelX, pixelY, 0);
                        totalGreen += image(pixelX, pixelY, 1);
                        totalBlue += image(pixelX, pixelY, 2);
                    }
                }
            }

            int numPixels = kernelSize * kernelSize;
            totalRed /= numPixels;
            totalGreen /= numPixels;
            totalBlue /= numPixels;

            image(i, j, 0) = static_cast<unsigned char>(totalRed);
            image(i, j, 1) = static_cast<unsigned char>(totalGreen);
            image(i, j, 2) = static_cast<unsigned char>(totalBlue);
        }
    }
}
void purplefilter(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                // Must decrease the green color and make the red and blue constant
                image(i, j, 1) *= 0.91;

            }

        }

    }
}
Image Detect_Image_Edges(Image& image) {
    int w = image.width;
    int h = image.height;
    Image image2(w, h);
    for (int i = 1; i < image.width - 1; ++i) {
        for (int j = 1; j < image.height - 1; ++j) {
            if ((image(i - 1, j, 0) == 255 || image(i, j - 1, 0) == 255 || image(i + 1, j, 0) == 255 || image(i, j + 1, 0) == 255) && image(i, j, 0) == 0) {
                image2(i, j, 0) = 0;
                image2(i, j, 1) = 0;
                image2(i, j, 2) = 0;
            }
            else {
                image2(i, j, 0) = 255;
                image2(i, j, 1) = 255;
                image2(i, j, 2) = 255;
            }
        }
    }
    return image2;
}
void infrared(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            image(i, j, 0) = 255;
            image(i, j, 1) = 255 - image(i, j, 1);
            image(i, j, 2) = 255 - image(i, j, 2);
        }
    }
}
int main() {
    int R = 0, G = 0, B = 0;
    cout << "=============== Welcome to Baby-Photoshop ===============\nPlease load the image, enter name of the image: ";
    load(image);
    bool x = false;
    string choice, choice2;
    while (true) {
        cout << "\n{1} load new image\n{2} GrayScale \n{3} Black And White \n{4} Invert Image \n{5} Lighten Image Or Darken Image \n{6} Flip Image\n{7} Frame\n{8} Blur\n{9} Rotate  \n{10} Purple Effect  \n{11} Detect Image Edges  \n{12} infrared  \n{13} CropImage   \n{14} resize image  \n{15}   \n{16}   \n{17} Save the image\n{18} Exit \n";
        cout << "enter your choice : ";
        cin >> choice;
        if (choice == "1") {
            if (x == false) {
                cout << "Please load the new image, enter name of the image: ";
                load(image);
                remove("Temp.jpg");
            }
            else {
                cout << "\nDo you want to save the current image before loading a new one?\n1)Yes\n2)No\nEnter your choice: ";
                while (true) {
                    cin >> choice2;
                    if (choice2 == "1") {
                        save();
                        cout << "Please load the new image, enter name of the image: ";
                        load(image);
                        remove("Temp.jpg");
                        break;
                    }
                    else if (choice2 == "2") {
                        cout << "Please load the new image, enter name of the image: ";
                        load(image);
                        remove("Temp.jpg");
                        break;
                    }
                    else {
                        cout << "Please enter right choice:\a ";
                    }
                }
            }

        }
        else if (choice == "2") {
            Gray_Scale(image);
            x = true;
        }
        else if (choice == "3") {
            Black_White(image);
            x = true;
        }
        else if (choice == "4") {
            invert_image(image);
            x = true;
        }
        else if (choice == "5") {
            cout << "{1} Lighten Image \n";
            cout << "{2} Darken Image \n";
            string choice2;
            while (true) {
                cout << "enter your choice2 : ";
                cin >> choice2;
                if (choice2 == "1") {
                    Lighten_Image(image);
                    x = true;
                    break;

                }
                else if (choice2 == "2") {
                    Darken_Image(image);
                    x = true;
                    break;

                }
            }

        }
        else if (choice == "6") {
            filter_55(image);
        }
        else if (choice == "7") {
            string z;    //choice enter
            cout << "1) Fancy frame\n2) Simple frame\nChoose your choice: ";
            while (true) {
                cin >> z;
                if (z == "1") {
                    filter_colors(R, G, B);
                    filter_fancyframe(image, R, G, B);
                    break;
                }
                else if (z == "2") {
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
            int i = 4;
            while (i--) {
                BlurFilter(image, 25);
            }
            x = true;
        }
        else if (choice == "9") {
            string ch;
            cout << "1) Rotate by 90 degree\n2) Rotate by 180 degree\n3) Rotate by 270 degree\nChoose the angle of rotation Enter Your choice: ";
            while (true) {
                cin >> ch;
                if (ch == "1" || ch == "3") {
                    Image image2 = filter_rotate(image, ch);
                    image2.saveImage("Temp.jpg");
                    image.loadNewImage("Temp.jpg");
                    break;
                }
                else if (ch == "2") {
                    Image image3 = rotate_180(image);
                    image3.saveImage("Temp.jpg");
                    image.loadNewImage("Temp.jpg");
                    break;
                }
                else {
                    cout << "Enter right Choice please:\a ";
                }
            }
            x = true;
        }
        else if (choice == "10") {
            purplefilter(image);
            x = true;
        }
        else if (choice == "11") {
            Black_White(image);
            Image image2 = Detect_Image_Edges(image);
            image2.saveImage("Temp2.jpg");
            image.loadNewImage("Temp2.jpg");
            x = true;
        }
        else if (choice == "12") {
            infrared(image);
            x = true;
        }
        else if (choice == "13") {
            Image image3 = cropfunction(image);
            image3.saveImage("Temp3.jpg");
            image.loadNewImage("Temp3.jpg");
            x = true;
        }
        else if (choice == "14") {
            Image image4 = resize(image);
            image4.saveImage("Temp4.jpg");
            image.loadNewImage("Temp4.jpg");
            x = true;
        }
        else if (choice == "15") {

            x = true;
        }
        else if (choice == "16") {

            x = true;
        }
        else if (choice == "17") {
            save();
            remove("Temp.jpg");
            x = false;
        }
        else if (choice == "18") {
            if (x == true) {
                cout << "Do you want to save the current image before exit?\n1) Yes\n2) No\nEnter your choice: ";
                while (true) {
                    cin >> choice2;
                    if (choice2 == "1") {
                        save();
                        remove("Temp.jpg");
                        break;
                    }
                    else if (choice2 == "2") {
                        cout << "Thanks for using app";
                        remove("Temp.jpg");
                        break;
                    }
                    else {
                        cout << "Please Enter Right choice: ";
                    }
                }
                break;
            }
            else {
                cout << "Thanks for using app";
                break;
            }
        }
        else {
            cout << "Wrong choice, try again:\a ";
        }
    }
}