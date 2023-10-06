// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void Flip_Image ();

int main()
{
  loadImage();
  doSomethingForImage();
  saveImage();
  return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

//_________________________________________
void Flip_Image(){
	char Flip_Image_Input;
	unsigned char image2[SIZE][SIZE];
	cin>>Flip_Image_Input;
	switch(Flip_Image_Input){
		case 'h':
		for(int i=0;i<SIZE;i++)
		  {
			for(int j=0;j<SIZE;j++)
			{
             image2[i][j]=image[i][SIZE-j];
			}
		  }
		 for(int i=0;i<SIZE;i++)
		  {
			for(int j=0;j<SIZE;j++)
			{
             image[i][j]=image2[i][j];
			}
		  }
		 break;
		case 'v':
		for(int i=0;i<SIZE;i++)
		  {
			for(int j=0;j<SIZE;j++)
			{
             image2[i][j]=image[SIZE-i][j];
			}
		  }
		 for(int i=0;i<SIZE;i++)
		  {
			for(int j=0;j<SIZE;j++)
			{
             image[i][j]=image2[i][j];
			}
		  }
		 break;
		default:
		 cout<<"invalid input\n";
		 break;
	}
}
