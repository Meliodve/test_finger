#pragma once
#include <functional>
#include <Windows.h>

// �̻߳ص���������
#define ThreadFunction_t std::function<void(void)>
#define ThreadFunction [&]()

class MyThread{
public:
    // ���tmpΪ��,��ô�߳̽�������Զ��ͷ�,����ֻ��newû��delete
    MyThread(ThreadFunction_t pFunction,bool tmp=false);
    // �����߳�
    bool start();
    // �ر��߳�
    bool terminate();
    // �����߳��Ƿ�����
    bool isRun();
private:
    // �߳̾��
    HANDLE thread=0;
    // �̻߳ص�����
    ThreadFunction_t pf;
    // �Ƿ������ͷ��߳�
    bool temporary;
    // ��ͨ�߳����к���
    static DWORD WINAPI run(LPVOID params);
    // ���ͷ��߳����к���
    static DWORD WINAPI temporaryRun(LPVOID params);
};
