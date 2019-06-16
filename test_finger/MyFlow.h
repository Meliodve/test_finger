#pragma once
#include "MyDefine.h"
#include <functional>

//����true������Լ���ִ����һ������,false����ִ��֮���ж�
#define FlowFunction_t _Function_t(bool,int&)

class MyFlow{
public:
    // β�巨���һ������,flowID�������ȷ�ᱨ��
    void add(int flowID,FlowFunction_t flow);
    // ִ�е�һ������,������int
    void start(int result=0);
    // ִ�����һ������,������int
    void terminate(int result=0);
    // ִ����һ������,������result����
    void execRef(int& result);
    // ִ����һ������,������resultֵ
    void execVal(int result=0);
    // �������
    void clear();
    // �������̰ٷֱ�
    double percent();
    // ������һ������
    bool next();
    // ������һ������
    bool prev();
    // ������������
    bool jump(int flowID);
private:
    // ��ǰ���̵�����
    std::vector<FlowFunction_t> flowVec;
    // ��ǰ���̵�ID
    int flowID;
};

// ��ǰ����
extern MyFlow flow;
