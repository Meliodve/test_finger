#pragma once
#include"stdafx.h"

// �������ӿ�
class ICommListener{
public:
    // ������,�����Ǻ궨����ַ���,���������������ʲôЭ���½��м���
    ICommListener(const char* protocol=0);
    // ������Լ���,������
    bool accept();
    // ����ʵ���߼�
    virtual void listen(DataPacket response)=0;
private:
    // Э���ַ���
    const char* protocol;
};

// �������㲥
class ListenerBoardcast{
public:
    // ������,��ʼ����Ҫ������map
    ListenerBoardcast();
    // �����¼����Ӧ�ļ�����
    void attach(int event,ICommListener*listener);
    // �㲥�¼�
    void boardcast(int event,DataPacket response);
private:
    // ���������ϵ��map
    std::map<int,std::vector<ICommListener*>>m;
};

// ȫ��Ψһ�������㲥����
extern ListenerBoardcast listenerBoardcast;
