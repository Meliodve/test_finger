#include"stdafx.h"

DataPacket::DataPacket(const void * d,int l){
    NEWA_INFO;
    data=new uint8_t[l+1];
    memset(data,0,l+1);
    len=l;
    read=0;
    memcpy(data,d,l);
}

DataPacket::DataPacket(std::vector<uint8_t>& v){
    len=v.size();
    NEWA_INFO;
    data=new uint8_t[len];
    memset(data,0,len);
    read=0;
    for(int i=0;i<len;i++){
        data[i]=v[i];
    }
}

DataPacket::DataPacket(){
    data=0;
    len=0;
    read=0;
}

// ����֮�����
void DataPacket::Destruction(){
    if(isValid()){
        DELA_INFO;
        delete[] data;
        len=0;
        read=0;
    }
}

// �Ƿ���Ч
bool DataPacket::isValid(){
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
