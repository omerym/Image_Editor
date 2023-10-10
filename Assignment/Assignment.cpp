#include <iostream>
#include <string>
#include <cstring>
#include <math.h>
#include "bmplib.cpp"
using namespace std;
class Image
{
public:
	unsigned char image[SIZE][SIZE];
	void merge(unsigned char other[SIZE][SIZE]);
	void copyTo(unsigned char other[SIZE][SIZE]);
	void copyFrom(unsigned char other[SIZE][SIZE]);
	void multiply(float factor);
	void invert();
	void shrink(int factor);
	void mirror();
	void flip();
	void crop();
	void toBlackWhite();
	void detectEdges();
	void rotate();
	void enlarge();
	int getAvarage();
	void skewUp(float degree);
	void skewRight(float degree);
	void combineTransformations(float output[2][2], float first[2][2], float second[2][2]);
	void trasform(float inverseTransformation[2][2], int centreX = 0, int centreY = 0);
};

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
			image.flip();
			break;
		case '5':
		{
			cout << "Do you want to (d)arken or (l)ighten?\n";
			char input;
			cin >> input;
			float factor = input == 'd' ? 0.5 : input == 'l' ? 1.5 : 0;
			image.multiply(factor);
			break;
		}
		case '6':
			cout << "rotate (w)270deg or  or (x)90deg or (y)180deg\n";
			image.rotate();
			break;
		case '7':
			cout << "Detect Image Edges applied\n";
			image.detectEdges();
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
			cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
			image.mirror();
			break;
		case 'b':
			cout << "Work in progress\n";
			break;
		case 'c':
			cout << "Work in progress\n";
			break;
		case 'd':
			cout << "Please enter x y l w:\n";
			image.crop();
			break;
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


// load image and merge it with current image
void Image::merge(unsigned char other[SIZE][SIZE])
{
	// merge the two images
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			// average pixels of the images
			image[i][j] = ((int)image[i][j] + (int)other[i][j]) / 2;
		}
	}
}

void Image::copyTo(unsigned char other[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			other[i][j] = image[i][j];
		}
	}
}

void Image::copyFrom(unsigned char other[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = other[i][j];
		}
	}
}

// multiply all pixels with a factor for darkening and lightening
void Image::multiply(float factor)
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
void Image::invert()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = 255 - image[i][j];
		}
	}
}

