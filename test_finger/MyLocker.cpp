#include "stdafx.h"

// ������Դ����
MyLocker::MyLocker(int now,int sum){
    mutex=CreateSemaphore(0,now,sum,0);
    this->now=now;
}

// Pԭ��
void MyLocker::lock(){
    WaitForSingleObject(mutex,-1);
    now--;
}

// Vԭ��
void MyLocker::unlock(){
    ReleaseSemaphore(mutex,1,0);
    now++;
}

// ����true�����������Դ���ľ�
bool MyLocker::islock(){
    return now==0;
}
