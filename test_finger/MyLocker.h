#pragma once
#include <Windows.h>

class locker{
public:
    //������Դ����
    locker(int now=1,int sum=1);
    //Pԭ��
    void lock();
    //Vԭ��
    void unlock();
    //����true�����������Դ���ľ�
    bool islock();
private:
    HANDLE mutex;
    int now;
};
