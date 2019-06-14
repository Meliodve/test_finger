#include"stdafx.h"

// ȫ��Ψһת�����㲥
ConverterBoardcast converterBoardcast;

// ������
ConverterBoardcast::ConverterBoardcast(){
    attach(new RequestConverterSyno());
    attach(new ResponseConverterSyno());

    attach(new RequestConverterGD32F30());
    attach(new ResponseConverterGD32F30());

    attach(new ResponseConverterLOG());
}

// ���Ӽ���������ת����
void ConverterBoardcast::attach(ICommProtocolRequestConverter * converter){
    requestVector.push_back(converter);
}

// ���Ӽ�������Ӧת����
void ConverterBoardcast::attach(ICommProtocolResponseConverter * converter){
    responseVector.push_back(converter);
}

// �������ת����
ICommProtocolRequestConverter* ConverterBoardcast::RequestConvert(){
    auto&v=requestVector;
    for(auto it=v.begin();it!=v.end();it++){
        if((*it)->checkProtocol(DataPacket())){
            return *it;
        }
    }
    return NULL;
}

// ��ϴ���ݰ�,�������е�����
DataPacket ConverterBoardcast::ResponseConvert(DataPacket & dataPacket){
    auto&v=responseVector;
    for(auto it=v.begin();it!=v.end();it++){
        if((*it)->checkProtocol(dataPacket)){
            return (*it)->convert(dataPacket);
        }
    }
    return DataPacket();
}

// �������ݰ�,��������������
int ConverterBoardcast::ResponseGetCmdCode(DataPacket dataPacket){
    auto&v=responseVector;
    for(auto it=v.begin();it!=v.end();it++){
        if((*it)->checkProtocol(dataPacket)){
            return (*it)->getCmdCode(dataPacket);
        }
    }
    return -1;
}
