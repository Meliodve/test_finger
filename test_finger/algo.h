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

//��CString���ͱ������char*�ͱ���
//ע��,��������static,�����εĻ�
//��Ҫѧ�������,�Լ�д����ת��
char* CString2char(CString&c);

//ö�ٴ��� useful���ؿ��еĴ���,used���ر�ռ�õĴ���
void enumerateSerialPorts(CUIntArray* idle,CUIntArray* buzy);

//����ͨ�ŷ�ʽ��Ͽ�
void updateCommunityWay();

//���ݶ������¿ؼ�������
void updateControlDisable(action a);

//��filePath��ͼ����ص�ͼƬ�ؼ���
void loadImage(WCHAR* filePath);

bool saveBmp(int height,int width,BYTE*pData,CString dir,CString path);

void saveImage(CString x);