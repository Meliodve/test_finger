#pragma once

class DataPacket{
public:
    DataPacket(const void* d,int l);
    DataPacket(std::vector<uint8_t>& v);
    DataPacket();

    // ����֮�����
    void Destruction();
    // �Ƿ���Ч
    bool isValid();
    // �������ݴ�С
    int size() const;
    // ���ڻ�ʣ��������
    int readSize() const;
    // ��ÿɶ����ݵ���ʼ��ַ
    uint8_t* getPointer() const;
    // ����һЩ����
    void readData(int readByteSize);
    // �ж��Ƿ��пɶ�����
    bool haveData() const;
private:
    // ���ݰ�
    uint8_t* data;
    // ���ݰ�����
    int   len;
    // �Ѷ��ֽ���
    int   read;
};