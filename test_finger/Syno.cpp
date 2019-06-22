#include "stdafx.h"

// ���ݷ���ֵ����Syno's ������Ϣ
const char* SynoFormatMessage(int errorCode){
    switch(errorCode){
        //case 0x00:return "ָ��ִ����ϻ�OK";
    case 0x00:return "";
    case 0x01:return "���ݰ����մ���";
    case 0x02:return "��������û����ָ";
    case 0x03:return "¼��ָ��ͼ��ʧ�ܻ�¼���������";
    case 0x04:return "ָ��ͼ��̫�ɡ�̫��������������";
    case 0x05:return "ָ��ͼ��̫ʪ��̫��������������";
    case 0x06:return "ָ��ͼ��̫�Ҷ�����������";
    case 0x07:return "ָ��ͼ����������������̫�٣������̫С��������������";
    case 0x08:return "ָ�Ʋ�ƥ��";
    case 0x09:return "û������ָ��";
    case 0x0a:return "�����ϲ�ʧ��";
    case 0x0b:return "����ָ�ƿ�ʱ��ַ��ų���ָ�ƿⷶΧ";
    case 0x0c:return "��ָ�ƿ��ģ��������Ч";
    case 0x0d:return "�ϴ�����ʧ��";
    case 0x0e:return "ģ�鲻�ܽ��պ������ݰ�";
    case 0x0f:return "�ϴ�ͼ��ʧ��";
    case 0x10:return "ɾ��ģ��ʧ��";
    case 0x11:return "���ָ�ƿ�ʧ��";
    case 0x12:return "���ܽ���͹���״̬";
    case 0x13:return "�����ȷ";
    case 0x14:return "ϵͳ��λʧ��";
    case 0x15:return "��������û����Чԭʼͼ��������ͼ��";
    case 0x16:return "��������ʧ��";
    case 0x17:return "����ָ�ƻ����βɼ�֮����ָû���ƶ���";
    case 0x18:return "��дFLASH����";
    case 0x19:return "���������ʧ��";
    case 0x1a:return "��Ч�Ĵ�����";
    case 0x1b:return "�Ĵ����趨���ݴ����";
    case 0x1c:return "���±�ҳ��ָ������";
    case 0x1d:return "�˿ڲ���ʧ��";
    case 0x1e:return "�Զ�ע�ᣨenroll��ʧ��";
    case 0x1f:return "ָ�ƿ���";
    case 0x20:return "�豸��ַ����";
    case 0x21:return "��������";
    case 0x22:return "ָ��ģ��ǿ�";
    case 0x23:return "ָ��ģ��Ϊ��";
    case 0x24:return "ָ�ƿ�Ϊ��";
    case 0x25:return "¼��������ô���";
    case 0x26:return "��ʱ";
    case 0x27:return "ָ���Ѵ���";
    case 0x28:return "ָ��ģ���й���";
    case 0x29:return "��������ʼ��ʧ��";
    case 0x2A:return "ģ��Ψһ���кŷǿ�";
    case 0x2B:return "ģ��Ψһ���к�Ϊ��";
    case 0x2C:return "OTP����ʧ��";
    case 0xf0:return "�к������ݰ���ָ���ȷ���պ���0xf0Ӧ��";
    case 0xf1:return "�к������ݰ���ָ��������0xf1Ӧ��";
    case 0xf2:return "��д�ڲ�FLASHʱ��У��ʹ���";
    case 0xf3:return "��д�ڲ�FLASHʱ������ʶ����";
    case 0xf4:return "��д�ڲ�FLASHʱ�������ȴ���";
    case 0xf5:return "��д�ڲ�FLASHʱ�����볤��̫��";
    case 0xf6:return "��д�ڲ�FLASHʱ����дFLASHʧ��";
    default:return "";
    }
}

// ��response�ı�׼����
// ��ֻ�Դ�����Ϣ�������,Ȼ��ִ����һ������
void standardProcessResponse(DataPacket& response){
    int retVal=response.getPointer()[0];
    MyLog::user(SynoFormatMessage(retVal));
    flow.execRef(retVal);
}

// �Ӵ������϶���ͼ�����ͼ�񻺳���
__ILC(Syno,GetImage){
    standardProcessResponse(response);
}

// ����ԭʼͼ������ָ���������������ļ�������
__ILC(Syno,GenChar){
    standardProcessResponse(response);
}

// ��ȷ�ȶ������ļ��������е������ļ�
__ILC(Syno,Match){
    int retVal=response.getPointer()[0];
    MyLog::user(SynoFormatMessage(retVal));
    if(retVal==0x00){// �ɹ�
        response.readData(1);
        uint8_t* ptr=response.getPointer();
        MyLog::user("ָ��ƥ��ɹ�,�÷�:%d",ptr[0]*256+ptr[1]);
    }
    flow.execRef(retVal);
}

// �������ļ��������е������ļ����������򲿷�ָ�ƿ�
__ILC(Syno,Search){
    standardProcessResponse(response);
}

// �������ļ��ϲ�����ģ����������ļ�������
__ILC(Syno,RegModel){
    standardProcessResponse(response);
}

// �������������е��ļ����浽flashָ�ƿ���
__ILC(Syno,StoreChar){
    standardProcessResponse(response);
}

// ��flashָ�ƿ��ж�ȡһ��ģ�嵽����������
__ILC(Syno,LoadChar){
    standardProcessResponse(response);
}

// �ϴ�ԭʼͼ��
__ILC(Syno,UpImage){
    int retVal=response.getPointer()[0];
    MyLog::user(SynoFormatMessage(retVal));
    if(retVal==0x00){// �ɹ�
        response.readData(1);
        setProgress(50);
        MyLog::trace("���յ����ݰ�,��СΪ%d",response.readSize());
        MyLog::trace("�߳������̷߳�����ϢWM_GET_RAW_IMAGE");
        sendMainDialogMessage(WM_GET_RAW_IMAGE);
        setProgress(75);

        saveImage(response);
        setProgress(100);
        MyLog::trace("����ͼƬ���");
        MyLog::user("�������ݳɹ�");
    }
    flow.execRef(retVal);
}

// ɾ��flashָ�ƿ��е�һ�������ļ�
__ILC(Syno,DeleteChar){
    standardProcessResponse(response);
}

// ��������
__ILC(Syno,ReadIndexTable){
    int retVal=response.getPointer()[0];
    MyLog::user(SynoFormatMessage(retVal));
    if(retVal==0x00){// �ɹ�
        response.readData(1);
        // ���ݳ���һ����32���ֽ�
        if(response.readSize()!=32){
            MyLog::user("��������ʧ��");
        } else{
            // ������ע��ָ�Ʊ������
            MyString msg="��ע��ָ�Ʊ��Ϊ: ";
            uint8_t* p=response.getPointer();

            //����32��uint8_t,ÿһλΪ1�����Ӧ��ָ�ƴ���
            for(int i=0;i<32;i++){
                if(p[i]==0){
                    continue;
                }
                for(int j=0;j<8;j++){
                    if(p[i]&(1<<j)){
                        msg+=MyString::IntToMyString(i*8+j)+" ";
                    }
                }
            }
            MyLog::user(msg);
        }
    }
    flow.execRef(retVal);
}

// ע���û�ȡͼ��
__ILC(Syno,GetEnrollImage){
    standardProcessResponse(response);
}
