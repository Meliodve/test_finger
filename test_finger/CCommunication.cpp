#include"stdafx.h"
CSerial CCommunication::serial;
int CommType;

bool isUSB(){
    return cmbWay->GetCurSel()==0;
}

bool CCommunication::connect(int id,int baud){
    if(isUSB()){
        if(UsbPort.InitUsbPort(COMM_USB_MASS,"UD")){
            CommType=COMM_USB_MASS;
            cmbChipType->SetCurSel(1);
            bool ret=sendCommand(USR_CMD_GET_INFO);
            ret = waitForPacket(100*1000);
            return true;
        } else{
            CommType=-1;
            return false;
        }
    }
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
    return retCode==ERROR_SUCCESS;
}

bool CCommunication::disConnect(){
    if(isUSB()){
        return UsbPort.CloseUsbPort()==0;
    }
    int ret=serial.Close();
    if(ret==ERROR_SUCCESS){
        return true;
    } else{
        ASF_WARNING(5);
        return false;
    }
}

bool CCommunication::sendCommand(int CmdCode,uint8_t* Data,uint16_t Len){
    switch(cmbChipType->GetCurSel()){
        case 0:return sendCommand_Default(CmdCode,Data,Len);
        case 1:
            switch(CmdCode){
                case USR_CMD_GET_INFO:
                    return sendCommand_HangXin(USR_CMD_GET_INFO);
                    break;/*��о:����оƬ��Ϣ*/
                case CMD_GET_TEST_IMAGE:      break;/*��ñ���ͼƬ*/
                case CMD_DEVICE_RESET:        break;/*ϵͳ��λ*/
                case CMD_DETECT_FINGER:       break;/*̽��ָ��*/
                case CMD_GET_RAW_IMAGE:
                    sendCommand_HangXin(USR_CMD_GRAB_NO_CHECK);
                    waitForPacket(10*1000);
                    return sendCommand_HangXin(USR_CMD_UP_IMG);
                    break;/*�ɼ�ԭʼͼ��*/
                case CMD_GET_REDRESS_IMAGE:   break;/*�ɼ�����ͼ��*/
                case CMD_UPLOAD_IMAGE:        break;/*�ϴ�ͼ��(����ԭʼͼ��ͽ���ͼ��)*/
                case CMD_GEN_CHAR:            break;/*����ģ��*/
                case CMD_MATCH_CHAR:          break;/*�ȶ�ģ��*/
                case CMD_STORE_CHAR:          break;/*�洢ģ��*/
                case CMD_SEARCH_CHAR:         break;/*����ģ��*/
                case CMD_DELETE_CHAR:         break;/*ɾ��ָ��ģ��*/
                case CMD_EMPTY_CHAR:          break;/*���ģ���*/
                case CMD_VERIFY_CHAR:         break;/*��һ�ȶ�ģ��*/
                case CMD_GET_CHAR:            break;/*��ȡģ��*/
                case CMD_PUT_CHAR:            break;/*����ģ��*/
                case CMD_GET_MBINDEX:         break;/*��ȡMBIndex*/
                case CMD_READ_NOTE_BOOK:      break;/*�����±�*/
                case CMD_WRITE_NOTE_BOOK:     break;/*д���±�*/
                case CMD_READ_PAR_TABLE:      break;/*��ȡ������*/
                case CMD_SET_BAUD_RATE:       break;/*���ò�����*/
                case CMD_SET_SECURLEVEL:      break;/*����ָ�ư�ȫ����*/
                case CMD_SET_CMOS_PARA:       break;/*����CMOS����*/
                case CMD_RESUME_FACTORY:      break;/*�ָ���������*/
                case CMD_MERGE_CHAR:          break;/*�ϲ�����*/
                case CMD_SET_PSW:             break;/*��������*/
                case CMD_SET_ADDRESS:         break;/*��ַ����*/
                case CMD_GET_RANDOM:          break;/*��ȡ�����*/
                case CMD_DOWNLOAD_IMAGE:      break;/*����ָ��ͼ��*/
                case CMD_ERASE_PROGRAM:       break;/*���������ʶ*/
                case CMD_STORE_CHAR_DIRECT:   break;/*ֱ�Ӵ洢ָ��ģ��*/
                case CMD_READ_CHAR_DIRECT:    break;/*ֱ�Ӹ��ݵ�ַ��ȡָ��ģ��*/
                case CMD_GET_FIRSTVALID_ADD:  break;/*��ȡ��һ�����е�ָ������*/
                case CMD_CHIP_ERASE:          break;/*��Ƭ����FLASH*/
            }
            return sendCommand_HangXin(CmdCode,Data,Len);
        default:
            ASF_ERROR(2);
            return false;
    }
}

