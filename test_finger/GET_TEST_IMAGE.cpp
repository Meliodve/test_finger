#include "stdafx.h"
#include "GET_TEST_IMAGE.h"

void GET_TEST_IMAGE_Listener::listen(DataPacket response){
    progress->SetPos(50);
    MyLog.print(Log::LOGD,"���յ����ݰ�,��СΪ%d",response.len);
    MyLog.print(Log::LOGD,"�߳������̷߳�����ϢCMD_GET_TEST_IMAGE");
    SendMessage(hwnd,WM_GET_TEST_IMAGE,WM_GET_TEST_IMAGE,0);
    progress->SetPos(75);
    MyLog.print(Log::LOGD,"��Ϣ�������յ���ϢWM_GET_TEST_IMAGE");

    if(response.len==0){
        MyLog.print(Log::LOGU,"���ձ������ݳ�ʱ");
    } else{
        saveImage(_T("collectedBGI"),response);
        progress->SetPos(100);
        MyLog.print(Log::LOGD,"����ͼƬ���");
        MyLog.print(Log::LOGU,"���ձ������ݳɹ�");
    }
}
