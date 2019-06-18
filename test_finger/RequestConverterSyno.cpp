#include "stdafx.h"
// ���屾�ļ������������DataPacketSyno�����ʽ��
typedef struct DataPacketSyno Request;

// ȷ�������ת����������,�Ϳ�Э��ѡ���ǲ���SYNO
bool RequestConverterSyno::checkProtocol(DataPacket dataPacket){
    return getProtocol()==SYNO;
}

// Karl<2019��5��19��13:21:47>��:
// ���쳣�ĺô�:
// ����if/else����try/catch
// ���Էֿ�����ҵ���߼����������,��߿ɶ���
// ���Ҳ�������쳣����ķ���ֵ


// ������ڲ�ָ��ת��Ϊ��Ӧ��������
int ToSyno(int cmdCode){
    switch(cmdCode){
        case SII(GetRawImage):
            return __SCC(Syno,GetImage);
        case SII(UpImage):
            return __SCC(Syno,UpImage);
        case SII(GenChar):
            return __SCC(Syno,GenChar);
        case SII(RegModel):
            return __SCC(Syno,RegModel);
        case SII(StoreChar):
            return __SCC(Syno,StoreChar);
        case SII(GetEnrollImage):
            return __SCC(Syno,GetEnrollImage);
        case SII(Search):
            return __SCC(Syno,Search);
        case SII(ReadIndexTable):
            return __SCC(Syno,ReadIndexTable);
        case SII(Match):
            return __SCC(Syno,Match);
        case SII(LoadChar):
            return __SCC(Syno,LoadChar);
        case SII(DeleteChar):
            return __SCC(Syno,DeleteChar);
        default:
            ASF_ERROR(6);
            throw 0;
    }
}

// ��У���
void getSum(Request& r){
    unsigned char* p=(unsigned char*)&r;
    r.sum=0;
    for(int i=6;i<6+3+r.len;i++){
        r.sum+=p[i];
    }
}

// SYNO��ת������
std::vector<DataPacket> RequestConverterSyno::convert(int cmdCode,uint8_t* data,uint16_t len){
    std::vector<DataPacket> ret;
    try{
        cmdCode=ToSyno(cmdCode);
    } catch(...){
        return ret;
    }

    Request request;

    const int headLength=sizeof(request)-sizeof(request.data);
    const int dataLength=sizeof(request.data);

    // head & address
    memcpy(request.head,"\xEF\x01",2);
    memset(&request.address,-1,sizeof(request.address));

    // cmd_data = cmdCode + data
    uint8_t* cmd_data=new uint8_t[len+1];
    cmd_data[0]=cmdCode;
    memcpy(cmd_data+1,data,len);
    len+=1;

    // len & sign
    request.len=dataLength;
    request.sign=SynoSign::Command;

    uint8_t* p=cmd_data;
    do{
        // ���len����,����ʣ���len
        if(len<=dataLength){
            request.len=len;
        }

        // data
        memcpy(request.data,p,request.len);
        p+=request.len;
        len-=request.len;

        // sum
        getSum(request);
        int before_len=request.len;

        // ��С��ת��
        request.convert();
        ret.push_back(DataPacket(&request,headLength+before_len));
    } while(len>0);
    delete[] cmd_data;
    return ret;
}
