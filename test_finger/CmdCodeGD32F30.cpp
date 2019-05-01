#include "stdafx.h"

void READ_REGISTER_Listener::listen(DataPacket response){
    if(response.size()==0){
        MyLog.print(Log::LOGU,"�������ݳ�ʱ");
    } else{
        setText(editReadRegVal,MyString::Format("%X",response.getPointer()[0]));
        MyLog.print(Log::LOGU,"�������ݳɹ�");
    }
    sendMessage(WM_READ_REGISTER);
    updateControlDisable(actReadedReg);
}

void GET_TEST_IMAGE_Listener::listen(DataPacket response){
    progress->SetPos(50);
    MyLog.print(Log::LOGD,"���յ����ݰ�,��СΪ%d",response.size());
    MyLog.print(Log::LOGD,"�߳������̷߳�����ϢCMD_GET_TEST_IMAGE");
    sendMessage(WM_GET_TEST_IMAGE);
    progress->SetPos(75);
    MyLog.print(Log::LOGD,"��Ϣ�������յ���ϢWM_GET_TEST_IMAGE");

    if(response.size()==0){
        MyLog.print(Log::LOGU,"���ձ������ݳ�ʱ");
    } else{
        saveImage(_T("collectedBGI"),response);
        progress->SetPos(100);
        MyLog.print(Log::LOGD,"����ͼƬ���");
        MyLog.print(Log::LOGU,"���ձ������ݳɹ�");
    }
}

void GET_RAW_IMAGE_Listener::listen(DataPacket response){
    SendMessage(hwnd,WM_GET_RAW_IMAGE,WM_GET_RAW_IMAGE,0);
    progress->SetPos(50);
    MyLog.print(Log::LOGD,"���յ����ݰ�,��СΪ%d",response.size());
    MyLog.print(Log::LOGD,"�߳������̷߳�����ϢWM_GET_RAW_IMAGE");
    progress->SetPos(75);
    MyLog.print(Log::LOGD,"��Ϣ�������յ���ϢWM_GET_RAW_IMAGE");

    if(response.size()==0){
        MyLog.print(Log::LOGU,"�������ݳ�ʱ");
    } else{
        saveImage(_T("collectedImage"),response);
        progress->SetPos(100);
        MyLog.print(Log::LOGD,"����ͼƬ���");
        MyLog.print(Log::LOGU,"�������ݳɹ�");
    }
}
