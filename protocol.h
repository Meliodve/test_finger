#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_
//#include "main.h"

#include "common.h"
#include "Serial.h"
#pragma pack(1)

typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;

typedef unsigned          char UINT8;
typedef unsigned short     int UINT16;
typedef unsigned          char U8;
typedef unsigned short     int U16;

//prorocol struck
extern const UINT16 CRC16Table[256];
extern uint8_t FingerImageBuf[256][360];
extern uint8_t ImageBuf[];
#define Empty	1
#define	Full 	2
#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif


#define Protocol_SendOver	19	//��ͷ2 	�豸��ַ 4	��������4	�����2	������2	����ʶ1	���ݳ���2	У���2
#define Protocol_RevOver	21	//��ͷ2 	�豸��ַ 4	��������4	�����2	������2	����ʶ1	���ݳ���2	ȷ����2		У���2

#define Pack_Head		0x02EF
#define Device_Addr  	0x04030201		//?��???????0x00000000~0xFFFFFFFF????0xFFFFFFFF???????????????????????��?????????????????????
#define	Connect_PW		0x01020304//????????
#define Pack_NO			
#define CMD_Code
#define Pack_sign				0x01
#define Pack_Len								//<1024
#define Pack_Data								//<531
#define Pack_crc16
#define Pack_ACK_sign		0x02
#define Pack_ACK     
#define Pack_size sizeof(_Rev_pack_struct)

extern UINT16 CmdReturnCode[];
extern CSerial	g_Serial;
//string  MessageStr[];

struct _soft_param{
    BOOL ComTimeOut;
    U16  ComWaitCmd;
    U16	 PackNo;
    U8	 ComPort;
    UINT ComPortBaudRate;
    U8   ComPortState;
    U16  CmdCode;
};

extern _soft_param SoftParam;

struct Rev_struct{
    uint16_t 		Head;
    uint32_t		Addr;
    uint32_t  		Password;
    uint16_t		NO;
    uint16_t  		CMD;
    uint8_t			Sign;
    uint16_t  		Length;
    uint16_t		ACK;
    uint8_t			Revbuf[530];

};

struct _Rev_pack_struct{
    struct Rev_struct rev_stc;
    uint16_t	Revpt;
    uint8_t 	RevCp;
};

extern struct _Rev_pack_struct Rev_pack;
struct _Send_pack_struct{
    uint16_t	Head;
    uint32_t	Addr;
    uint32_t	Password;
    uint16_t	NO;
    uint16_t	CMD;
    uint8_t		Sign;
    uint16_t	Length;
    uint8_t		Sendbuf[532];
    //	uint16_t  crc16;
};

extern	struct _Send_pack_struct SendPack;
struct image_struct{
    uint8_t  bufIsEmpty;
    uint16_t width;
    uint16_t high;
    uint16_t readLine;
    uint16_t Length;
};
extern struct image_struct imageInfo;
extern uint8_t    Revbuf[549];
extern uint8_t    Sendbuf[549];

