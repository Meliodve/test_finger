#include "stdafx.h"

//��ǰ���̵�ID
int FlowID=0;
//��ǰ���̵�����
std::vector<FlowFunction_t>Flow;

// ִ����һ������,������int&
void ExecFlowRef(int& result){
    while(FlowID>=0&&FlowID<Flow.size()&&Flow[FlowID](result));
}

// ִ����һ������,������int
void ExecFlowVal(int result){
    while(FlowID>=0&&FlowID<Flow.size()&&Flow[FlowID](result));
}

// ִ�е�һ������,������int
void ExecStart(int result){
    FlowID=0;
    ExecFlowVal(result);
}

// ִ�����һ������,������int
void ExecEnd(int result){
    FlowID=Flow.size()-1;
    ExecFlowVal(result);
}
