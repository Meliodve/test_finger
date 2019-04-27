#pragma once
#include"stdafx.h"

CommDevice::CommDevice(){}

int CommDevice::getConnectId(){
    return id;
}

bool CommDevice::connect(int id,int baud){
    CString way;
    way.Format(_T("\\\\.\\COM%d"),id);//�õ��˿ڵ�ַ
    LONG retCode=ERROR_SUCCESS;

    if(retCode==ERROR_SUCCESS){
        retCode=serial.Open(way,2048,2048,true);
    }
    //����������������Ĭ�ϲ���
    if(retCode==ERROR_SUCCESS){
        retCode=serial.Setup((CSerial::EBaudrate)baud);
    }
    if(retCode==ERROR_SUCCESS){
        retCode=serial.SetMask(CSerial::EEventRecv);
    }
    if(retCode==ERROR_SUCCESS){
        serial.Purge();
    }
    MyLog.print(Log::LOGU,"����COM%d%s",id,retCode==ERROR_SUCCESS?"�ɹ�":"ʧ��");
    if(retCode==ERROR_SUCCESS){
        this->id=id;
    }
    return retCode==ERROR_SUCCESS;
}

bool CommDevice::disconnect(){
    int ret=serial.Close();
    MyLog.print(Log::LOGU,"�Ͽ����ӳɹ�");
    if(ret==ERROR_SUCCESS){
        id=0;
        return true;
    } else{
        ASF_WARNING(5);
        return false;
    }
}

void CommDevice::request(std::vector<DataPacket>& const dataPacket){
    DWORD sendCnt;
    LONG result;
    std::vector<DataPacket>::iterator it;
    for(it=dataPacket.begin();it!=dataPacket.end();it++){
        result=serial.Write(it->data,it->len,&sendCnt,NULL,10*1000);
        it->Destruction();
    }
}
