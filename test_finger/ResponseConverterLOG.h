#pragma once
#include"stdafx.h"

enum CmdCodeLOG{
    CmdCodeLOG_Info=0xCC00,
    CmdCodeLOG_MeasureTimeStart,
    CmdCodeLOG_MeasureTimeEnd,
};

#pragma pack(1)
struct DataPacketLOG{
    char Head[3];
    uint16_t Cmd;
    uint16_t Len;
    uint8_t Data[93];
    static const int Header=7;
    static const int Checker=0;
};
#pragma pack(4)

class ResponseConverterLOG:public ICommProtocolResponseConverter{
    virtual bool checkProtocol(uint16_t head) override;
    virtual DataPacket convert(DataPacket& data) override;
    virtual int getCmdCode(DataPacket data) override;
};
