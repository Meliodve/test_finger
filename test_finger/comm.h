#pragma once
#include"stdafx.h"

// ͨ���豸 Communication Device
class Comm{
public:
    Comm();
    // ���ID
    int getConnectId();
    // ������λ��
    bool connect(int id=0,int baud=0);
    // �Ͽ�����λ��������
    bool disconnect();
    // ����λ����������(����)
    void request(int cmdCode,DataPacket packet=DataPacket());
    // ����request��������ʽ,�����Ļ�,�յ���Ӧ֮���ټ�����
    void setBlock(bool block);
private:
    // �������ݳ�Ա
    CSerial serial;
    // USB���ݳ�Ա
    CUsbPort usb;
    // 0:USB,>0:Serial,<0:None
    int id;
    // �Ƿ�λ������̬
    bool block;
    // ������̬�±�ֻ֤��һ���������ȥ
    MyLocker blockLocker;

    // ����ַ�Packet����Ӧ��Listener,��Packet��������
    MyThread* responseThread;
    // ���������λ��������,��Packet��������
    MyThread* listenThread;
    // ���豸�����ֽ���
    void sendBytes(uint8_t* data,int len);
    // ���豸�ж�ȡ�ֽ���,�����Ƿ��������
    bool readBytes(uint8_t* buffer,int blen,ULONG& cnt);
    // �����豸�Ƿ��
    bool isOpen();
};

// ȫ��Ψһͨ���豸
extern Comm comm;
// ��UsbPort.cpp�õ�,-1����δ����
extern int CommType;
