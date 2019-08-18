#include "MyThread.h"
#include <vector>
#include "MyLocker.h"

// ���tmpΪ��,��ô�߳̽�������Զ��ͷ�,����ֻ��newû��delete
MyThread::MyThread(ThreadFunction_t pFunction,bool tmp){
    pf=pFunction;
    temporary=tmp;
}

// ���������ͷŵĽṹ��
struct temporaryParam{
    ThreadFunction_t pf;
    MyThread* beDelete;
};

// ��Ҫ�����ͷŵ���ʱ�߳�����
std::vector<temporaryParam> TPVec;

// ����ͣס���߳�ֱ�����̻߳��size֮���ټ���
MyLocker getSize(0,1);

// �����߳�
bool MyThread::start(){
    if(temporary){
        // ��һ��Vec�����ǲ����п�λ��
        bool needPushBack=true;
        int posInVec;
        for(int i=0;i<TPVec.size();i++){
            if(TPVec[i].beDelete==0){
                TPVec[i].pf=pf;
                TPVec[i].beDelete=this;
                needPushBack=false;
                posInVec=i;
                break;
            }
        }
        // û�п�λ��,push_backһ��
        if(needPushBack){
            TPVec.push_back(temporaryParam{pf,this});
            posInVec=TPVec.size()-1;
        }
        // ���߳�
        thread=CreateThread(0,0,temporaryRun,&posInVec,0,0);
        getSize.lock();
    } else{
        thread=CreateThread(0,0,run,&pf,0,0);

    }
    return thread!=0;
}

// �ر��߳�
bool MyThread::terminate(){
    if(thread){
        TerminateThread(thread,-1);
        CloseHandle(thread);
        thread=0;
        return true;
    }
    return false;
}

// �����߳��Ƿ�����
bool MyThread::isRun(){
    return thread!=0;
}

// ��ͨ�߳����к���
DWORD WINAPI MyThread::run(LPVOID params){
    (*(ThreadFunction_t*)params)();
    return 0;
}

// ���ͷ��߳����к���
DWORD WINAPI MyThread::temporaryRun(LPVOID params){
    // ��Ҫ�����Ҫִ�е���ʱ�߳����������±�
    int size=*(int*)params;
    getSize.unlock();
    TPVec[size].pf();
    delete TPVec[size].beDelete;
    TPVec[size].beDelete=0;
    return 0;
}
