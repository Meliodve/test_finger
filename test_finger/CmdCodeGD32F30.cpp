#include "stdafx.h"

void READ_REGISTER_Listener::listen(DataPacket response){
    if(response.size()==0){
        MyLog::user("�������ݳ�ʱ");
    } else{
        setText(editReadRegVal,MyString::Format("%X",response.getPointer()[0]));
        MyLog::user("�������ݳɹ�");
    }
    sendMessage(WM_READ_REGISTER);
    CtrlValidity::Work();
}

void GET_TEST_IMAGE_Listener::listen(DataPacket response){
    progress->SetPos(50);
    MyLog::debug("���յ����ݰ�,��СΪ%d",response.size());
    MyLog::debug("�߳������̷߳�����ϢCMD_GET_TEST_IMAGE");
    sendMessage(WM_GET_TEST_IMAGE);
    progress->SetPos(75);
    MyLog::debug("��Ϣ�������յ���ϢWM_GET_TEST_IMAGE");

    if(response.size()==0){
        MyLog::user("���ձ������ݳ�ʱ");
    } else{
        saveImage(_T("collectedBGI"),response);
        progress->SetPos(100);
        MyLog::debug("����ͼƬ���");
        MyLog::user("���ձ������ݳɹ�");
    }
}

void GET_RAW_IMAGE_Listener::listen(DataPacket response){
    SendMessage(hwnd,WM_GET_RAW_IMAGE,WM_GET_RAW_IMAGE,0);
    progress->SetPos(50);
    MyLog::debug("���յ����ݰ�,��СΪ%d",response.size());
    MyLog::debug("�߳������̷߳�����ϢWM_GET_RAW_IMAGE");
    progress->SetPos(75);
    MyLog::debug("��Ϣ�������յ���ϢWM_GET_RAW_IMAGE");

    if(response.size()==0){
        MyLog::user("�������ݳ�ʱ");
    } else{
        saveImage(_T("collectedImage"),response);
        progress->SetPos(100);
        MyLog::debug("����ͼƬ���");
        MyLog::user("�������ݳɹ�");
    }
}
