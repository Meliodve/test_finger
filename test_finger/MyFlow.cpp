#include "stdafx.h"

// ��ǰ����
MyFlow flow;

// β�巨���һ������,flowID�������ȷ�ᱨ��
void MyFlow::add(int flowID,FlowFunction_t flow){
    // ���flowID
    assert(flowID==this->flowVec.size());
    this->flowVec.push_back(flow);
}

// ִ�е�һ������,������int
void MyFlow::start(int result){
    this->flowID=0;
    this->execVal(result);
}

// ִ�����һ������,������int
void MyFlow::terminate(int result){
    this->flowID=this->flowVec.size()-1;
    this->execVal(result);
}

// ִ����һ������,������result����
void MyFlow::execRef(int & result){
    while(this->flowVec.size()>this->flowID&&this->flowID>=0){
        if(!this->flowVec[this->flowID](result)){
            break;
        }
    }
}

// ִ����һ������,������resultֵ
void MyFlow::execVal(int result){
    execRef(result);
}

// �������
void MyFlow::clear(){
    this->flowID=0;
    this->flowVec.clear();
}

double MyFlow::percent(){
    return (this->flowID+1.0)/this->flowVec.size();
}

bool MyFlow::next(){
    return jump(this->flowID+1);
}

bool MyFlow::prev(){
    return jump(this->flowID-1);
}

bool MyFlow::jump(int flowID){
    if(this->flowVec.size()>flowID&&flowID>=0){
        this->flowID=flowID;
        return true;
    }
    return false;
}
