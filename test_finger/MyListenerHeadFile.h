#pragma once

#pragma region SCC_DLC_ILC_BCL�궨��

/*
    ��һ��Э�����һ�������������²���:
    1.SCC,����һ������            ���ļ������ö�����Ͷ�����
    2.DLC,����һ��������          ���ļ�ö�����Ͷ���ǰ
    3.ILC,ʵ�����������          Э������C++�ļ���
    4.BCL,������������������   �������㲥��C++�ļ���������㲥���캯��

    ���ܻ���Ҫ���ö�Ӧ����ת������,�����²���:
    1.�ڴ��ļ������������ڲ�ָ��
    2.�ڶ�ӦЭ��Converter��C++�ļ����ת����������һ��case��

    ע:�������㲥��ListenerBoardcast
*/

//___SCN===Structure Class Name,����ƴ�������ĸ�����
#define ___SCN(Protocol,Message) \
CmdCode##Protocol##_##Message##_Listener

//__SCC===Structure Command Code,����ƴ������ĺ�
#define __SCC(Protocol,Message) \
CmdCode##Protocol##_##Message

//__DLC===Define Listener Class,���ٶ����������ĺ�
#define __DLC(Protocol,Message) \
class ___SCN(Protocol,Message):public ICommListener{\
public:\
    void listen(DataPacket& response);\
    ___SCN(Protocol,Message)(const char* protocol):ICommListener(protocol){}\
}

//__BCL===Binding Command into Listener,���ٰ�����󵽼������ĺ�
#define __BCL(ProtocolName,Protocol,Message) \
attach(__SCC(Protocol,Message),new ___SCN(Protocol,Message)(ProtocolName))

//__ILC===Implement Listener Class,����ʵ�ּ�������ĺ�
#define __ILC(Protocol,Message) \
void ___SCN(Protocol,Message)::listen(DataPacket& response)

//SII===Software Inner Instruction,����ڲ�ָ��
#define SII(Name) \
SII_##Name##_����ڲ�ָ��

#pragma endregion

//����ڲ������ʶ��
enum CmdCode{
    SII(GetRawImage),           //���ԭʼͼ��
    SII(GetTestImage),          //��ò���ͼ��
    SII(ReadRegister),          //���Ĵ���
    SII(WriteRegister),         //д�Ĵ���
    SII(UpImage),               //�ϴ�ͼ��
    SII(GenChar),               //����ԭʼͼ������ָ���������������ļ�������
    SII(GetEnrollImage),        //ע���û�ȡͼ��
    SII(RegModel),              //�������ļ��ϲ�����ģ����������ļ�������
    SII(StoreChar),             //�������������е��ļ����浽flashָ�ƿ���
    SII(Search),                //�������ļ��������е������ļ����������򲿷�ָ�ƿ�
    SII(ReadIndexTable),        //��������
    SII(Match),                 //��ȷ�ȶ������ļ��������е������ļ�
    SII(LoadChar),              //��flashָ�ƿ��ж�ȡһ��ģ�嵽����������
    SII(DeleteChar),            //ɾ��flashָ�ƿ��е�һ�������ļ�
    SII(DeviceInfo),            //��ȡ�豸��Ϣ
    SII(UpChar),                //�ϴ������ļ�
    SII(ReadINFPage),           //�������ҳ
    SII(ControlLED),            //����LED
};

#pragma region SynoЭ����

__DLC(Syno,GetImage);
__DLC(Syno,UpImage);
__DLC(Syno,GenChar);
__DLC(Syno,GetEnrollImage);
__DLC(Syno,RegModel);
__DLC(Syno,StoreChar);
__DLC(Syno,Search);
__DLC(Syno,ReadIndexTable);
__DLC(Syno,Match);
__DLC(Syno,LoadChar);
__DLC(Syno,DeleteChar);
__DLC(Syno,UpChar);
__DLC(Syno,ReadINFPage);
__DLC(Syno,ControlLED);

