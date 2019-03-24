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


void all_struct_Init(void){
    imageInfo.bufIsEmpty=Empty;
    imageInfo.width=160;
    imageInfo.high=160;
    imageInfo.readLine=0;
}


BOOL SendCommand(U16 CmdCode,U8 *Data,U16 Len){
    
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