///////////////////////������///////////////////////////////
#define	CMD_DEVICE_RESET	    	0x0320	    	//ϵͳ��λ
#define	CMD_DETECT_FINGER	    	0x0321	    	//̽��ָ��
#define	CMD_GET_RAW_IMAGE	    	0x0322	    	//�ɼ�ԭʼͼ��
#define	CMD_GET_REDRESS_IMAGE		0x0323	    	//�ɼ�����ͼ��
#define	CMD_UPLOAD_IMAGE	    	0x0324	    	//�ϴ�ͼ��(����ԭʼͼ��ͽ���ͼ��)
#define	CMD_GEN_CHAR	    	   	0x0325	    	//����ģ��
#define	CMD_MATCH_CHAR	    	   	0x0326	    	//�ȶ�ģ��
#define	CMD_STORE_CHAR	    	   	0x0327	    	//�洢ģ��
#define	CMD_SEARCH_CHAR	    	   	0x0328	    	//����ģ��
#define	CMD_DELETE_CHAR	    	   	0x0329	    	//ɾ��ָ��ģ��
#define	CMD_EMPTY_CHAR	    	   	0x032A	    	//���ģ���
#define	CMD_VERIFY_CHAR	    	   	0x032B	    	//��һ�ȶ�ģ��
#define	CMD_GET_CHAR	    	   	0x032C			//��ȡģ��
#define	CMD_PUT_CHAR	    	   	0x032D			//����ģ��
#define	CMD_GET_MBINDEX	    	   	0x032E	    	//��ȡMBIndex
#define	CMD_READ_NOTE_BOOK	    	0x032F	    	//�����±�
#define	CMD_WRITE_NOTE_BOOK	    	0x0330	    	//д���±�
#define	CMD_READ_PAR_TABLE	    	0x0331	    	//��ȡ������
#define	CMD_SET_BAUD_RATE	    	0x0332			//���ò�����
#define	CMD_SET_SECURLEVEL	    	0x0333	    	//����ָ�ư�ȫ����
#define	CMD_SET_CMOS_PARA	    	0x0334			//����CMOS����
#define	CMD_RESUME_FACTORY	    	0x0335	    	//�ָ���������
#define	CMD_MERGE_CHAR	    		0x0336			//�ϲ�����
#define	CMD_SET_PSW	    			0x0337			//��������
#define	CMD_SET_ADDRESS	    		0x0338			//��ַ����
#define	CMD_GET_RANDOM	    		0x0339			//��ȡ�����
#define	CMD_DOWNLOAD_IMAGE	    	0x0340	    	//����ָ��ͼ��
#define	CMD_ERASE_PROGRAM	    	0x0341			//���������ʶ
#define	CMD_STORE_CHAR_DIRECT	   	0x0342	    	//ֱ�Ӵ洢ָ��ģ��
#define	CMD_READ_CHAR_DIRECT	   	0x0343	    	//ֱ�Ӹ��ݵ�ַ��ȡָ��ģ��
#define	CMD_GET_FIRSTVALID_ADD		0x0344	    	//��ȡ��һ�����е�ָ������
#define	CMD_CHIP_ERASE	    		0x0380			//��Ƭ����FLASH
#define CMD_FINGER_DETECT			0X0400			//��ָ���
#define	CMD_Sleep_MODE				0X0401			//sleepģʽ
#define CMD_SleepToIdle				0x0402
#define CMD_AdjustImage				0x0403
//������		    		    	
#define	CMD_RT_OK	    									0x0000	    	//����ִ����ϻ�OK
#define	CMD_RT_PACKGE_ERR	    					0x0001	    	//���ݰ����մ���
#define	CMD_RT_DEVICE_ADDRESS_ERR				0x0002	    	//�豸��ַ����
#define	CMD_RT_COM_PASSWORD_ERR	  			0x0003	    	//ͨ���������
#define	CMD_RT_NO_FINGER	    					0x0004	    	//��������û����ָ
#define	CMD_RT_GET_IMAGE_FAIL	    			0x0005	    	//�Ӵ������ϻ�ȡͼ��ʧ��
#define	CMD_RT_GEN_CHAR_ERR	    				0x0006	    	//��������ʧ��
#define	CMD_RT_FINGER_MATCH_ERR	  			0x0007	    	//ָ�Ʋ�ƥ��
#define	CMD_RT_FINGER_SEARCH_FAIL				0x0008	    	//û������ָ��
#define	CMD_RT_MERGE_TEMPLET_FAIL				0x0009	    	//�����ϲ�ʧ��
#define	CMD_RT_ADDRESS_OVERFLOW	  			0x000A	    	//��ģ����ʱ��ַ��ų���ָ�ƿⷶΧ
#define	CMD_RT_READ_TEMPLET_ERR	  			0x000B	    	//��ָ�ƿ��ģ�����
#define	CMD_RT_UP_TEMPLET_ERR	    			0x000C	    	//�ϴ�����ʧ��
#define	CMD_RT_UP_IMAGE_FAIL	    			0x000D	    	//�ϴ�ͼ��ʧ��
#define	CMD_RT_DELETE_TEMPLET_ERR				0x000E	    	//ɾ��ģ��ʧ��
#define	CMD_RT_CLEAR_TEMPLET_LIB_ERR		0x000F	    	//���ָ�ƿ�ʧ��
#define	CMD_RT_FINGER_NOT_MOVE	    		0x0010	    	//����ָ�ƻ򴫸������ڵİ�ָ��ʱ��δ�ƿ�
#define	CMD_RT_NO_TEMPLET_IN_ADDRESS		0x0011	    	//ָ��λ��û����Чģ��
#define	CMD_RT_CHAR_REPEAT	    				0x0012	    	//ָ���ظ�����Ҫע���ָ���Ѿ���FLASH��ע��
#define	CMD_RT_MB_NOT_EXIST_IN_ADDRESS	0x0013	    	//�õ�ַ�в�����ָ��ģ��
#define	CMD_RT_GET_MBINDEX_OVERFLOW	    0x0014	    	//��ȡģ�������������
#define	CMD_RT_SET_BAUD_RATE_FAIL	    	0x0015	    	//���ò�����ʧ��
#define	CMD_RT_ERASE_FLAG_FAIL	    		0x0016	    	//���������־ʧ��
#define	CMD_RT_SYSTEM_RESET_FAIL	    	0x0017	    	//ϵͳ��λʧ��
#define	CMD_RT_OPERATION_FLASH_ERR	    0x0018	    	//����FLASH����
#define	CMD_RT_NOTE_BOOK_ADDRESS_OVERFLOW	 0x0019	    //���±���ַ���
#define	CMD_RT_PARA_ERR	    			0x001A	    	//���ò�������
#define	CMD_RT_NO_CMD	    				0x001B	    	//�������

//extern void protocol_deal(struct _Rev_pack_struct *R_pack);
//
// extern void GET_RAW_IMAGE(struct image_struct *image );
// extern void sendCaptureCmd(uint8_t *Sendbuf);
extern BOOL SendCommand(U16 CmdCode,U8 *Data,U16 Len);

extern U8 Asc2Hex(CString strasc);
extern UINT16 GetCRC16(UINT8 *pSource,UINT16 len);
extern const UINT16 CRC16Table[256];


#endif




