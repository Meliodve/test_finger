#pragma once
#include "MyString.h"

// �ѳ�Ϊw,��Ϊh��ͼƬpData,�浽��ǰĿ¼��dirnameĿ¼��,�ļ�����filename
bool saveBmp(int w,int h,uint8_t* pData,MyString dirname,MyString filename);

// ��dataPacket������ݵ���ͼƬ�浽dir·����
void saveImage(MyString dir,DataPacket dataPacket);

// ��������ֱ��ͼ,����Ϊw*h��pData,���Ϊhw*hh��Histogram
void generateHistogram(uint8_t* Histogram,int hw,int hh,uint8_t* pData,int w,int h);

// ��w*h��src��ͼƬ�Ŵ�һ��,�浽dest��
void imgSizeX2(uint8_t* src,int w,int h,uint8_t* dest);