/*
д����ǰ,�Ȳ��ĵ�,��ö�ٸ�ֵ,�ʹ���ʵ���˶�Ӧ������
ָ��򻯰�:
    No	|InstructionName	|EnumVal|����
    ====|===================|=======|=============================================
    1	|GetImage			|01H	|�Ӵ������϶���ͼ�����ͼ�񻺳���
    2	|GenChar			|02H	|����ԭʼͼ������ָ���������������ļ�������
    3	|Match				|03H	|��ȷ�ȶ������ļ��������е������ļ�
    4	|Search				|04H	|�������ļ��������е������ļ����������򲿷�ָ�ƿ�
    5	|RegModel			|05H	|�������ļ��ϲ�����ģ����������ļ�������
    6	|StoreChar			|06H	|�������������е��ļ����浽flashָ�ƿ���
    7	|LoadChar			|07H	|��flashָ�ƿ��ж�ȡһ��ģ�嵽����������
    8	|UpChar				|08H	|�������������е��ļ��ϴ�����λ��
    9	|DownChar			|09H	|����λ������һ�������ļ�������������
    10	|UpImage			|0aH	|�ϴ�ԭʼͼ��
    11	|DownImage			|0bH	|����ԭʼͼ��
    12	|DeleteChar			|0cH	|ɾ��flashָ�ƿ��е�һ�������ļ�
    13	|Empty				|0dH	|���flashָ�ƿ�
    14	|WriteReg			|0eH	|дSOCϵͳ�Ĵ���
    15	|ReadSysPara		|0FH	|��ϵͳ��������
    16	|SetPwd				|12H	|�����豸���ֿ���
    17	|VfyPwd				|13H	|��֤�豸���ֿ���
    18	|GetRandomCode		|14H	|���������
    19	|SetChipAddr		|15H	|����оƬ��ַ
    20	|ReadINFPage		|16H	|��ȡFLASH Information Page����
    21	|Port_Control		|17H	|ͨѶ�˿ڣ�UART/USB�����ؿ���
    22	|WriteNotepad		|18H	|д���±�
    23	|ReadNotepad		|19H	|�����±�
    24	|BurnCode			|1aH	|��дƬ��FLASH
    25	|HighSpeedSearch	|1bH	|��������FLASH
    26	|GenBinImage		|1cH	|���ɶ�ֵ��ָ��ͼ��
    27	|ValidTempleteNum	|1dH	|����Чģ�����
    28	|ReadIndexTable		|1fH	|��������
    29	|GetEnrollImage		|29H	|ע���û�ȡͼ��
    30	|Cancel				|30H	|ȡ��ָ��
    31	|AutoEnroll			|31H	|�Զ�ע��
    32	|AutoIdentify		|32H	|�Զ���֤
    33	|Sleep				|33H	|����ָ��
    34	|GetChipSN			|34H	|��ȡоƬΨһ���к�
    35	|HandShake			|35H	|����ָ��
    36	|CheckSensor		|36H	|У�鴫����
    37	|ControlLED			|40H	|����LED
*/
enum CmdCodeSyno{
    __SCC(Syno,GetImage)=0x01,
    __SCC(Syno,GenChar)=0x02,
    __SCC(Syno,Match)=0x03,
    __SCC(Syno,Search)=0x04,
    __SCC(Syno,RegModel)=0x05,
    __SCC(Syno,StoreChar)=0x06,
    __SCC(Syno,LoadChar)=0x07,
    __SCC(Syno,UpChar)=0x08,
    __SCC(Syno,DownChar),
    __SCC(Syno,UpImage)=0x0a,
    __SCC(Syno,DownImage),
    __SCC(Syno,DeleteChar)=0x0c,
    __SCC(Syno,Empty),
    __SCC(Syno,WriteReg),
    __SCC(Syno,ReadSysPara),
    __SCC(Syno,SetPwd),
    __SCC(Syno,VfyPwd),
    __SCC(Syno,GetRandomCode),
    __SCC(Syno,SetChipAddr),
    __SCC(Syno,ReadINFPage)=0x16,
    __SCC(Syno,Port_Control),
    __SCC(Syno,WriteNotepad),
    __SCC(Syno,ReadNotepad),
    __SCC(Syno,BurnCode),
    __SCC(Syno,HighSpeedSearch),
    __SCC(Syno,GenBinImage),
    __SCC(Syno,ValidTemplateNum),
    __SCC(Syno,ReadIndexTable)=0x1f,
    __SCC(Syno,GetEnrollImage)=0x29,
    __SCC(Syno,Cancel),
    __SCC(Syno,AutoEnrollImage),
    __SCC(Syno,AutoIdentify),
    __SCC(Syno,GetChipSN),
    __SCC(Syno,HandShake),
    __SCC(Syno,CalibrateSensor),
    __SCC(Syno,����ģ��Ψһ���к�),
    __SCC(Syno,��ȡģ��Ψһ���к�),
    __SCC(Syno,��ȡָ���㷨��汾��),
    __SCC(Syno,��ȡ�̼���汾��),
    __SCC(Syno,ControlLED)=0x40,
    __SCC(Syno,������ɫLED),
};

