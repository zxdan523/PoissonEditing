#include <iostream>
#include "ImageIO.h"
#include "Matrix.h"
int main(int argc,char** argv)
{
	Image img,img2;
	float kernel1[9]={1.0/9,1.0/9,1.0/9,
			1.0/9,1.0/9,1.0/9,
			1.0/9,1.0/9,1.0/9};
	float kernel2[9]={1,0,-1,
			 0,0,0,
			 -1,0,1};
	float kernel3[9]={0,-1,0,
			-1,5,-1,
			0,-1,0};
	float kernel4[9]={1.0/16,2.0/16,1.0/16,
			2.0/16,4.0/16,2.0/16,
			1.0/16,2.0/16,1.0/16};
	float kernel5[9]={0,1,0,
			1,-4,1,
			0,1,0};
	float kernel6[9]={-1,-1,-1,
			-1,8,-1,
			-1,-1,-1};


	/*if(argc>1)
	{
		importBMP(argv[1],img);
		img2=img.convolution(kernel1,3);
		exportBMP("../data/blur.bmp",img2);
		img2=img.convolution(kernel2,3);
		exportBMP("../data/edge1.bmp",img2);
		img2=img.convolution(kernel3,3);
		exportBMP("../data/sharp.bmp",img2);
		img2=img.convolution(kernel4,3);
		exportBMP("../data/guassian_blur.bmp",img2);
		img2=img.convolution(kernel5,3);
		exportBMP("../data/edge2.bmp",img2);
		img2=img.convolution(kernel6,3);
		exportBMP("../data/edge3.bmp",img2);
	}*/


	if(argc>2)
	{
		importBMP(argv[1],img);
		importBMP(argv[2],img2);
		Image result=img.merge(img2,150,250,25,25,250,250);
		result=result.merge(img2,150,250,25,25,200,100);
		exportBMP("../data/merge.bmp",result);
	}
	return 0;
}
