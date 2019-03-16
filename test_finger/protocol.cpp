#include "stdafx.h"
#include "string.h"

//#include "crc16.h"
#include "protocol.h"
#include <winuser.h>
#include "Serial.h"

//extern "C"
//{
//extern int Port;
// class CUSBDlg : public CDialog

Ctest_fingerDlg *app=(Ctest_fingerDlg *)AfxGetApp();

//app->Port = 0;
// Port
struct _soft_param SoftParam;

uint8_t FingerImageBuf[256][360];
//uint16_t CmdReturnCode[]=
//{
//CMD_RT_OK,
//CMD_RT_MATCH,
//CMD_RT_NO_MATCH,
//CMD_RT_PACKGE_ERR,
//CMD_RT_DEVICE_ADDRESS_ERR,
//CMD_RT_COM_PASSWORD_ERR,
//CMD_RT_NO_FINGER,
//CMD_RT_GET_IMAGE_FAILE,
//CMD_RT_GET_IMAGE_TIMEOUT,
//CMD_RT_GET_IMAGE_AGC_FAIL,
//CMD_RT_ENROLL_EARLY_OUT,
//CMD_RT_PARAMETER_ERR,
//CMD_RT_USER_FULL,
//CMD_RT_USER_NOT_EXIST,
//CMD_RT_ERASE_PAGE_FAIL,
//CMD_RT_WRITE_FLASH_FAIL,
//CMD_RT_HEAP_NO_MEMORY,
//CMD_RT_USERLIB_IS_EMPTY,
//CMD_RT_FEATURE_NOT_SUPPORT,
//CMD_RT_NO_TEMPLATE_EXIT,
//CMD_RT_ENROLL_LESS_MINUTIAE,
//CMD_RT_SENSOR_CHIP_NOT_MATCH,
//CMD_RT_ENROLL_LESS_AREA,
//CMD_RT_ENROLL_MOVEFINGER,
//CMD_RT_NO_CMD,
//CMD_RT_NO_USER_MATCHED
// };// 
//string  MessageStr[][]=
//{
//"��ȡͼ��ʱ",
//"������AGC����ʧ��",
//"ָ��¼����ǰ����(��������Ҫ����)",
//"���������Ĳ�������",
//"ģ��ָ�ƿ���",
//"�û�������",
//"ģ��flash�����ʧ��",
//"ģ��flash��дʧ��",
//"ģ���ڴ����ʧ��",
//"ģ��ָ�ƿ�Ϊ��",
//"ģ��������֧��",
//"��ģ��",
//"ע��ָ�����������",
//"�������Ͳ��������趨��ƥ��",
//"ע�������С",
//"ע�����ƶ���ָ",
//"�������",
//"���û�ƥ��"
//};

uint8_t    Revbuf[549];
uint8_t    Sendbuf[549];
struct Rev_struct 	rev_stc;//=(struct Rev_struct*)Revbuf;

struct image_struct imageInfo=
{
    //.bufpt =	Sendbuf,
    Empty,
    160,
    160,
    0,
};

void all_struct_Init(void){
    imageInfo.bufIsEmpty=Empty;
    imageInfo.width=160;
    imageInfo.high=160;
    imageInfo.readLine=0;
}

struct _Send_pack_struct SendPack;


BOOL SendCommand(U16 CmdCode,U8 *Data,U16 Len){
    U8 err=TRUE;
    SendPack.Head=Pack_Head;
    SendPack.Addr=0x04030201;
    SendPack.Password=0x01020304;
    SendPack.NO=0x0201;
    SendPack.CMD=CmdCode;
    SendPack.Sign=Pack_sign;
    SendPack.Length=Len;
	memcpy(SendPack.Sendbuf,Data,Len);
    SoftParam.ComWaitCmd=CmdCode;
	switch(CmdCode){
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
		DWORD    w_nSendCnt=0;
		LONG     w_nResult=0;
        UINT16   length=SendPack.Length+Protocol_SendOver;
        uint8_t* SendPt=(uint8_t *)&SendPack;
        UINT16   crcValue=GetCRC16(SendPt,length-2);
        SendPack.Sendbuf[Len]=crcValue&0xFF;
        SendPack.Sendbuf[Len+1]=(crcValue>>8)&0xFF;
		memcpy(packet,SendPt,length);

		/*���ڻ�ȡ�����16���Ʊ�ʾ
		freopen("1.txt","a+",stdout);
		printf("CmdCode:%x\n",CmdCode);
		for(int i=0;i<length;i++){
			printf("%x%s",g_Packet[i],i==length-1?"\n":" ");
		}*/

        w_nResult=serial.Write(packet,length,&w_nSendCnt,NULL,10*1000);
        return TRUE;
    } else{
        //û�и�����
        return FALSE;
    }
}


void SystemParamInit(void){
    SendPack.Head=Pack_Head;
    SendPack.Addr=0x04030201;
    SendPack.Password=0x01020304;
    SendPack.NO=0x0000;
    SendPack.CMD=NULL;
    SendPack.Sign=Pack_sign;
    SendPack.Length=0;
    SendPack.Sendbuf[0]=0xff;
    SendPack.Sendbuf[1]=0xff;
}

U8  Asc2Hex(CString strasc){
    U8 strhex=0;

    strasc.MakeUpper();
    if(strasc.GetLength()==1){
        strasc='0'+strasc;
    }

    if((strasc.GetAt(0)>='A')&&(strasc.GetAt(0)<='F'))
        strhex=(strasc.GetAt(0)-55)*16;
    else
        if(strasc.GetAt(0)>='0' && strasc.GetAt(0)<='9')
            strhex=(strasc.GetAt(0)-0x30)*16;

    if(strasc.GetAt(1)>='A' && strasc.GetAt(1)<='Z') strhex+=(strasc.GetAt(1)-55);
    else if(strasc.GetAt(1)>='0' && strasc.GetAt(1)<='9') strhex+=(strasc.GetAt(1)-0x30);

    return strhex;

}




/********************************************************************
* Function Name  : GetCRC16
* Description    : ����CRC16ֵ.
* Input          : *pSource: ����ͷָ��  len:���ݳ���
* Output         : None
* Return         : CRC16��
*******************************************************************************/
UINT16 GetCRC16(UINT8 *pSource,UINT16 len){
    UINT16 i;
    UINT16 result=0;
    for(i=0; i<len; i++){
        result=(result<<8)^CRC16Table[(result>>8)^(UINT8)*pSource++];
    }
    return result;
}
//  CRC16У��  
//X16 + X12 + X5 + 1 ��ʽ��
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
