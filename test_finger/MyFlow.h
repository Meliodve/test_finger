#pragma once
#include "MyDefine.h"

//����true������Լ���ִ����һ������,false����ִ��֮���ж�
#define FlowFunction_t _Function_t(bool,int&)
#define __FlowFunction(arg) _Function(bool,arg)
//����true������Լ���ִ����һ������,false����ִ��֮���ж�,idָ�������̵�ID
#define FlowFunction(id) __FlowFunction
//��ǰ���̵�ID
extern int FlowID;
//��ǰ���̵�����
extern std::vector<FlowFunction_t> Flow;

void ExecFlowRef(int& result);
void ExecFlowVal(int result=0);
void ExecStart(int result=0);
void ExecEnd(int result=0);