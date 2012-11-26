// кусок программы для обсчета psnr
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>


int PSNR1(int max, long double mse)
{
	int psnr;

	//max=255;
	psnr=20*(log10(max/sqrt(mse)));

	return psnr;
}

// RGB: shift = 3
// RGBA, RGB4: shift = 4
int MSECALC(int width, int heigth, int shift, unsigned char *r1, unsigned char *r2)
{
	int sum = 0;
	
	for(int i=0; i<width;i++)
	{
		for(int j=0;j<heigth;j++)
		{
			// здесь должны быть получены данные r,g,b для обсчета по формуле далее
			sum += ((*r2) - (*r1))*((*r2) - (*r1));// обсчет mse
			r1 += shift;
			r2 += shift;
		}
		
	}

	return sum;// передаем полученное значение mse в функцию для обсчета psnr	
}

int BMPLOAD(char *filename, unsigned int &width, unsigned int &height, unsigned char **data)
{
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;

	FILE *file = fopen(filename, "rb");
    if (!file)                              
	{
		printf("Image could not be opened\n"); return 0;
	}

	if ( fread(header, 1, 54, file) != 54 )
	{
		printf("Not a correct BMP file\n"); return 0;
	}
	
	if ( header[0]!='B' || header[1]!='M' ){
		   printf("Not a correct BMP file\n");return 0;}

    dataPos =   *(int*)(header + 0x0A);
    imageSize = *(int*)(header + 0x22);
    width =     *(int*)(header + 0x12);
    height =    *(int*)(header + 0x16);

	if (imageSize==0)  
	   imageSize = width * height * 3;

	if (dataPos==0)      
		dataPos=54;

	*data = new unsigned char [imageSize];

	fseek(file, dataPos, SEEK_SET);

	fread(*data,1,imageSize,file);
	fclose(file);

	return 1;
}

int main(int argc, char** argv)
{
	unsigned char *image1;
	unsigned int width1;
	unsigned int height1;
	unsigned char *image2;
	unsigned int width2;
	unsigned int height2;
	int shift=3;
	unsigned char *data;
	unsigned char *mse;
	BMPLOAD(argv[1], width1, height1, &image1);
	BMPLOAD(argv[2], width2, height2, &image2);
	unsigned int MSE=MSECALC(&width1, &height1, shift=3, &r1, &r2);// kak peredat' v msecalc znacheniya r1 i r2?
	system ("pause");

}
