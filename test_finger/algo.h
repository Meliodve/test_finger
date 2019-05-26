#pragma once
#include"stdafx.h"

//ö������ ����,���ڿ��ƿؼ��Ŀ�����
enum action{
    actInit,        //��ʼ��

    actOpeningPort,	//�򿪶˿���
    actClosingPort,	//�رն˿���
    actOpenedPort,	//���˶˿�
    actClosedPort,	//�ر��˶˿�

    actGetingImage,	//��ȡͼ����
    actGotImage,	//��ȡ��ͼ��
    actGetConImage,	//��ʼ����ȡͼ
    actStpGetImage,	//ֹͣ����ȡͼ
    actGetConBKI,	//��ʼ����ȡͼ
    actStpGetBKI,	//ֹͣ����ȡͼ
    actReadingReg,	//���Ĵ�����
    actReadedReg,	//�����˼Ĵ���
    actWritingReg,	//д�Ĵ�����
    actWritedReg	//д���˼Ĵ���
};

//����ͨ�ŷ�ʽ��Ͽ�
void updateCommunityWay();

//�Զ�����
void autoConnect();
//�Զ��Ͽ�����
void autoDisconnect();

//���ݶ������¿ؼ�������
void updateControlDisable(action a);

//��filePath��ͼ����ص�ͼƬ�ؼ���
void loadImage(CStatic* image,MyString filePath);

bool saveBmp(int w,int h,uint8_t* pData,MyString dirname,MyString filename);

void saveImage(MyString dir,DataPacket dataPacket);

void generateHistogram(uint8_t* Histogram,int hw,int hh,uint8_t* pData,int w,int h);

void imgSizeX2(uint8_t* src,int w,int h,uint8_t* dest);

uint16_t GetCRC16(const void*pSource,uint16_t len);
