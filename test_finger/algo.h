#pragma once
#include"stdafx.h"

//ö������ ����,���ڿ��ƿؼ��Ŀ�����
enum action{
	actInit,        //��ʼ��
	actOpeningPort,	//�򿪶˿���
	actClosingPort,	//�رն˿���
	actOpenedPort,	//���˶˿�
	actClosedPort	//�ر��˶˿�
};

//ö�ٴ��� exist���ش��ڵĴ���,useful���ؿ��еĴ���,used���ر�ռ�õĴ���
void enumerateSerialPorts(CUIntArray& exist,CUIntArray& useful,CUIntArray& used);

//����ͨ�ŷ�ʽ��Ͽ�
void updateCommunityWay();

//д����־ CString����
void log(CString info);
//д����־ printf���
void log(const char* format,...);

//���ݶ������¿ؼ�������
void updateControlDisable(action a);

//
void loadImage(WCHAR* filePath);