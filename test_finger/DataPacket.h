#pragma once

class DataPacket{
public:
    DataPacket(const void* d,int l);
    DataPacket();

    // ����֮�����
    void Destruction();
    // �Ƿ���Ч
    bool isValid() const;
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