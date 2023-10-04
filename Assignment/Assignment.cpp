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

int main()
{
	// TODO: change welcome message
	cout << "welcome message:\n";
	cout << "Enter filename: ";
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
		char operation_code;
		cin >> operation_code;
		switch (operation_code)
		{
		case '0':
			running = false;
			break;
		case '1':
			cout << "Work in progress\n";
			break;
		case '2':
			cout << "Work in progress\n";
			break;
		case '3':
			while(merge());
			break;
		case '4':
			cout << "Work in progress\n";
			break;
		case '5':
			cout << "Work in progress\n";
			break;
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
			cout << "Work in progress\n";
			break;
		case 'a':
			cout << "Work in progress\n";
			break;
		case 'b':
			cout << "Work in progress\n";
			break;
		case 'c':
			cout << "Work in progress\n";
			break;
		case 'd':
			cout << "Work in progress\n";
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

		default:
			cout << "Invalid input!\n";
			break;
		}
	}
	return 0;
}

int loadImage() {
	char imageFileName[100];

	// Get gray scale image file name
	cout << "Enter the source image file name: ";
	cin >> imageFileName;

	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");
	return readGSBMP(imageFileName, image);
}

void saveImage() {
	char imageFileName[100];

	// Get gray scale image target file name
	cout << "Enter the target image file name: ";
	cin >> imageFileName;

	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");
	writeGSBMP(imageFileName, image);
}
int merge()
{
	char imageFileName[100];
	// Get gray scale image file name to merge with
	cout << "Enter the target image file name: ";
	cin >> imageFileName;
	strcat(imageFileName, ".bmp");
	unsigned char other[SIZE][SIZE];
	int readResult = readGSBMP(imageFileName, other);
	if (readResult)
	{
		return readResult;
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = ((int)image[i][j] + (int)other[i][j]) / 2;
		}
	}
	return 0;
}