//Shrink image:
void Image::shrink(int factor)
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
void Image::mirror()
{
	char Mirror_input;
	int Switch_Var1;
	int Switch_Var2;
	cin >> Mirror_input;
	switch (Mirror_input) {
	case 'r':
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[i][j] = image[i][SIZE - j];
			}
		}
		cout << "Effect Applied Successfully\n";
		break;
	case 'd':
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[i][j] = image[SIZE - i][j];
			}
		}
		cout << "Effect Applied Successfully\n";
		break;
	case 'l':
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[i][SIZE - j] = image[i][j];
			}
		}
		cout << "Effect Applied Successfully\n";
		break;
	case 'u':
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[SIZE - i][j] = image[i][j];
			}
		}
		cout << "Effect Applied Successfully\n";
		break;
	default:
		cout << "Invalid Input\n";
		break;
	}
}
void Image::flip() {
	char Flip_Image_Input;
	unsigned char image2[SIZE][SIZE];
	cin >> Flip_Image_Input;
	switch (Flip_Image_Input) {
	case 'h':
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image2[i][j] = image[i][SIZE - j];
			}
		}
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[i][j] = image2[i][j];
			}
		}
		break;
	case 'v':
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image2[i][j] = image[SIZE - i][j];
			}
		}
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[i][j] = image2[i][j];
			}
		}
		break;
	default:
		cout << "invalid input\n";
		break;
	}
}
void Image::crop() {
	int X, Y, L, W;
	cin >> X >> Y >> L >> W;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (X <= i && i <= L && Y <= j && j <= W) {
				;
			}
			else
			{
				image[i][j] = 255;
			}
		}
	}
}
void Image::toBlackWhite() {
	int avarage = getAvarage();
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (image[i][j] < avarage)
			{
				image[i][j] = 0;
			}
			else
			{
				image[i][j] = 255;
			}
		}
	}
}
void Image::detectEdges() {
	int changeH;
	int changeV;
	int Grad;
	int image2[SIZE][SIZE];
	for (int j = 2; j <= SIZE; j++)
	{
		for (int i = 2; i <= SIZE - 2; i++)
		{
                        //Horizontal Kernal.
			changeH =
				-1 * image[i - 1][j + 1] - 2 * image[i - 1][j] - 1 * image[i - 1][j - 1]
				+ 0 * image[i][j - 1] + 0 * image[i][j] + 0 * image[i][j + 1]
				+ 1 * image[i + 1][j - 1] + 2 * image[i + 1][j] + 1 * image[i + 1][j + 1];
			//Vertical Kernal.
			changeV =
				+1 * image[i - 1][j + 1] + 0 * image[i - 1][j] - 1 * image[i - 1][j - 1]
				- 2 * image[i][j - 1] + 0 * image[i][j] + 2 * image[i][j + 1]
				- 1 * image[i + 1][j - 1] + 0 * image[i + 1][j] + 1 * image[i + 1][j + 1];
			Grad = sqrt(pow(changeH, 2) + pow(changeV, 2));
			image2[i][j] = Grad;
		}
	}
	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if(image2[i][j]>127)
			{
				image[i][j] = 0;
			}
			else
			{
				image[i][j]=255;
			}
		}
	}
}
//rotateImage
void Image::rotate() {
	char rotareInput;
	unsigned char image2[SIZE][SIZE];
	cin >> rotareInput;
	switch (rotareInput) {
	case 'w':
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image2[i][j] = image[i][SIZE - j];
			}
		}
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[i][j] = image2[SIZE - i][j];
			}
		}
		break;
	case 'x':
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image2[i][j] = image[SIZE - j][i];
			}
		}
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[i][j] = image2[i][j];
			}
		}
		break;
	case'y':
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image2[i][j] = image[i][j];
			}
		}
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[SIZE - i][SIZE - j] = image2[i][j];
			}
		}
	default:
		cout << "invalid input\n";
		break;
	}
}
//enlargeImage
void Image::enlarge() {
	int image2[SIZE][SIZE];
	int N = SIZE / 2;
	char input;
	cout << "please enter quarter to enlarge\n";
	cin >> input;
	switch (input)
	{
	case'1':
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				image2[i][j] = image[i][j];
			}
		}
		for (int i = 0; i <= SIZE / 2; i++)
		{
			for (int j = 0; j <= SIZE / 2; j++)
			{
				int i2 = i * 2;
				int j2 = j * 2;
				image[i2][j2] = image2[i][j];

				image[i2 + 1][j2] = image2[i][j];

				image[i2][j2 + 1] = image2[i][j];

				image[i2 + 1][j2 + 1] = image2[i][j];
			}
		}
		break;
	case '2':
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < N; j++) {

				image2[i][j] = image[i][j + N];
			}
		}
		for (int i = 0; i <= SIZE / 2; i++)
		{
			for (int j = 0; j <= SIZE / 2; j++)
			{
				int i2 = i * 2;
				int j2 = j * 2;
				image[i2][j2] = image2[i][j];

				image[i2 + 1][j2] = image2[i][j];

				image[i2][j2 + 1] = image2[i][j];

				image[i2 + 1][j2 + 1] = image2[i][j];
			}
		}
		break;
	case '3':
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image2[i][j] = image[i + N][j];
			}
		}
		for (int i = 0; i <= SIZE / 2; i++)
		{
			for (int j = 0; j <= SIZE / 2; j++)
			{
				int i2 = i * 2;
				int j2 = j * 2;
				image[i2][j2] = image2[i][j];

				image[i2 + 1][j2] = image2[i][j];

				image[i2][j2 + 1] = image2[i][j];

				image[i2 + 1][j2 + 1] = image2[i][j];
			}
		}
		break;
	case '4':
		for (int i = 0; i < SIZE; i++) {

			for (int j = 0; j < SIZE; j++)
			{
				image2[i][j] = image[i + N][j + N];
			}
		}
		for (int i = 0; i <= SIZE / 2; i++) {

			for (int j = 0; j <= SIZE / 2; j++)
			{
				int i2 = i * 2;
				int j2 = j * 2;
				image[i2][j2] = image2[i][j];

				image[i2 + 1][j2] = image2[i][j];

				image[i2][j2 + 1] = image2[i][j];

				image[i2 + 1][j2 + 1] = image2[i][j];
			}
		}
		break;
	default:
		cout << "invalid input\n";
		break;
	}
}

int Image::getAvarage()
{
	int sum = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			sum += image[i][j];
		}
	}
	return sum / SIZE / SIZE;
}

void Image::skewUp(float degree)
{
	float scale = 1 / (1 + tan(degree * 3.14 / 180));
	float arr[2][2];
	float arr1[2][2] = { { 1,0},
						{tan(-degree * 3.14 / 180),1} };
	float f[2][2] = { { scale,0},
					{0,1} };
	combineTransformations(arr, arr1, f);
	trasform(arr,0, SIZE - 1);
}
void Image::skewRight(float degree)
{
	float scale = 1 / (1 + tan(degree * 3.14 / 180));
	float arr[2][2];
	float arr1[2][2] = { { 1,tan(-degree * 3.14 / 180)},
						{0,1} };
	float f[2][2] = { { 1,0},
					{0,scale} };
	combineTransformations(arr, arr1, f);
	trasform(arr,SIZE - 1);
}
void Image::combineTransformations(float output[2][2], float first[2][2], float second[2][2])
{
	output[0][0] = second[0][0] * first[0][0] + second[1][0] * first[0][1];
	output[0][1] = second[0][1] * first[0][0] + second[1][1] * first[0][1];
	output[1][0] = second[0][0] * first[1][0] + second[1][0] * first[1][1];
	output[1][1] = second[0][1] * first[1][0] + second[1][1] * first[1][1];

}
void Image::trasform(float transformation[2][2], int centreX, int centreY)
{
	unsigned char t[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			t[SIZE][SIZE] = SIZE - 1;
		}
	}
	for (int i = 0 - centreX; i < SIZE - centreX; i++)
	{
		for (int j = 0 - centreY; j < SIZE - centreY; j++)
		{
			int it = transformation[0][0] * i + transformation[1][0] * j + centreX;
			int jt = transformation[0][1] * i + transformation[1][1] * j + centreY;
			bool is_iValid = it >= 0 && it < SIZE;
			bool is_jValid = jt >= 0 && jt < SIZE;
			if (is_iValid && is_jValid)
			{
				t[it][jt] = image[i + centreX][j + centreY];
			}
		}
	}
	copyFrom(t);
}
