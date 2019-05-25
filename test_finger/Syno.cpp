#include "stdafx.h"

__ILC(Syno,GetImage){
    int front=response.getPointer()[0];
    switch(front){
        case 0x00://¼��ɹ�
            break;
        case 0x01://�հ��д�
            ASF_ERROR(5);
            return;
        case 0x02://������������ָ
            MyLog.user("������������ָ");
            break;
        case 0x03://¼�벻�ɹ����������
            MyLog.user("¼�벻�ɹ����������");
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
            MyLog.debug("���յ����ݰ�,��СΪ%d",response.readSize());
            MyLog.debug("�߳������̷߳�����ϢWM_GET_RAW_IMAGE");
            progress->SetPos(75);
            MyLog.debug("��Ϣ�������յ���ϢWM_GET_RAW_IMAGE");

            saveImage(_T("collectedImage"),response);
            progress->SetPos(100);
            MyLog.debug("����ͼƬ���");
            MyLog.user("�������ݳɹ�");

            break;
        case 0x01://�հ��д�
            ASF_ERROR(5);
            return;
        case 0x0f://���ܷ��ͺ������ݰ�
            MyLog.user("���ܷ��ͺ������ݰ�");
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
            return;
        case 0x06://ͼ��̫��,����������
            MyLog.user("ͼ��̫��,����������");
            break;
        case 0x07://ͼ������̫��,����������
            MyLog.user("ͼ������̫��,����������");
            break;
        case 0x15://ͼ�񻺳�����û��ͼ��,������ͼ��
            MyLog.user("ͼ�񻺳�����û��ͼ��,������ͼ��");
            break;
        case 0x1b://�Ĵ����趨���ݴ���
            MyLog.user("�Ĵ����趨���ݴ���");
            break;
        case 0x28://��ǰָ��ģ����֮ǰ��ģ��֮���й���
            MyLog.user("��ǰָ��ģ����֮ǰ��ģ��֮���й���");
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
            return;
        case 0x02://������������ָ
            MyLog.user("������������ָ");
            break;
        case 0x03://¼�벻�ɹ����������
            MyLog.user("¼�벻�ɹ����������");
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
            return;
        case 0x0a://�ϲ�ʧ��
            MyLog.user("�ϲ�ʧ��");
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
            return;
        case 0x0b://PageID����ָ�ƿⷶΧ
            MyLog.user("PageID����ָ�ƿⷶΧ");
            break;
        case 0x18://дFLASH����
            MyLog.user("дFLASH����");
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
            return;
        case 0x09://û������
            MyLog.user("û������");
            break;
        case 0x17://��ָû���ƶ�
            MyLog.user("��ָû���ƶ�");
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
                MyLog.user("ReadIndexTable����ִ��ʧ��");
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
            return;
    }
    ExecFlow(front);
}

__ILC(Syno,Match){
    int front=response.getPointer()[0];
    switch(front){
        case 0x00://�ɹ�
            response.readData(1);
            MyLog.user("ָ��ƥ��ɹ�,�÷�:%d",response.getPointer()[0]*256+response.getPointer()[1]);
            break;
        case 0x01://�հ��д�
            ASF_ERROR(5);
            return;
        case 0x08://ָ�Ʋ�ƥ��
            MyLog.user("ָ�Ʋ�ƥ��");
            break;
    }
    ExecFlow(front);
}

__ILC(Syno,LoadChar){
    int front=response.getPointer()[0];
    switch(front){
        case 0x00://�ɹ�
            break;
        case 0x01://�հ��д�
            ASF_ERROR(5);
            return;
        case 0x0b://��ų���ָ�ƿⷶΧ
            MyLog.user("��ų���ָ�ƿⷶΧ");
            break;
        case 0x0c://�����д��ģ����Ч
            MyLog.user("�����д��ģ����Ч");
            break;
    }
    ExecFlow(front);
}
