#pragma once
#include"stdafx.h"

class DataPacket{
public:
    DataPacket(const void* d,int l);
    DataPacket();

    //����֮�����
    void Destruction();
    //�Ƿ���Ч
    bool isValid();
    //�������ݴ�С
    int size();
    //���ڻ�ʣ��������
    int readSize();
    //��ÿɶ����ݵ���ʼ��ַ
    BYTE* getPointer();
    //����һЩ����
    void readData(int readByteSize);
    //�ж��Ƿ��пɶ�����
    bool haveData();
private:
    //���ݰ�
    BYTE* data;
    //���ݰ�����
    int   len;
    //�Ѷ��ֽ���
    int   read;
};