bool CCommunication::sendCommand_HangXin(int CmdCode,uint8_t* Data,uint16_t Len){
    serial.Purge();
    uint8_t err=FALSE;
    static struct HangXinSendPacket sendPacket;
    memcpy(sendPacket.fixed,"zt\0",3);
    memcpy(sendPacket.fixed2,"\0\0\0\0",3);
    sendPacket.cmd=CmdCode;
    if((CmdCode>=1&&CmdCode<=0x1f)||CmdCode==0x22){
        err=TRUE;
    }
    if(err!=FALSE){
        uint8_t* p=(uint8_t*)&sendPacket;
        sendPacket.sumVal=0;
        for(int i=2;i<sendPacket.len+12;i++){
            sendPacket.sumVal+=p[i];
        }
        memcpy(p+sendPacket.len+12,&sendPacket.sumVal,2);
        memcpy(packet,p,sendPacket.len+14);

        DWORD    sendCnt=0;
        LONG     result=0;
        if(isUSB()){
            result=USB_Send(packet,sendPacket.len+14);
        } else{
            result=serial.Write(packet,sendPacket.len+14,&sendCnt,NULL,10*1000);
        }
        return TRUE;
    } else{
        //û�и�����
        return FALSE;
    }
}

bool CCommunication::sendCommand_Default(int CmdCode,uint8_t* Data,uint16_t Len){
    serial.Purge();
    uint8_t err=TRUE;
    struct DefaultSendPacket SendPack;
    SendPack.Head=0x02EF;
    SendPack.Addr=0x04030201;
    SendPack.Password=0x01020304;
    SendPack.NO=0x0201;
    SendPack.CMD=CmdCode;
    SendPack.Sign=0x01;
    SendPack.Length=Len;
    memcpy(SendPack.Sendbuf,Data,Len);
    switch(CmdCode){
        case CMD_GET_TEST_IMAGE:      break;/*��ñ���ͼƬ*/
        case CMD_DEVICE_RESET:        break;/*ϵͳ��λ*/
        case CMD_DETECT_FINGER:       break;/*̽��ָ��*/
        case CMD_GET_RAW_IMAGE:       break;/*�ɼ�ԭʼͼ��*/
        case CMD_GET_REDRESS_IMAGE:   break;/*�ɼ�����ͼ��*/
        case CMD_UPLOAD_IMAGE:        break;/*�ϴ�ͼ��(����ԭʼͼ��ͽ���ͼ��)*/
        case CMD_GEN_CHAR:            break;/*����ģ��*/
        case CMD_MATCH_CHAR:          break;/*�ȶ�ģ��*/
        case CMD_STORE_CHAR:          break;/*�洢ģ��*/
        case CMD_SEARCH_CHAR:         break;/*����ģ��*/
        case CMD_DELETE_CHAR:         break;/*ɾ��ָ��ģ��*/
        case CMD_EMPTY_CHAR:          break;/*���ģ���*/
        case CMD_VERIFY_CHAR:         break;/*��һ�ȶ�ģ��*/
        case CMD_GET_CHAR:            break;/*��ȡģ��*/
        case CMD_PUT_CHAR:            break;/*����ģ��*/
        case CMD_GET_MBINDEX:         break;/*��ȡMBIndex*/
        case CMD_READ_NOTE_BOOK:      break;/*�����±�*/
        case CMD_WRITE_NOTE_BOOK:     break;/*д���±�*/
        case CMD_READ_PAR_TABLE:      break;/*��ȡ������*/
        case CMD_SET_BAUD_RATE:       break;/*���ò�����*/
        case CMD_SET_SECURLEVEL:      break;/*����ָ�ư�ȫ����*/
        case CMD_SET_CMOS_PARA:       break;/*����CMOS����*/
        case CMD_RESUME_FACTORY:      break;/*�ָ���������*/
        case CMD_MERGE_CHAR:          break;/*�ϲ�����*/
        case CMD_SET_PSW:             break;/*��������*/
        case CMD_SET_ADDRESS:         break;/*��ַ����*/
        case CMD_GET_RANDOM:          break;/*��ȡ�����*/
        case CMD_DOWNLOAD_IMAGE:      break;/*����ָ��ͼ��*/
        case CMD_ERASE_PROGRAM:       break;/*���������ʶ*/
        case CMD_STORE_CHAR_DIRECT:   break;/*ֱ�Ӵ洢ָ��ģ��*/
        case CMD_READ_CHAR_DIRECT:    break;/*ֱ�Ӹ��ݵ�ַ��ȡָ��ģ��*/
        case CMD_GET_FIRSTVALID_ADD:  break;/*��ȡ��һ�����е�ָ������*/
        case CMD_CHIP_ERASE:          break;/*��Ƭ����FLASH*/
        default:err=TRUE;
    }
    if(err!=FALSE){

        DWORD    sendCnt=0;
        LONG     result=0;
        UINT16   length=SendPack.Length+19;
        uint8_t* SendPt=(uint8_t *)&SendPack;
        UINT16   crcValue=GetCRC16(SendPt,length-2);
        SendPack.Sendbuf[Len]=crcValue&0xFF;
        SendPack.Sendbuf[Len+1]=(crcValue>>8)&0xFF;
        memcpy(packet,SendPt,length);

        ////���ڻ�ȡ�����16���Ʊ�ʾ
        //freopen("1.txt","w",stdout);
        ////printf("CmdCode:%x\n",CmdCode);
        //for(int i=0;i<length;i++){
        //	printf("%c",packet[i]);
        //}

        if(isUSB()){
            result=USB_Send(packet,length);
        } else{
            result=serial.Write(packet,length,&sendCnt,NULL,10*1000);
        }
        return TRUE;
    } else{
        //û�и�����
        return FALSE;
    }
}