#pragma endregion

#pragma region LOGЭ����

__DLC(LOG,Info);
__DLC(LOG,MeasureTimeStart);
__DLC(LOG,MeasureTimeEnd);
__DLC(LOG,AdvDbg_AdjImg);

enum CmdCodeLOG{
    __SCC(LOG,Info)                 =0xCC00,//��ʾ��λ����Info
    __SCC(LOG,MeasureTimeStart)     =0xCC01,//��ʼ��ʱ
    __SCC(LOG,MeasureTimeEnd)       =0xCC02,//������ʱ
    __SCC(LOG,AdvDbg_AdjImg)        =0xCC03,//��õ����е�ͼ��
};

#pragma endregion

#pragma region GD32F30Э����

__DLC(GD32F30,GetRawImage);
__DLC(GD32F30,GetTestImage);
__DLC(GD32F30,ReadRegister);
__DLC(GD32F30,DeviceInfo);

enum CmdCodeGD32F30{
    __SCC(GD32F30,GetTestImage)=0x031F,     //���ԭʼͼ��
    CMD_DEVICE_RESET=0x0320,
    CMD_DETECT_FINGER=0x0321,
    __SCC(GD32F30,GetRawImage)=0x0322,      //��ò���ͼ��
    CMD_GET_REDRESS_IMAGE=0x0323,
    CMD_UPLOAD_IMAGE=0x0324,
    CMD_GEN_CHAR=0x0325,
    CMD_MATCH_CHAR=0x0326,
    CMD_STORE_CHAR=0x0327,
    CMD_SEARCH_CHAR=0x0328,
    CMD_DELETE_CHAR=0x0329,
    CMD_EMPTY_CHAR=0x032A,
    CMD_VERIFY_CHAR=0x032B,
    CMD_GET_CHAR=0x032C,
    CMD_PUT_CHAR=0x032D,
    CMD_GET_MBINDEX=0x032E,
    __SCC(GD32F30,ReadRegister)=0x032F,     //���Ĵ���
    __SCC(GD32F30,WriteRegister)=0x0330,    //д�Ĵ���
    CMD_READ_PAR_TABLE=0x0331,
    CMD_SET_BAUD_RATE=0x0332,
    CMD_SET_SECURLEVEL=0x0333,
    CMD_SET_CMOS_PARA=0x0334,
    CMD_RESUME_FACTORY=0x0335,
    CMD_MERGE_CHAR=0x0336,
    CMD_SET_PSW=0x0337,
    CMD_SET_ADDRESS=0x0338,
    CMD_GET_RANDOM=0x0339,
    CMD_DOWNLOAD_IMAGE=0x0340,
    CMD_ERASE_PROGRAM=0x0341,
    CMD_STORE_CHAR_DIRECT=0x0342,
    CMD_READ_CHAR_DIRECT=0x0343,
    CMD_GET_FIRSTVALID_ADD=0x0344,
    CMD_CHIP_ERASE=0x0380,
    __SCC(GD32F30,DeviceInfo)=0x0381,       //��ȡ�豸��Ϣ
};

#pragma endregion
