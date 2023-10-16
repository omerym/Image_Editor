#include <iostream>
#include "bmplib.cpp"
using namespace std;
class Image
{
	unsigned char getPixelSafe(int i, int j);
	unsigned char getPixelByKernal(float kernal[3][3], int x, int y);
public:
	unsigned char image[SIZE][SIZE];
	void merge(unsigned char other[SIZE][SIZE]);
	void copyTo(unsigned char other[SIZE][SIZE]);
	void copyFrom(unsigned char other[SIZE][SIZE]);
	void lighten(float factor);
	void invert();
	void shrink(int factor);
	void mirror();
	void flip();
	void crop(int x, int y, int w, int l);
	void toBlackWhite(int threshold, bool inverted = false);
	void toBlackWhite(bool inverted = false);
	void getSobelX(int result[SIZE][SIZE]);
	void getSobelY(int result[SIZE][SIZE]);
	void detectEdges();
	void rotate(float degree);
	void blur(int s = 1);
	void applyKernal(float kernal[3][3]);
	void enlarge();
	int getAvarage();
	void skewUp(float degree);
	void skewRight(float degree);
	void combineTransformations(float output[2][2], float first[2][2], float second[2][2]);
	void trasform(float inverseTransformation[2][2], int centreX = 0, int centreY = 0);
	void Shuffle_Image();
};

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
void Image::lighten(float factor)
{
	// calculate change in pixels based on average pixel
	float average = getAvarage();
	float diff = average * factor - average;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			float pixel = (float)image[i][j] + diff;
			// clamp values between 0 and SIZE -1
			pixel = pixel > SIZE - 1 ? SIZE - 1 : pixel;
			pixel = pixel < 0 ? 0 : pixel;
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
		break;
	case 'v':
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image2[i][j] = image[SIZE - i][j];
			}
		}
		break;
	default:
		cout << "invalid input\n";
		break;
	}
	copyFrom(image2);
}
void Image::crop(int x, int y, int w, int l) {
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			// check if pixel is outside specified boundry
			if (i < x || i >= x + w || i < y || i >= y + l)
			{
				// set pixel to maximum value (white)
				image[i][j] = 255;
			}
		}
	}
}
void Image::toBlackWhite(int threshold, bool inverted) {
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (image[i][j] < threshold)
			{
				image[i][j] = inverted ? 255 : 0;
			}
			else
			{
				image[i][j] = inverted ? 0 : 255;
			}
		}
	}
}
void Image::toBlackWhite(bool inverted)
{
	toBlackWhite(getAvarage(), inverted);
}
void Image::getSobelX(int result[SIZE][SIZE])
{
	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			result[i][j] =
				-getPixelSafe(i - 1, j + 1) - 2 * getPixelSafe(i - 1, j) - getPixelSafe(i - 1, j - 1)
				+ getPixelSafe(i + 1, j + 1) + 2 * getPixelSafe(i + 1, j) + getPixelSafe(i + 1, j - 1);
		}
	}
}

void Image::getSobelY(int result[SIZE][SIZE])
{
	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			result[i][j] =
				getPixelSafe(i - 1, j + 1) + 2 * getPixelSafe(i, j + 1) + getPixelSafe(i + 1, j + 1)
				- getPixelSafe(i - 1, j - 1) - 2 * getPixelSafe(i, j - 1) - getPixelSafe(i + 1, j - 1);
		}
	}
}
void Image::detectEdges()
{
	// blur image before detecting edges to reduce noise effect
	blur();
	int changeH[SIZE][SIZE];
	int changeV[SIZE][SIZE];
	int average = getAvarage();
	getSobelX(changeH);
	getSobelY(changeV);
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			int ch = changeH[i][j];
			int cv = changeV[i][j];
			int grad = sqrt(ch * ch + cv * cv);
			grad = grad < 255 ? grad : 255;
			image[i][j] = grad;
		}
	}
	toBlackWhite(average, true);
}
void Image::rotate(float degree)
{
	//degree to radian
	degree *= -3.14 / 180;
	float rotation[2][2] = { {cos(degree),sin(degree)},
							 {-sin(degree),cos(degree)} };
	trasform(rotation, SIZE / 2, SIZE / 2);
}

