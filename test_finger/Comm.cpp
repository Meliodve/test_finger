#include "stdafx.h"

HANDLE dataQueueMutex=CreateMutex(0,0,0);
std::queue<DataPacket> dataQueue;
BYTE buffer[1<<18];
Comm comm;

Comm::Comm(){
    id=0;
    type=DataPacket();
    listenThread=0;
}

DataPacket Comm::getType(){
    return type;
}

int Comm::getConnectId(){
    return id;
}

DWORD WINAPI ResponseThread(LPVOID params){
    DataPacket dataPacket;
    while(1){
        WaitForSingleObject(dataQueueMutex,INFINITE);
        if(dataQueue.size()){
            dataPacket=dataQueue.front();
            dataQueue.pop();
        }
        ReleaseMutex(dataQueueMutex);
        while(dataPacket.isValid()){
            int cmdCode=converterBoardcast.ResponseGetCmdCode(dataPacket);
            //û��Э�����ת��ʣ�µ�������,���ݷ���
            if(cmdCode==-1){
                break;
            }
            auto data=converterBoardcast.ResponseConvert(dataPacket);
            listenerBoardcast.boardcast(cmdCode,data);
            data.Destruction();
        }
        dataPacket.Destruction();
    }
}

bool Comm::connect(int id,int baud){
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
        retCode=serial.SetupReadTimeouts(CSerial::EReadTimeoutNonblocking);
    }
    if(retCode==ERROR_SUCCESS){
        serial.Purge();
    }
    MyLog.print(Log::LOGU,"����COM%d%s",id,retCode==ERROR_SUCCESS?"�ɹ�":"ʧ��");
    if(retCode==ERROR_SUCCESS){
        responseThread=CreateThread(0,0,ResponseThread,0,0,0);
        startListen();
        this->id=id;
    }
    return retCode==ERROR_SUCCESS;
}

bool Comm::disconnect(){
    TerminateThread(responseThread,-1);
    CloseHandle(responseThread);
    responseThread=0;
    terminateListen();

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

void Comm::request(int CmdCode,uint8_t * Data,uint16_t Len){
    auto converter=converterBoardcast.RequestConvert(getType());
    if(converter){
        auto dataPacket=converter->convert(CmdCode,Data,Len);
        for(auto it=dataPacket.begin();it!=dataPacket.end();it++){
            serial.Write(it->getPointer(),it->size());
            it->Destruction();
        }
    } else{
        ASF_ERROR(3);
    }
}

DWORD WINAPI ListenThread(LPVOID params){
    CSerial* serial=(CSerial*)params;
    while(serial->IsOpen()){
        DWORD cnt;
        LONG result;
        result=serial->Read(buffer,1<<18,&cnt);
        if(result==ERROR_SUCCESS){
            WaitForSingleObject(dataQueueMutex,INFINITE);
            dataQueue.push(DataPacket(buffer,cnt));
            ReleaseMutex(dataQueueMutex);
        }
    }
    return 0;
}

bool Comm::startListen(){
    if(listenThread==0){
        listenThread=CreateThread(0,0,ListenThread,&serial,0,0);
    }
    return listenThread!=0;
}

bool Comm::terminateListen(){
    if(listenThread){
        bool ret=TerminateThread(listenThread,-1);
        CloseHandle(listenThread);
        listenThread=0;
        return ret;
    }
    return true;
}
