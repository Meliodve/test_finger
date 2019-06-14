#pragma once
#include"stdafx.h"

// Э��ת�����ӿ�
class ICommProtocolConverter{
public:
    // ȷ���Ƿ�����Ҫ�����Э��
    virtual bool checkProtocol(DataPacket dataPacket)=0;
};

// ����ת�����ӿ�
class ICommProtocolRequestConverter:public ICommProtocolConverter{
public:
    // ������+����ת��Ϊ�ֽ���
    virtual std::vector<DataPacket> convert(int CmdCode,uint8_t* Data,uint16_t Len)=0;
};

// ��Ӧת�����ӿ�
class ICommProtocolResponseConverter:public ICommProtocolConverter{
public:
    // ��ϴ���ݰ�,��ȡ���е�����
    virtual DataPacket convert(DataPacket& data)=0;
    // �������ݰ�,�������е�������
    virtual int getCmdCode(DataPacket data)=0;
};

// ת�����㲥
class ConverterBoardcast{
public:
    // ������
    ConverterBoardcast();
    // �������ת����
    ICommProtocolRequestConverter* RequestConvert();
    // ��ϴ���ݰ�,�������е�����
    DataPacket ResponseConvert(DataPacket& data);
    // �������ݰ�,��������������
    int ResponseGetCmdCode(DataPacket data);
private:
    // ���Ӽ���������ת����
    void attach(ICommProtocolRequestConverter* converter);
    // ���Ӽ�������Ӧת����
    void attach(ICommProtocolResponseConverter* converter);
    // ����ת��������
    std::vector<ICommProtocolRequestConverter*> requestVector;
    // ��Ӧת��������
    std::vector<ICommProtocolResponseConverter*> responseVector;
};

// ȫ��Ψһת�����㲥
extern ConverterBoardcast converterBoardcast;

// GD32��Sign
enum ProtocolSign{
    Unspecified,
    DataNotEnd,
    DataEnd,
};

// Syno��Sign
enum SynoSign{
    Command=1,
    NotEndData=2,
    ACK=7,
    EndData=8,
};
