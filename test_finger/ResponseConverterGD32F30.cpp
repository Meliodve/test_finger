#include "stdafx.h"
// ���屾�ļ�����Ļ�Ӧ��ResponsePacketGD32F30�����ʽ��
typedef ResponsePacketGD32F30 Response;

// �鿴���ݰ��Ŀ�ͷȷ��Э��
bool ResponseConverterGD32F30::checkProtocol(DataPacket dataPacket){
    if(!dataPacket.haveData()){
        return false;
    }
    uint8_t*p=dataPacket.getPointer();
    return p[0]==0xEF&&p[1]==0x02;
}

// GD32��������ϴ����,��������ݲ���
DataPacket ResponseConverterGD32F30::convert(DataPacket& data){
    const int size=Response::Header+Response::Checker;
    int tmpLength=0;

    // ���뻺����
    uint8_t* tmpArray=new uint8_t[data.readSize()];
    Response* pData=(Response*)data.getPointer();
    while(checkProtocol(data)){
        // ת������,����Ϊ��Ӧ��Length
        memcpy(tmpArray+tmpLength,pData->Sendbuf,pData->Length);
        tmpLength+=pData->Length;
        data.readData(size+pData->Length);
        pData=(Response*)data.getPointer();
    }
    DataPacket ret(tmpArray,tmpLength);
    delete[] tmpArray;
    return ret;
}

// ����������
int ResponseConverterGD32F30::getCmdCode(DataPacket data){
    return ((Response*)data.getPointer())->CMD;
}
