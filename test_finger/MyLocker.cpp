#include "stdafx.h"

// ������Դ����
MyLocker::MyLocker(int now,int max){
    mutex=CreateSemaphore(0,now,max,0);
    this->now=now;
}

// Pԭ��
void MyLocker::lock(){
    WaitForSingleObject(mutex,-1);
    now--;
}

// Vԭ��
void MyLocker::unlock(){
    now++;
    ReleaseSemaphore(mutex,1,0);
}

// ����true�����������Դ���ľ�
bool MyLocker::islock(){
    return now==0;
}
