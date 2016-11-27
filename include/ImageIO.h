#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <memory>
#include <algorithm>
#include "Image.h"

void importBMP(std::string filePath,Image& img)
{
	std::ifstream bmp(filePath.c_str(),std::ifstream::binary);
	if(!bmp.is_open())
	{
		std::cout<<"Cannot find the file: "<<filePath.c_str()<<std::endl;
		return;
	}

	std::unique_ptr<uint8_t[]> head(new uint8_t[54]);
	bmp.read((char*)head.get(),54);
	int width,height;
	std::memcpy(&width,&head[18],4);
	std::memcpy(&height,&head[22],4);
	int size=3*height*width;
	std::unique_ptr<uint8_t[]> data(new uint8_t[size]);
	bmp.read((char*)data.get(),size);
	img=Image(width,height);
	std::transform(data.get(),data.get()+size,img.begin()->begin(),[](uint8_t val)
			{
				return (float)val/255.0f;
			});
	img.setHead(head.get(),54);
	bmp.close();
}

void exportBMP(std::string filePath,Image& img)
{
	std::ofstream bmp(filePath.c_str(),std::ofstream::binary);
	if(!bmp.is_open())
	{
		std::cout<<"Cannot write to the file: "<<filePath.c_str()<<std::endl;
		return;
	}

	bmp.write((const char*)img.getHead(),54);
	std::unique_ptr<uint8_t[]> data(new uint8_t[3*img.size()]);
	std::transform(img.begin()->begin(),img.end()->begin(),data.get(),[](float val)
			{
				return uint8_t(255*val);
			});
	bmp.write((const char*)data.get(),3*img.size());
	bmp.close();
}
#endif
