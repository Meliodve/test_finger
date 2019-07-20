#pragma once
#include"stdafx.h"

// ȫ��Ψһ�������㲥����
ListenerBoardcast listenerBoardcast;

// ������,��ʼ����Ҫ������map
ListenerBoardcast::ListenerBoardcast(){
    __BCL(GD32,GD32F30,GetRawImage);
    __BCL(GD32,GD32F30,GetTestImage);
    __BCL(GD32,GD32F30,ReadRegister);
    __BCL(GD32,GD32F30,DeviceInfo);

    __BCL(0,LOG,Info);
    __BCL(0,LOG,MeasureTimeStart);
    __BCL(0,LOG,MeasureTimeEnd);
    __BCL(0,LOG,AdvDbg_AdjImg);

    __BCL(SYNO,Syno,GetImage);
    __BCL(SYNO,Syno,UpImage);
    __BCL(SYNO,Syno,GetEnrollImage);
    __BCL(SYNO,Syno,GenChar);
    __BCL(SYNO,Syno,RegModel);
    __BCL(SYNO,Syno,StoreChar);
    __BCL(SYNO,Syno,Search);
    __BCL(SYNO,Syno,ReadIndexTable);
    __BCL(SYNO,Syno,Match);
    __BCL(SYNO,Syno,LoadChar);
    __BCL(SYNO,Syno,DeleteChar);
}

// �����¼����Ӧ�ļ�����
void ListenerBoardcast::attach(int event,ICommListener* listener){
    if(!m.count(event)){
        m[event]=std::vector<ICommListener*>();
    }
    m[event].push_back(listener);
}

// �㲥�¼�
void ListenerBoardcast::boardcast(int event,DataPacket response){
    std::vector<ICommListener*>::iterator it;
    if(isFreeRequest){
        isFreeRequest--;
        std::string str="data:";
        uint8_t* ptr=response.getPointer();
        for(int i=0;i<response.readSize();i++){
            str+=MyString::Format("%02x,",(int)ptr[i]);
        }
        str.pop_back();
        MyLog::user("�յ�CmdCode=%02x������,%s",event,str.c_str());
    }
    for(it=m[event].begin();it!=m[event].end();it++){
        if((*it)->accept()){
            (*it)->listen(response);
        }
    }
}

// ������,�����Ǻ궨����ַ���,���������������ʲôЭ���½��м���
ICommListener::ICommListener(const char* protocol){
    this->protocol=protocol;
}

// ������Լ���,������
bool ICommListener::accept(){
    if(protocol==0){
        return true;
    } else{
        return getProtocol()==protocol;
    }
}
