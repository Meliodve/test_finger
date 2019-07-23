#include "stdafx.h"
// ���屾�ļ�����Ļ�Ӧ��DataPacketSyno�����ʽ��
typedef DataPacketSyno Response;

// �鿴���ݰ��Ŀ�ͷȷ��Э��
bool ResponseConverterSyno::checkProtocol(DataPacket dataPacket){
    if(!dataPacket.haveData()){
        return false;
    }
    unsigned char* head=dataPacket.getPointer();
    return head[0]==0xEF&&head[1]==0x01;
}

// SYNO��������ϴ����,����Ƿ���ֵ+���ݲ���
DataPacket ResponseConverterSyno::convert(DataPacket& data){
    // ��Ϊ�д��С������,����ÿ�������ݶ���memcpy
    Response response;
    memcpy(&response,data.getPointer(),sizeof(response));

    // ���뻺����
    NEWA_INFO;
    uint8_t* arr=new uint8_t[data.readSize()];
    const int header=sizeof(Response)-sizeof(response.data)-sizeof(response.sum);
    int len=0;
    while(checkProtocol(data)){
        // ��С��ת��
        response.reconvert();

        // ת������,����Ϊ��Ӧ��len
        memcpy(arr+len,response.data,response.len);

        len+=response.len;
        data.readData(header+response.len);
        //TODO У��λ
        data.readData(2);
        if(response.sign==SynoSign::EndData){
            break;
        }
        memcpy(&response,data.getPointer(),sizeof(response));
    }
    DataPacket ret(arr,len);
    DELA_INFO;
    delete[] arr;
    return ret;
}

// ����������
int ResponseConverterSyno::getCmdCode(DataPacket data){
    return comm.blockQueue.back().first;
}
