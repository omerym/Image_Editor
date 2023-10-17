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

int load(unsigned char image[][SIZE][RGB]);
void save(unsigned char image[][SIZE][RGB]);
void toGSArray(Image to[RGB]);
void fromGSArray(Image from[RGB]);
void detectEdges();
void blur();
void toBlackWhite();
int getAverage();
void skewUp(float deg);
void skewRight(float deg);
void lighten(float factor);
void invert();
void crop(int x,int y, int w, int l);
void flip(char Flip_Image_Input);
void Shuffle_Image(int input[4]);
void mirror(char Mirror_input);
unsigned char image[SIZE][SIZE][RGB];
int main()
{
	cout << "welcome,\n";
	cout << "Enter filename: ";
	// get filename from user and load it, if file does not exist try again.
	while (load(image));
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
			toBlackWhite();
			break;
		case '2':
		   cout<<"apply invert";
		    invert();
			break;
		case '3':
			unsigned char other[SIZE][SIZE][RGB];
			while (load(other));
			break;
		case '4':
			cout<<"Flip (h)orizontally or (v)ertically ?\n";
			char Flip_Image_Input;
			cin >> Flip_Image_Input;
			flip(Flip_Image_Input);
			break;
		case '5':
		{
			cout << "Do you want to (d)arken or (l)ighten?: ";
			char input;
			cin >> input;
			float factor = input == 'd' ? 0.5 : input == 'l' ? 1.5 : 0;
			lighten(factor);
			break;
		}
		case '6':
		{
			cout << "Enter degrees of rotation(90,180,270): ";
			float degree;
			cin >> degree;
			break;
		}
		case '7':
			cout << "Appling Detect Image Edges\n";
			detectEdges();
			cout << "Detect Image Edges applied\n";
			break;
		case '8':
			cout << "Filter Applied\n";
			break;
		case '9':
		{
			cout << "Enter shrink factor.(2,3,4...):  ";
			int factor;
			cin >> factor;
			break;
		}
		case 'a':
			cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side: ";
			char Mirror_input;
			cin >> Mirror_input;
			mirror(Mirror_input);
			cout << "Effect Applied Successfully\n";
			break;
		case 'b':
			cout << "please enter the order of quarters\n";
			int input[4];
			for(int i =0;i<4;i++)
				{
					cin>>input[i];
				}
			Shuffle_Image(input);
			break;
		case 'c':
			blur();
			break;
		case 'd':
		{
			int x, y, w, l;
			cout << "Please enter crop position (x,y)";
			cin >> x >> y;
			cout << "Please enter crop dimensions (w,l)";
			cin >> w >> l;
			crop(x,y,w,l);
			break;
		}
		case 'e':
		{
			cout << "Please enter degree to skew right:";
			float deg;
			cin >> deg;
			skewRight(deg);
			break;
		}
		case 'f':
		{
			cout << "Please enter degree to skew up:";
			float deg;
			cin >> deg;
			skewUp(deg);
			break;
		}
		case 's':
			save(image);
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
int load(unsigned char image[][SIZE][RGB]) {
	char imageFileName[100];

	// Get gray scale image file name
	cout << "Enter the source image file name: ";
	cin >> imageFileName;

	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");
	return readRGBBMP(imageFileName, image);
}

// save image to file
void save(unsigned char image[][SIZE][RGB]) {
	char imageFileName[100];

	// Get gray scale image target file name
	cout << "Enter the target image file name: ";
	cin >> imageFileName;

	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");
	writeRGBBMP(imageFileName, image);
}

void toGSArray(Image to[RGB])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int color = 0; color < RGB; color++)
			{
				to[color].image[i][j] = image[i][j][color];
			}
		}
	}
}

void fromGSArray(Image from[RGB])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int color = 0; color < RGB; color++)
			{
				image[i][j][color] = from[color].image[i][j];
			}
		}
	}
}

void detectEdges()
{
	blur();
	Image t[RGB];
	toGSArray(t);
	int grad[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			grad[i][j] = 0;
		}
	}
	for (int c = 0; c < RGB; c++)
	{
		int* x = new int[SIZE * SIZE];
		int* y = new int[SIZE * SIZE];
		t[c].getSobelX(x);
		t[c].getSobelY(y);
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				int h = x[i * SIZE + j], v = y[i * SIZE + j];
				grad[i][j] += h * h + v * v;
			}
		}
		delete[]x;
		delete[]y;
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int c = 0; c < RGB; c++)
			{
				int g = sqrt(grad[i][j]);
				image[i][j][c] = g > 127 ? 0 : 255;
			}
		}
	}
}
void blur()
{
	Image t[RGB];
	toGSArray(t);
	for (int c = 0; c < RGB; c++)
	{
		t[c].blur();
	}
	fromGSArray(t);
}

void toBlackWhite()
{
	Image t[RGB];
	int temp;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			//gray=0.299 * red + 0.587 * green+ 0.114 * blue
			temp = image[i][j][0]*0.299 + image[i][j][1]*0.587 + image[i][j][2]*0.114;
			
			if(temp<127)
				{
					temp=0;
				}
			else
				{
					temp=255;
				}
			for (int color = 0; color < RGB; color++)
			{
				t[color].image[i][j] = temp;
			}
		}
	}
	fromGSArray(t);
}

int getAverage()
{
	int x = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int c = 0; c < RGB; c++)
			{
				x += image[i][j][c];
			}
		}
	}
	return x / SIZE / SIZE / RGB;
}

void skewUp(float deg)
{
	Image t[RGB];
	toGSArray(t);
	for (int c = 0; c < RGB; c++)
	{
		t[c].skewUp(deg);
	}
	fromGSArray(t);
}

void skewRight(float deg)
{
	Image t[RGB];
	toGSArray(t);
	for (int c = 0; c < RGB; c++)
	{
		t[c].skewRight(deg);
	}
	fromGSArray(t);
}

void lighten(float factor)
{
	Image t[RGB];
	toGSArray(t);
	float average = getAverage();
	for (int c = 0; c < RGB; c++)
	{
		t[c].lighten(average, factor);
	}
	fromGSArray(t);
}
void crop(int x, int y, int w, int l)
{
	Image t[RGB];
	toGSArray(t);
	for(int c =0;c<RGB;c++)
		{
			t[c].crop(x,y,w,l);
		}
	fromGSArray(t);
}
void flip(char Flip_Image_Input)
{
	Image t[RGB];
	toGSArray(t);
	for(int c =0;c<RGB;c++)
		{
			t[c].flip(Flip_Image_Input);
		}
	fromGSArray(t);
}
void Shuffle_Image(int input[4])
{
	Image t[RGB];
	toGSArray(t);
	for(int c =0;c<RGB;c++)
		{
			t[c].Shuffle_Image(input);
		}
	fromGSArray(t);
}
void mirror(char Mirror_input)
{
	Image t[RGB];
	toGSArray(t);
	for(int c =0;c<RGB;c++)
		{
			t[c].mirror(Mirror_input);
		}
	fromGSArray(t);
}
void invert()
{
	Image t[RGB];
	toGSArray(t);
	for(int c =0;c<RGB;c++)
		{
			t[c].invert();
		}
	fromGSArray(t);
}