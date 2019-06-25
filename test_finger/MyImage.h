#pragma once
#include "MyString.h"

// ��dataPacket������ݵ���ͼƬ��ΪͼƬ
void saveImage(DataPacket dataPacket);

// ��dataPacket������ݵ���ͼƬ��Ϊ����ͼƬ
void saveBGImg(DataPacket dataPacket);

// ��������ֱ��ͼ,����Ϊw*h��pData,���Ϊhw*hh��Histogram
void generateHistogram(int w,int h,uint8_t* pData,int hw,int hh,uint8_t* Histogram);

// ��w*h��src��ͼƬ�Ŵ�һ��,�浽dest��
void imgSizeX2(int w,int h,uint8_t* src,uint8_t* dest);

// ��w*h��pDataͼƬ�浽id����ʱͼƬ��
bool saveTempImage(int w,int h,uint8_t* pData,int id);

void imgResize(int w,int h,uint8_t* src,int a,int b,uint8_t* dest);