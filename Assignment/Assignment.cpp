#include "bmplib.cpp"
#include <iostream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

unsigned char image[SIZE][SIZE];
int loadImage();
void saveImage();
int merge();
void multiply(float factor);
void invert();
void shrink(int factor);
int main()
{
	cout << "welcome,\n";
	cout << "Enter filename: ";
	// get filename from user and load it, if file does not exist try again.
	while (loadImage());
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
			void Black_White_Filter();
			Black_White_Filter();
			break;
		case '2':
			invert();
			break;
		case '3':
			while(merge());
			break;
		case '4':
			cout<<"Flip (h)orizontally or (v)ertically ?\n";
			void Flip_Image();
			Flip_Image();
			break;
		case '5':
		{
			cout << "Do you want to (d)arken or (l)ighten?\n";
			char input;
			cin >> input;
			float factor = input == 'd' ? 0.5 : input == 'l' ? 1.5 : 0;
			multiply(factor);
			break;
		}
		case '6':
			cout << "Work in progress\n";
			break;
		case '7':
			cout << "Work in progress\n";
			break;
		case '8':
			cout << "Work in progress\n";
			break;
		case '9':
		{
			cout << "Enter shrink factor.(2,3,4...):  ";
			int factor;
			cin >> factor;
			shrink(factor);
			break;
		}
		case 'a':
			void Mirror_Image();
			cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
			Mirror_Image();
			break;
		case 'b':
			cout << "Work in progress\n";
			break;
		case 'c':
			cout << "Work in progress\n";
			break;
		case 'd':
			cout << "Please enter x y l w:\n";
			void Crop_Image();
			Crop_Image();
			break;
		case 'e':
			cout << "Work in progress\n";
			break;
		case 'f':
			cout << "Work in progress\n";
			break;
		case 's':
			saveImage();
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
int loadImage() {
	char imageFileName[100];

	// Get gray scale image file name
	cout << "Enter the source image file name: ";
	cin >> imageFileName;

	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");
	return readGSBMP(imageFileName, image);
}

// save image to file
void saveImage() {
	char imageFileName[100];

	// Get gray scale image target file name
	cout << "Enter the target image file name: ";
	cin >> imageFileName;

	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");
	writeGSBMP(imageFileName, image);
}

// load image and merge it with current image
int merge()
{
	char imageFileName[100];
	// Get gray scale image file name to merge with
	cout << "Enter the target image file name: ";
	cin >> imageFileName;
	strcat(imageFileName, ".bmp");
	unsigned char other[SIZE][SIZE];
	int readResult = readGSBMP(imageFileName, other);
	// if readGSBMP was not successfull
	if (readResult)
	{
		return readResult;
	}
	// merge the two images
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			// average pixels of the images
			image[i][j] = ((int)image[i][j] + (int)other[i][j]) / 2;
		}
	}
	return 0;
}

// multiply all pixels with a factor for darkening and lightening
void multiply(float factor)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			float pixel = (float)image[i][j] * factor;
			// limit pixel value to 255
			pixel = pixel > 255 ? 255 : pixel;
			image[i][j] = pixel;
		}
	}
}

// Invert all image pixels
void invert()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = 255-image[i][j];
		}
	}
}

//Shrink image:
void shrink(int factor)
{
	// Draw shrunk image on top left corner
	for (int i = 0; i * factor < SIZE; i++)
	{
		for (int j = 0; j * factor < SIZE; j++)
		{
			image[i][j] = image[i * factor][j * factor];
		}
	}

	// Set pixeles outside image boundries to white.
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (i * factor >= SIZE || j * factor >= SIZE) 
			{
				image[i][j] = 255;
			}
		}
	}
}
void Mirror_Image()
{
	char Mirror_input;
	int Switch_Var1;
	int Switch_Var2;
	cin>>Mirror_input;
	switch(Mirror_input){
		case 'r':
		  for(int i=0;i<SIZE;i++)
		  {
		    for (int j = 0; j < SIZE; j++)
			{
				image[i][j]=image[i][SIZE-j];
			}
		  }
		  cout<<"Effect Applied Successfully\n";
		  break;
		case 'd':
		  for(int i=0;i<SIZE;i++)
		  {
		    for (int j = 0; j < SIZE; j++)
			{
				image[i][j]=image[SIZE-i][j];
			}
		  }
		  cout<<"Effect Applied Successfully\n";
		    break;
		case 'l':
		for(int i=0;i<SIZE;i++)
		  {
		    for (int j = 0; j < SIZE; j++)
			{
				image[i][SIZE-j]=image[i][j];
			}
		  }
		  cout<<"Effect Applied Successfully\n";
		    break;
		case 'u':
		for(int i=0;i<SIZE;i++)
		  {
		    for (int j = 0; j < SIZE; j++)
			{
				image[SIZE-i][j]=image[i][j];
			}
		  }
		  cout<<"Effect Applied Successfully\n";
		    break;
		default:
		 cout<<"Invalid Input\n";
		    break;
	}
}
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
void Crop_Image(){
	int X,Y,L,W;
	cin>>X>>Y>>L>>W;
	for(int i =0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			if(X<=i&&i<=L&&Y<=j&&j<=W){
				;
			}
			else
			{
			   image[i][j]=255;
			}
		}
	}
}
void Black_White_Filter(){
	for(int i =0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			if(image[i][j]<127)
			{
				image[i][j]=0;
			}
			else
			{
				image[i][j]=255;
			}
		}
	}
}