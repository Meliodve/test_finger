#include "stdafx.h"

__ILC(Syno,GetImage){
    int front=response.getPointer()[0];
    switch(front){
        case 0x00://¼��ɹ�
            break;
        case 0x01://�հ��д�
            ASF_ERROR(5);
            break;
        case 0x02://������������ָ
            MyLog.debug("������������ָ");
            break;
        case 0x03://¼�벻�ɹ����������
            MyLog.debug("¼�벻�ɹ����������");
            break;
    }
    ExecFlow(front);
}

__ILC(Syno,UpImage){
    int front=response.getPointer()[0];
    switch(front){
        case 0x00://�ɹ�
            response.readData(1);
            SendMessage(hwnd,WM_GET_RAW_IMAGE,WM_GET_RAW_IMAGE,0);
            progress->SetPos(50);
            MyLog.print(Log::LOGD,"���յ����ݰ�,��СΪ%d",response.readSize());
            MyLog.print(Log::LOGD,"�߳������̷߳�����ϢWM_GET_RAW_IMAGE");
            progress->SetPos(75);
            MyLog.print(Log::LOGD,"��Ϣ�������յ���ϢWM_GET_RAW_IMAGE");

            saveImage(_T("collectedImage"),response);
            progress->SetPos(100);
            MyLog.print(Log::LOGD,"����ͼƬ���");
            MyLog.print(Log::LOGU,"�������ݳɹ�");

            break;
        case 0x01://�հ��д�
            ASF_ERROR(5);
            break;
        case 0x0f://���ܷ��ͺ������ݰ�
            MyLog.debug("���ܷ��ͺ������ݰ�");
            break;
    }
    ExecFlow(front);
}

__ILC(Syno,GenChar){
    int front=response.getPointer()[0];
    switch(front){
        case 0x00://�ɹ�
            break;
        case 0x01://�հ��д�
            ASF_ERROR(5);
            break;
        case 0x06://ͼ��̫��,����������
            MyLog.print(Log::LOGE,"ͼ��̫��,����������");
            break;
        case 0x07://ͼ������̫��,����������
            MyLog.print(Log::LOGE,"ͼ������̫��,����������");
            break;
        case 0x15://ͼ�񻺳�����û��ͼ��,������ͼ��
            MyLog.print(Log::LOGE,"ͼ�񻺳�����û��ͼ��,������ͼ��");
            break;
        case 0x1b://�Ĵ����趨���ݴ���
            MyLog.print(Log::LOGE,"�Ĵ����趨���ݴ���");
            break;
        case 0x28://��ǰָ��ģ����֮ǰ��ģ��֮���й���
            MyLog.print(Log::LOGU,"��ǰָ��ģ����֮ǰ��ģ��֮���й���");
            break;
    }
    ExecFlow(front);
}

__ILC(Syno,GetEnrollImage){
    int front=response.getPointer()[0];
    switch(front){
        case 0x00://�ɹ�
            break;
        case 0x01://�հ��д�
            ASF_ERROR(5);
            break;
        case 0x02://������������ָ
            MyLog.debug("������������ָ");
            break;
        case 0x03://¼�벻�ɹ����������
            MyLog.debug("¼�벻�ɹ����������");
            break;
    }
    ExecFlow(front);
}

__ILC(Syno,RegModel){
    int front=response.getPointer()[0];
    switch(front){
        case 0x00://�ɹ�
            break;
        case 0x01://�հ��д�
            ASF_ERROR(5);
            break;
        case 0x0a://�ϲ�ʧ��
            MyLog.debug("�ϲ�ʧ��");
            break;
    }
    ExecFlow(front);
}

__ILC(Syno,StoreChar){
    int front=response.getPointer()[0];
    switch(front){
        case 0x00://�ɹ�
            break;
        case 0x01://�հ��д�
            ASF_ERROR(5);
            break;
        case 0x0b://PageID����ָ�ƿⷶΧ
            MyLog.debug("PageID����ָ�ƿⷶΧ");
            break;
        case 0x18://дFLASH����
            MyLog.debug("дFLASH����");
            break;
    }
    ExecFlow(front);
}

__ILC(Syno,Search){
    int front=response.getPointer()[0];
    switch(front){
        case 0x00://�ɹ�
            break;
        case 0x01://�հ��д�
            ASF_ERROR(5);
            break;
        case 0x09://û������
            MyLog.debug("û������");
            break;
        case 0x17://��ָû���ƶ�
            MyLog.debug("��ָû���ƶ�");
            break;
    }
    ExecFlow(front);
}

__ILC(Syno,ReadIndexTable){
    int front=response.getPointer()[0];
    switch(front){
        case 0x00://�ɹ�
            response.readData(1);
            if(response.readSize()!=32){
                MyLog.error("ReadIndexTable����ִ��ʧ��");
            } else{
                MyString msg="��ע��ָ�Ʊ��Ϊ:";
                std::vector<int>v;
                uint8_t* p=response.getPointer();
                for(int i=0;i<32;i++){
                    if(p[i]){
                        for(int j=0;j<8;j++){
                            if(p[i]&(1<<j)){
                                v.push_back(i*8+j);
                            }
                        }
                    }
                }
                if(v.size()){
                    msg+=MyString::IntToMyString(v[0]);
                    for(int i=1;i<v.size();i++){
                        msg+=MyString(",")+MyString::IntToMyString(v[i]);
                    }
                }
                MyLog.user(msg);
            }
            break;
        case 0x01://�հ��д�
            ASF_ERROR(5);
            break;
    }
}
