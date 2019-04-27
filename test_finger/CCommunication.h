#pragma once
#include"stdafx.h"

class CCommunication{
private:
    static CSerial serial;
    static int id;
    static bool sendCommand_Default(int cmdCode,uint8_t* Data=0,uint16_t Len=0);
    static bool sendCommand_HangXin(int cmdCode,uint8_t* Data=0,uint16_t Len=0);
    static bool USB_Send(BYTE CmdBuf[],DWORD CmdLength);
    static bool USB_Receive(BYTE RspBuf[],DWORD RspLength);
public:
    static int getConnectId();
    static bool connect(int id,int baud);
    static bool disConnect();
    static bool sendCommand(int cmdCode,uint8_t* Data=0,uint16_t Len=0);
    static bool waitForPacket(int timeOutMs);
    //��ϴ���ڰ��ĺ���,�Ѱ�ͷ��У����ϴ��,���������ݷ���packetData
    static void CCommunication::getDataFromPacket();
};

uint16_t GetCRC16(const void*pSource,uint16_t len);


///////////////////////������///////////////////////////////
#define	CMD_GET_TEST_IMAGE			0x031F			//��ñ���ͼƬ
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
#define	CMD_RT_OK	    					0x0000	    	//����ִ����ϻ�OK
#define	CMD_RT_PACKGE_ERR	    			0x0001	    	//���ݰ����մ���
#define	CMD_RT_DEVICE_ADDRESS_ERR			0x0002	    	//�豸��ַ����
#define	CMD_RT_COM_PASSWORD_ERR	  			0x0003	    	//ͨ���������
#define	CMD_RT_NO_FINGER	    			0x0004	    	//��������û����ָ
#define	CMD_RT_GET_IMAGE_FAIL	    		0x0005	    	//�Ӵ������ϻ�ȡͼ��ʧ��
#define	CMD_RT_GEN_CHAR_ERR	    			0x0006	    	//��������ʧ��
#define	CMD_RT_FINGER_MATCH_ERR	  			0x0007	    	//ָ�Ʋ�ƥ��
#define	CMD_RT_FINGER_SEARCH_FAIL			0x0008	    	//û������ָ��
#define	CMD_RT_MERGE_TEMPLET_FAIL			0x0009	    	//�����ϲ�ʧ��
#define	CMD_RT_ADDRESS_OVERFLOW	  			0x000A	    	//��ģ����ʱ��ַ��ų���ָ�ƿⷶΧ
#define	CMD_RT_READ_TEMPLET_ERR	  			0x000B	    	//��ָ�ƿ��ģ�����
#define	CMD_RT_UP_TEMPLET_ERR	    		0x000C	    	//�ϴ�����ʧ��
#define	CMD_RT_UP_IMAGE_FAIL	    		0x000D	    	//�ϴ�ͼ��ʧ��
#define	CMD_RT_DELETE_TEMPLET_ERR			0x000E	    	//ɾ��ģ��ʧ��
#define	CMD_RT_CLEAR_TEMPLET_LIB_ERR		0x000F	    	//���ָ�ƿ�ʧ��
#define	CMD_RT_FINGER_NOT_MOVE	    		0x0010	    	//����ָ�ƻ򴫸������ڵİ�ָ��ʱ��δ�ƿ�
#define	CMD_RT_NO_TEMPLET_IN_ADDRESS		0x0011	    	//ָ��λ��û����Чģ��
#define	CMD_RT_CHAR_REPEAT	    			0x0012	    	//ָ���ظ�����Ҫע���ָ���Ѿ���FLASH��ע��
#define	CMD_RT_MB_NOT_EXIST_IN_ADDRESS		0x0013	    	//�õ�ַ�в�����ָ��ģ��
#define	CMD_RT_GET_MBINDEX_OVERFLOW			0x0014	    	//��ȡģ�������������
#define	CMD_RT_SET_BAUD_RATE_FAIL	    	0x0015	    	//���ò�����ʧ��
#define	CMD_RT_ERASE_FLAG_FAIL	    		0x0016	    	//���������־ʧ��
#define	CMD_RT_SYSTEM_RESET_FAIL	    	0x0017	    	//ϵͳ��λʧ��
#define	CMD_RT_OPERATION_FLASH_ERR			0x0018	    	//����FLASH����
#define	CMD_RT_NOTE_BOOK_ADDRESS_OVERFLOW	0x0019			//���±���ַ���
#define	CMD_RT_PARA_ERR	    				0x001A	    	//���ò�������
#define	CMD_RT_NO_CMD	    				0x001B	    	//�������


////HangXin
//enum HangXinCmd{
//    USR_CMD_GET_INFO=1,
//    USR_CMD_GET_DEVICESN,
//    USR_CMD_SET_DEVICESN,
//    USR_CMD_GET_SESSION,
//    USR_CMD_SET_SESSION,
//    USR_CMD_GET_SENSOR_INFO,
//    USR_CMD_CONFIG_SENSOR,
//    USR_CMD_GRAB,
//    USR_CMD_GRAB_NO_CHECK,
//    USR_CMD_GRAB_WAIT,
//    USR_CMD_GENERATE,
//    USR_CMD_MERGE,
//    USR_CMD_STORE,
//    USR_CMD_SEARCH,
//    USR_CMD_MATCH,
//    USR_CMD_UP_IMG,
//    USR_CMD_DOWN_IMG,
//    USR_CMD_LOAD_CHAR,
//    USR_CMD_UP_CHAR,
//    USR_CMD_DOWN_CHAR,
//    USR_CMD_LIST,
//    USR_CMD_GET_EMPTY_ID,
//    USR_CMD_CHECK_ID,
//    USR_CMD_DELETE_ID,
//    USR_CMD_REMOVE_ALL,
//    USR_CMD_SET_LED,
//    USR_CMD_ENTER_IAP,
//    USR_CMD_CANCEL,
//    USR_CMD_WIRTE_PRODUCT_SESSION,
//    USR_CMD_SLEEP,
//    USR_CMD_DEV_BOOTLOADER,
//    USR_CMD_UP_IMG_EX=0x22
//};

#define COMM_USB_MASS	0
#define COMM_UART		1
#define COMM_USB_HID	2
#define COMM_USB_DRIVER	3

#define SENSOR_TYPE_NONE		0
#define SENSOR_TYPE_YW			1
#define SENSOR_TYPE_NB			2
#define SENSOR_TYPE_FPC1011F	3