void Image::blur(int s)
{
	float kernal[3][3] = { {1,2,1},
						  {2,4,2},
						  {1,2,1}
	};
	for (int i = 0; i < s; i++)
	{
		applyKernal(kernal);
	}
}
void Image::applyKernal(float kernal[3][3])
{
	unsigned char t[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			t[i][j] = getPixelByKernal(kernal, i, j);
		}
	}
	copyFrom(t);
}
unsigned char Image::getPixelByKernal(float kernal[3][3], int x, int y)
{
	float weightSum = 0;
	float pixel = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			weightSum += kernal[i][j];
			pixel += kernal[i][j] * getPixelSafe(x + i - 1, y + j - 1);
		}
	}
	weightSum = weightSum != 0 ? weightSum : 1;
	pixel /= weightSum;
	pixel = pixel > 0 ? pixel : 0;
	pixel = pixel < 255 ? pixel : 255;
	return pixel;
}
// return pixel at a position or at border if the position is out of image boundry
unsigned char Image::getPixelSafe(int i, int j)
{
	i = i > 0 ? i : 0;
	i = i < SIZE ? i : SIZE - 1;
	j = j > 0 ? j : 0;
	j = j < SIZE ? j : SIZE - 1;
	return image[i][j];
}
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
	float transformation[2][2];
	float skewMatrix[2][2] = { { 1,0},
						{tan(-degree * 3.14 / 180),1} };
	float scalerMatrix[2][2] = { { scale,0},
					{0,1} };
	combineTransformations(transformation, skewMatrix, scalerMatrix);
	trasform(transformation, 0, SIZE - 1);
}
void Image::skewRight(float degree)
{
	float scale = 1 / (1 + tan(degree * 3.14 / 180));
	float transformation[2][2];
	float skewMatrix[2][2] = { { 1,tan(-degree * 3.14 / 180)},
						{0,1} };
	float scalerMatrix[2][2] = { { 1,0},
					{0,scale} };
	combineTransformations(transformation, skewMatrix, scalerMatrix);
	trasform(transformation, SIZE - 1);
}
// combine two linear transformations ORDER IS IMPORTANT!
void Image::combineTransformations(float output[2][2], float first[2][2], float second[2][2])
{
	output[0][0] = second[0][0] * first[0][0] + second[1][0] * first[0][1];
	output[0][1] = second[0][1] * first[0][0] + second[1][1] * first[0][1];
	output[1][0] = second[0][0] * first[1][0] + second[1][0] * first[1][1];
	output[1][1] = second[0][1] * first[1][0] + second[1][1] * first[1][1];

}
// performs a linear transformation on the image
void Image::trasform(float transformation[2][2], int centreX, int centreY)
{
	// sets an image with white color for areas outside image boundry
	unsigned char t[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			t[SIZE][SIZE] = SIZE - 1;
		}
	}
	// apply the transformation
	for (int i = 0 - centreX; i < SIZE - centreX; i++)
	{
		for (int j = 0 - centreY; j < SIZE - centreY; j++)
		{
			//matrix multiplication
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
	// copy the transfotmed image back
	copyFrom(t);
}
void Image::Shuffle_Image()
{
 int input,Vertical,Vertical_Start,Horizontal,Horizontal_Start;
 int LoopStartH=0;
 int LoopStartV=0;
 int Half=SIZE/2;
 unsigned char image2[SIZE][SIZE];
 cout<<"please enter the order of quarters";
 for(int i =0;i<4;i++)
 {
	switch(i)
	{
		case 0:
		LoopStartH=0;
		LoopStartV=0;
		 break;
		case 1:
		LoopStartH=Half;
		LoopStartV=0;
		 break;
		case 2:
		LoopStartH=0;
		LoopStartV=Half;
		 break;
		case 3:
		LoopStartH=Half;
		LoopStartV=Half;
		 break;
	}
	cin>>input;
	switch(input)
	{
		case 1:
		Horizontal_Start=0;
		Vertical_Start=0;
		 break;
		case 2:
		Horizontal_Start=Half;
		Vertical_Start=0;
		 break;
		case 3:
		Horizontal_Start=0;
		Vertical_Start=Half;
		 break;
		case 4:
		Horizontal_Start=Half;
		Vertical_Start=Half;
		 break;
	}
	for(int j=0;j<Half;j++)
		{
			for(int k=0;k<Half;k++){
				image2[LoopStartH+j][LoopStartV+k]=image[Horizontal_Start+j][Vertical_Start+k];
			}
		}
 }
 copyFrom(image2);
}