bool CCommunication::waitForPacket(int timeOutMs){
    //��ʱdebug����,�趨��ʱʱ��Ϊ60s
    timeOutMs=60*1000;
    LONG ret,time=1;
    do{
        if(isUSB()){
            ret=USB_Receive(packet,sizeof packet);
        } else{
            ret=serial.Read(packet,sizeof packet,&packetCnt,0,timeOutMs);
        }
        MyLog.print(Log::LOGT,"��ʱ���Ե�%d��",time++);
    } while(chkTimeoutContinue->GetCheck()&&ret!=ERROR_SUCCESS);
    return ret==ERROR_SUCCESS;
}

//��ϴ���ڰ��ĺ���,�Ѱ�ͷ��У����ϴ��,���������ݷ���packetData
void CCommunication::getDataFromPacket(){
    packetDataLen=0;
    switch(cmbChipType->GetCurSel()){
        case 0://Default
            for(int i=0,j=0;i<packetCnt;){
                //�����ݲ��ֳ���
                int k=packet[i+15]+packet[i+16]*256;
                MyLog.print(Log::LOGT,"Default singlePacketLen=%d",k);
                //������ǰ��bug
                if(k==530)k=528;
                //������ͷ
                i+=19;
                //�ۼ����ݳ���
                packetDataLen+=k;
                while(k--){
                    packetData[j++]=packet[i++];
                }
                //TODO: CRCУ��
                //����CRC
                i+=2;
                if(i>packetCnt)
                    ASF_WARNING(2);
            }
            break;
        case 1://HangXin
            memcpy(&packetDataLen,packet+8,4);
            MyLog.print(Log::LOGT,"HangXin packetDataLen=%d",packetDataLen);
            memcpy(packetData,packet+12,packetDataLen);
            break;
    }

}

const UINT16 CRC16Table[256]={
    0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
    0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
    0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
    0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
    0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
    0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
    0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
    0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
    0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
    0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
    0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
    0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
    0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
    0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
    0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
    0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
    0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
    0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
    0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
    0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
    0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
    0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
    0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
    0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
    0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
    0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
    0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
    0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
    0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
    0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
    0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
    0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};
//X16 + X12 + X5 + 1 ��ʽ��
uint16_t GetCRC16(UINT8 *pSource,UINT16 len){
    UINT16 i;
    UINT16 result=0;
    for(i=0; i<len; i++){
        result=(result<<8)^CRC16Table[(result>>8)^(UINT8)*pSource++];
    }
    return result;
}

BYTE cdb_w[16]={0xef,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
BYTE cdb_r[16]={0xef,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

bool CCommunication::USB_Send(BYTE CmdBuf[],DWORD CmdLength){
    return UsbPort.USBSCSIWrite(UsbPort.m_DeviceHandle,cdb_w,IOCTRL_CDB_LEN,CmdBuf,CmdLength,SCSI_TIMEOUT);
}

bool CCommunication::USB_Receive(BYTE RspBuf[],DWORD RspLength){
    return UsbPort.USBSCSIRead(UsbPort.m_DeviceHandle,cdb_r,IOCTRL_CDB_LEN,RspBuf,RspLength,SCSI_TIMEOUT);
}