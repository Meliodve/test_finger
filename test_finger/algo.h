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

//ö�ٴ��� exist���ش��ڵĴ���,useful���ؿ��еĴ���,used���ر�ռ�õĴ���
void enumerateSerialPorts(CUIntArray& exist,CUIntArray& useful,CUIntArray& used);

//����ͨ�ŷ�ʽ��Ͽ�
void updateCommunityWay();

//log�ĵ�һ������ѡ��
#define LOGU 0			//�û�����Ϣ,���û���ʾ����Ϣ
#define LOGE 1			//������Ϣ
#define LOGW 2			//���漶��Ϣ
#define LOGD 3			//���Լ���Ϣ
#define LOGT 4			//��ʱ����Ϣ
//д����־ CString����
void log(int level,CString info);
//д����־ printf���
void log(int level,const char* format,...);

//���ݶ������¿ؼ�������
void updateControlDisable(action a);

//��filePath��ͼ����ص�ͼƬ�ؼ���
void loadImage(WCHAR* filePath);

bool saveBmp(int height,int width,BYTE*pData,CString dir,CString path);

//��ϴ���ڰ��ĺ���,�Ѱ�ͷ��У����ϴ��,���������ݷ���packetData
void getDataFromPacket();
