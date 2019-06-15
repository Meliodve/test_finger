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

// ִ����һ������,������int&
void ExecFlowRef(int& result);
// ִ����һ������,������int
void ExecFlowVal(int result=0);
// ִ�е�һ������,������int
void ExecStart(int result=0);
// ִ�����һ������,������int
void ExecEnd(int result=0);