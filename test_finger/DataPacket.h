#pragma once
#include"stdafx.h"

class DataPacket{
public:
    DataPacket(const void* d,int l);
    DataPacket();

    //����֮�����
    void Destruction();
    bool isValid();
    int size();
    BYTE* getPointer();
    BYTE* getNewArray();
    void readData(int readByteSize);
    bool haveData();
private:
    //���ݰ�
    BYTE* data;
    //���ݰ�����
    int   len;
    //�Ѷ��ֽ���
    int   read;
};