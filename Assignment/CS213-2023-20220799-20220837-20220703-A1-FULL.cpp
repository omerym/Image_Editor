/*
FCAI – OOP Programming – 2023 - Assignment 1
Program Name: Assignment.cpp
Last Modification Date: 10/10/2023
Author1 and ID and Group: Omer Yassir 20200799 - omerym10@gmail.com
Author2 and ID and Group: Bashar Abdalla 20220837 - basharabdallha@gmail.com
Author3 and ID and Group: Omar Sallah 20220703 - sd.omar04@gmail.com
Teaching Assistant: xxxxx xxxxx
Purpose:..........

*/

#include <iostream>
#include <string>
#include <cstring>
#include <math.h>
#include "Image.cpp"
using namespace std;

int load(unsigned char image[][SIZE]);
void save(unsigned char image[][SIZE]);
int main()
{
	Image image;
	cout << "welcome,\n";
	cout << "Enter filename: ";
	// get filename from user and load it, if file does not exist try again.
	while (load(image.image));
	bool running = true;
	while (running)
	{
		cout << "Please select a filter to apply or 0 to exit:\n";
		cout << "1-	Black & White Filter\n"
			<< "2-	Invert Filter\n"
			<< "3-	Merge Filter\n"
			<< "4-	Flip Image\n"
			<< "5-	Darken and Lighten Image\n"
			<< "6-	Rotate Image\n"
			<< "7-	Detect Image Edges\n"
			<< "8-	Enlarge Image\n"
			<< "9-	Shrink Image\n"
			<< "a-	Mirror 1/2 Image\n"
			<< "b-	Shuffle Image\n"
			<< "c-	Blur Image\n"
			<< "d-	Crop Image\n"
			<< "e-	Skew Image Right\n"
			<< "f-	Skew Image Up\n"
			<< "s-  Save the image to a file\n"
			<< "0-	Exit\n";
		// get operation code
		char operation_code;
		cin >> operation_code;
		switch (operation_code)
		{
		case '0':
			//exit the loop
			running = false;
			break;
		case '1':
			cout << "Black and White filter applied\n";
			image.toBlackWhite();
			break;
		case '2':
			image.invert();
			break;
		case '3':
			unsigned char other[SIZE][SIZE];
			while (load(other));
			image.merge(other);
			break;
		case '4':
			cout<<"Flip (h)orizontally or (v)ertically ?\n";
			char Flip_Image_Input;
			cin >> Flip_Image_Input;
			image.flip(Flip_Image_Input);
			break;
		case '5':
		{
			cout << "Do you want to (d)arken or (l)ighten?: ";
			char input;
			cin >> input;
			float factor = input == 'd' ? 0.5 : input == 'l' ? 1.5 : 0;
			image.lighten(factor);
			break;
		}
		case '6':
		{
			cout << "Enter degrees of rotation(90,180,270): ";
			float degree;
			cin >> degree;
			image.rotate(degree);
			break;
		}
		case '7':
			cout << "Appling Detect Image Edges\n";
			image.detectEdges();
			cout << "Detect Image Edges applied\n";
			break;
		case '8':
			image.enlarge();
			cout << "Filter Applied\n";
			break;
		case '9':
		{
			cout << "Enter shrink factor.(2,3,4...):  ";
			int factor;
			cin >> factor;
			image.shrink(factor);
			break;
		}
		case 'a':
			cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side: ";
			image.mirror();
			break;
		case 'b':
		cout << "please enter the order of quarters\n";
		int input[4];
			for(int i =0;i<4;i++)
				{
					cin>>input[i];
				}
			image.Shuffle_Image(input);
			break;
		case 'c':
			image.blur
			();
			break;
		case 'd':
		{
			int x, y, w, l;
			cout << "Please enter crop position (x,y)";
			cin >> x >> y;
			cout << "Please enter crop dimensions (w,l)";
			cin >> w >> l;
			image.crop(x,y,w,l);
			break;
		}
		case 'e':
		{
			cout << "Please enter degree to skew right:";
			float deg;
			cin >> deg;
			image.skewRight(deg);
			break;
		}
		case 'f':
		{
			cout << "Please enter degree to skew up:";
			float deg;
			cin >> deg;
			image.skewUp( deg);
			break;
		}
		case 's':
			save(image.image);
			break;
		// if operation code does not match any defined operation 
		default:
			cout << "Invalid input!\n";
			break;
		}
	}
	return 0;
}





// load image from file
int load(unsigned char image[][SIZE]) {
	char imageFileName[100];

	// Get gray scale image file name
	cout << "Enter the source image file name: ";
	cin >> imageFileName;

	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");
	return readGSBMP(imageFileName, image);
}

// save image to file
void save(unsigned char image[][SIZE]) {
	char imageFileName[100];

	// Get gray scale image target file name
	cout << "Enter the target image file name: ";
	cin >> imageFileName;

	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");
	writeGSBMP(imageFileName, image);
}