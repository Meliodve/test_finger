#include"stdafx.h"
//CSerial CCommunication::serial;
//int CCommunication::id=0;
//int CommType;
//
//bool isUSB(){
//    CString selectionText;
//    cmbWay->GetWindowText(selectionText);
//    return selectionText.Compare(_T("USB"))==0;
//}
//
//int CCommunication::getConnectId(){
//    return CCommunication::id;
//}
//
//bool CCommunication::connect(int id,int baud){
//    if(isUSB()){
//        if(UsbPort.InitUsbPort(COMM_USB_MASS,"UD")){
//            CommType=COMM_USB_MASS;
//            cmbChipType->SetCurSel(1);
//            bool ret=sendCommand(USR_CMD_GET_INFO);
//            ret=waitForPacket(100*1000);
//            return true;
//        } else{
//            CommType=-1;
//            return false;
//        }
//    }
//    CString way;
//    way.Format(_T("\\\\.\\COM%d"),id);//�õ��˿ڵ�ַ
//    LONG retCode=ERROR_SUCCESS;
//
//    if(retCode==ERROR_SUCCESS){
//        retCode=serial.Open(way,2048,2048,true);
//    }
//    //����������������Ĭ�ϲ���
//    if(retCode==ERROR_SUCCESS){
//        retCode=serial.Setup((CSerial::EBaudrate)baud);
//    }
//    if(retCode==ERROR_SUCCESS){
//        retCode=serial.SetMask(CSerial::EEventRecv);
//    }
//    if(retCode==ERROR_SUCCESS){
//        serial.Purge();
//    }
//    MyLog.print(Log::LOGU,"����COM%d%s",id,retCode==ERROR_SUCCESS?"�ɹ�":"ʧ��");
//    if(retCode==ERROR_SUCCESS){
//        CCommunication::id=id;
//    }
//    return retCode==ERROR_SUCCESS;
//}
//
//bool CCommunication::disConnect(){
//    if(isUSB()){
//        return UsbPort.CloseUsbPort()==0;
//    }
//    int ret=serial.Close();
//    MyLog.print(Log::LOGU,"�Ͽ����ӳɹ�");
//    if(ret==ERROR_SUCCESS){
//        CCommunication::id=0;
//        return true;
//    } else{
//        ASF_WARNING(5);
//        return false;
//    }
//}
//
//bool CCommunication::sendCommand(int CmdCode,uint8_t* Data,uint16_t Len){
//    switch(cmbChipType->GetCurSel()){
//        case 0:return sendCommand_Default(CmdCode,Data,Len);
//        case 1:
//            switch(CmdCode){
//                case USR_CMD_GET_INFO:
//                    return sendCommand_HangXin(USR_CMD_GET_INFO);
//                    break;/*��о:����оƬ��Ϣ*/
//                case CMD_GET_TEST_IMAGE:      break;/*��ñ���ͼƬ*/
//                case CMD_DEVICE_RESET:        break;/*ϵͳ��λ*/
//                case CMD_DETECT_FINGER:       break;/*̽��ָ��*/
//                case CMD_GET_RAW_IMAGE:
//                    sendCommand_HangXin(USR_CMD_GRAB_NO_CHECK);
//                    waitForPacket(10*1000);
//                    return sendCommand_HangXin(USR_CMD_UP_IMG);
//                    break;/*�ɼ�ԭʼͼ��*/
//                case CMD_GET_REDRESS_IMAGE:   break;/*�ɼ�����ͼ��*/
//                case CMD_UPLOAD_IMAGE:        break;/*�ϴ�ͼ��(����ԭʼͼ��ͽ���ͼ��)*/
//                case CMD_GEN_CHAR:            break;/*����ģ��*/
//                case CMD_MATCH_CHAR:          break;/*�ȶ�ģ��*/
//                case CMD_STORE_CHAR:          break;/*�洢ģ��*/
//                case CMD_SEARCH_CHAR:         break;/*����ģ��*/
//                case CMD_DELETE_CHAR:         break;/*ɾ��ָ��ģ��*/
//                case CMD_EMPTY_CHAR:          break;/*���ģ���*/
//                case CMD_VERIFY_CHAR:         break;/*��һ�ȶ�ģ��*/
//                case CMD_GET_CHAR:            break;/*��ȡģ��*/
//                case CMD_PUT_CHAR:            break;/*����ģ��*/
//                case CMD_GET_MBINDEX:         break;/*��ȡMBIndex*/
//                case CMD_READ_NOTE_BOOK:      break;/*�����±�*/
//                case CMD_WRITE_NOTE_BOOK:     break;/*д���±�*/
//                case CMD_READ_PAR_TABLE:      break;/*��ȡ������*/
//                case CMD_SET_BAUD_RATE:       break;/*���ò�����*/
//                case CMD_SET_SECURLEVEL:      break;/*����ָ�ư�ȫ����*/
//                case CMD_SET_CMOS_PARA:       break;/*����CMOS����*/
//                case CMD_RESUME_FACTORY:      break;/*�ָ���������*/
//                case CMD_MERGE_CHAR:          break;/*�ϲ�����*/
//                case CMD_SET_PSW:             break;/*��������*/
//                case CMD_SET_ADDRESS:         break;/*��ַ����*/
//                case CMD_GET_RANDOM:          break;/*��ȡ�����*/
//                case CMD_DOWNLOAD_IMAGE:      break;/*����ָ��ͼ��*/
//                case CMD_ERASE_PROGRAM:       break;/*���������ʶ*/
//                case CMD_STORE_CHAR_DIRECT:   break;/*ֱ�Ӵ洢ָ��ģ��*/
//                case CMD_READ_CHAR_DIRECT:    break;/*ֱ�Ӹ��ݵ�ַ��ȡָ��ģ��*/
//                case CMD_GET_FIRSTVALID_ADD:  break;/*��ȡ��һ�����е�ָ������*/
//                case CMD_CHIP_ERASE:          break;/*��Ƭ����FLASH*/
//            }
//            return sendCommand_HangXin(CmdCode,Data,Len);
//        default:
//            ASF_ERROR(2);
//            return false;
//    }
//}
//
//bool CCommunication::sendCommand_HangXin(int CmdCode,uint8_t* Data,uint16_t Len){
//    serial.Purge();
//    uint8_t err=FALSE;
//    static struct HangXinSendPacket sendPacket;
//    memcpy(sendPacket.fixed,"zt\0",3);
//    memcpy(sendPacket.fixed2,"\0\0\0\0",3);
//    sendPacket.cmd=CmdCode;
//    if((CmdCode>=1&&CmdCode<=0x1f)||CmdCode==0x22){
//        err=TRUE;
//    }
//    if(err!=FALSE){
//        uint8_t* p=(uint8_t*)&sendPacket;
//        sendPacket.sumVal=0;
//        for(int i=2;i<sendPacket.len+12;i++){
//            sendPacket.sumVal+=p[i];
//        }
//        memcpy(p+sendPacket.len+12,&sendPacket.sumVal,2);
//        memcpy(packet,p,sendPacket.len+14);
//
//        DWORD    sendCnt=0;
//        LONG     result=0;
//        if(isUSB()){
//            result=USB_Send(packet,sendPacket.len+14);
//        } else{
//            result=serial.Write(packet,sendPacket.len+14,&sendCnt,NULL,10*1000);
//        }
//        return TRUE;
//    } else{
//        //û�и�����
//        return FALSE;
//    }
//}
//
//bool CCommunication::sendCommand_Default(int CmdCode,uint8_t* Data,uint16_t Len){
//    serial.Purge();
//    uint8_t err=TRUE;
//    struct DataPacketGD32F30 SendPack;
//    SendPack.Head=0x02EF;
//    SendPack.Addr=0x04030201;
//    SendPack.Password=0x01020304;
//    SendPack.NO=0x0201;
//    SendPack.CMD=CmdCode;
//    SendPack.Sign=0x01;
//    SendPack.Length=Len;
//    memcpy(SendPack.Sendbuf,Data,Len);
//    switch(CmdCode){
//        case CMD_GET_TEST_IMAGE:      break;/*��ñ���ͼƬ*/
//        case CMD_DEVICE_RESET:        break;/*ϵͳ��λ*/
//        case CMD_DETECT_FINGER:       break;/*̽��ָ��*/
//        case CMD_GET_RAW_IMAGE:       break;/*�ɼ�ԭʼͼ��*/
//        case CMD_GET_REDRESS_IMAGE:   break;/*�ɼ�����ͼ��*/
//        case CMD_UPLOAD_IMAGE:        break;/*�ϴ�ͼ��(����ԭʼͼ��ͽ���ͼ��)*/
//        case CMD_GEN_CHAR:            break;/*����ģ��*/
//        case CMD_MATCH_CHAR:          break;/*�ȶ�ģ��*/
//        case CMD_STORE_CHAR:          break;/*�洢ģ��*/
//        case CMD_SEARCH_CHAR:         break;/*����ģ��*/
//        case CMD_DELETE_CHAR:         break;/*ɾ��ָ��ģ��*/
//        case CMD_EMPTY_CHAR:          break;/*���ģ���*/
//        case CMD_VERIFY_CHAR:         break;/*��һ�ȶ�ģ��*/
//        case CMD_GET_CHAR:            break;/*��ȡģ��*/
//        case CMD_PUT_CHAR:            break;/*����ģ��*/
//        case CMD_GET_MBINDEX:         break;/*��ȡMBIndex*/
//        case CMD_READ_NOTE_BOOK:      break;/*�����±�*/
//        case CMD_WRITE_NOTE_BOOK:     break;/*д���±�*/
//        case CMD_READ_PAR_TABLE:      break;/*��ȡ������*/
//        case CMD_SET_BAUD_RATE:       break;/*���ò�����*/
//        case CMD_SET_SECURLEVEL:      break;/*����ָ�ư�ȫ����*/
//        case CMD_SET_CMOS_PARA:       break;/*����CMOS����*/
//        case CMD_RESUME_FACTORY:      break;/*�ָ���������*/
//        case CMD_MERGE_CHAR:          break;/*�ϲ�����*/
//        case CMD_SET_PSW:             break;/*��������*/
//        case CMD_SET_ADDRESS:         break;/*��ַ����*/
//        case CMD_GET_RANDOM:          break;/*��ȡ�����*/
//        case CMD_DOWNLOAD_IMAGE:      break;/*����ָ��ͼ��*/
//        case CMD_ERASE_PROGRAM:       break;/*���������ʶ*/
//        case CMD_STORE_CHAR_DIRECT:   break;/*ֱ�Ӵ洢ָ��ģ��*/
//        case CMD_READ_CHAR_DIRECT:    break;/*ֱ�Ӹ��ݵ�ַ��ȡָ��ģ��*/
//        case CMD_GET_FIRSTVALID_ADD:  break;/*��ȡ��һ�����е�ָ������*/
//        case CMD_CHIP_ERASE:          break;/*��Ƭ����FLASH*/
//        default:err=TRUE;
//    }
//    if(err!=FALSE){
//
//        DWORD    sendCnt=0;
//        LONG     result=0;
//        UINT16   length=SendPack.Length+19;
//        uint8_t* SendPt=(uint8_t *)&SendPack;
//        UINT16   crcValue=GetCRC16(SendPt,length-2);
//        SendPack.Sendbuf[Len]=crcValue&0xFF;
//        SendPack.Sendbuf[Len+1]=(crcValue>>8)&0xFF;
//        memcpy(packet,SendPt,length);
//
//        ////���ڻ�ȡ�����16���Ʊ�ʾ
//        //freopen("1.txt","w",stdout);
//        ////printf("CmdCode:%x\n",CmdCode);
//        //for(int i=0;i<length;i++){
//        //	printf("%c",packet[i]);
//        //}
//
//        if(isUSB()){
//            result=USB_Send(packet,length);
//        } else{
//            result=serial.Write(packet,length,&sendCnt,NULL,10*1000);
//        }
//        return TRUE;
//    } else{
//        //û�и�����
//        return FALSE;
//    }
//}
//
//bool CCommunication::waitForPacket(int timeOutMs){
//    //��ʱdebug����,�趨��ʱʱ��Ϊ60s
//    timeOutMs=60*1000;
//    LONG ret,time=1;
//    do{
//        if(isUSB()){
//            ret=USB_Receive(packet,sizeof packet);
//        } else{
//            ret=serial.Read(packet,sizeof packet,&packetCnt,0,timeOutMs);
//        }
//        MyLog.print(Log::LOGT,"��ʱ���Ե�%d��",time++);
//    } while(chkTimeoutContinue->GetCheck()&&ret!=ERROR_SUCCESS);
//    return ret==ERROR_SUCCESS;
//}
//
////��ϴ���ڰ��ĺ���,�Ѱ�ͷ��У����ϴ��,���������ݷ���packetData
//void CCommunication::getDataFromPacket(){
//    packetDataLen=0;
//    switch(cmbChipType->GetCurSel()){
//        case 0://Default
//            for(int i=0,j=0;i<packetCnt;){
//                //�����ݲ��ֳ���
//                int k=packet[i+15]+packet[i+16]*256;
//                MyLog.print(Log::LOGT,"Default singlePacketLen=%d",k);
//                //������ǰ��bug
//                if(k==530)k=528;
//                //������ͷ
//                i+=19;
//                //�ۼ����ݳ���
//                packetDataLen+=k;
//                while(k--){
//                    packetData[j++]=packet[i++];
//                }
//                //TODO: CRCУ��
//                //����CRC
//                i+=2;
//                if(i>packetCnt)
//                    ASF_WARNING(2);
//            }
//            break;
//        case 1://HangXin
//            memcpy(&packetDataLen,packet+8,4);
//            MyLog.print(Log::LOGT,"HangXin packetDataLen=%d",packetDataLen);
//            memcpy(packetData,packet+12,packetDataLen);
//            break;
//    }
//
//}
//
//
//
//BYTE cdb_w[16]={0xef,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//BYTE cdb_r[16]={0xef,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//
//bool CCommunication::USB_Send(BYTE CmdBuf[],DWORD CmdLength){
//    return UsbPort.USBSCSIWrite(UsbPort.m_DeviceHandle,cdb_w,IOCTRL_CDB_LEN,CmdBuf,CmdLength,SCSI_TIMEOUT);
//}
//
//bool CCommunication::USB_Receive(BYTE RspBuf[],DWORD RspLength){
//    return UsbPort.USBSCSIRead(UsbPort.m_DeviceHandle,cdb_r,IOCTRL_CDB_LEN,RspBuf,RspLength,SCSI_TIMEOUT);
//}
