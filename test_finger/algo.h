#pragma once
#include"stdafx.h"

//ö������ ����,���ڿ��ƿؼ��Ŀ�����
enum action{
	actInit,        //��ʼ��
	actOpeningPort,	//�򿪶˿���
	actClosingPort,	//�رն˿���
	actOpenedPort,	//���˶˿�
	actClosedPort,	//�ر��˶˿�
	actGetConImage,	//��ʼ����ȡͼ
	actStpGetImage	//ֹͣ����ȡͼ
};

//ö�ٴ��� exist���ش��ڵĴ���,useful���ؿ��еĴ���,used���ر�ռ�õĴ���
void enumerateSerialPorts(CUIntArray& exist,CUIntArray& useful,CUIntArray& used);

//����ͨ�ŷ�ʽ��Ͽ�
void updateCommunityWay();

//log�ĵ�һ������ѡ��
#define LOGU 0			//�û�����Ϣ,���û���ʾ����Ϣ
#define LOGE 1			//������Ϣ
#define LOGW 2			//���漶��Ϣ
#define LOGD 3			//���Լ���Ϣ
//д����־ CString����
void log(int level,CString info);
//д����־ printf���
void log(int level,const char* format,...);

//���ݶ������¿ؼ�������
void updateControlDisable(action a);

//
void loadImage(WCHAR* filePath);

void saveBmp(int height,int width,BYTE*pData,CString path);