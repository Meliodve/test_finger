#pragma once
#include"stdafx.h"

//��filePath��ͼ����ص�ͼƬ�ؼ���
void loadImage(CStatic* image,MyString filePath);

bool saveBmp(int w,int h,uint8_t* pData,MyString dirname,MyString filename);

void saveImage(MyString dir,DataPacket dataPacket);

void generateHistogram(uint8_t* Histogram,int hw,int hh,uint8_t* pData,int w,int h);

void imgSizeX2(uint8_t* src,int w,int h,uint8_t* dest);
