#include"stdafx.h"

DataPacket::DataPacket(const void * d,int l){
    data=new uint8_t[l+1];
    memset(data,0,l+1);
    len=l;
    read=0;
    memcpy(data,d,l);
}

DataPacket::DataPacket(){
    data=0;
    len=0;
    read=0;
}

// ����֮�����
void DataPacket::Destruction(){
    if(isValid()){
        delete data;
        len=0;
        read=0;
    }
}

// �Ƿ���Ч
bool DataPacket::isValid() const{
    return len>read;
}

// �������ݴ�С
int DataPacket::size() const{
    return len;
}

// ���ڻ�ʣ��������
int DataPacket::readSize() const{
    return len-read;
}

// ��ÿɶ����ݵ���ʼ��ַ
uint8_t * DataPacket::getPointer() const{
    return data+read;
}

// ����һЩ����
void DataPacket::readData(int readByteSize){
    read+=readByteSize;
}

// �ж��Ƿ��пɶ�����
bool DataPacket::haveData() const{
    return len>read;
}
