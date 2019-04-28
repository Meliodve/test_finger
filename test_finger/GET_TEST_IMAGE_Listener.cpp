#include "stdafx.h"
#include "GET_TEST_IMAGE_Listener.h"

void GET_TEST_IMAGE_Listener::listen(DataPacket response){
    progress->SetPos(50);
    MyLog.print(Log::LOGD,"Serial Thread:2���յ����ݰ�,��СΪ%d",response.len);
    MyLog.print(Log::LOGD,"Serial Thread:3�߳������̷߳�����ϢCMD_GET_TEST_IMAGE");
    SendMessage(hwnd,WM_GET_TEST_IMAGE,WM_GET_TEST_IMAGE,0);
    progress->SetPos(75);
    MyLog.print(Log::LOGD,"Main Thread:4��Ϣ�������յ���ϢWM_GET_TEST_IMAGE");

    if(response.len==0){
        MyLog.print(Log::LOGU,"���ձ������ݳ�ʱ");
    } else{
        saveImage(_T("collectedBGI"),response);
        progress->SetPos(100);
        MyLog.print(Log::LOGD,"Main Thread:5����ͼƬ���");
        MyLog.print(Log::LOGU,"���ձ������ݳɹ�");
    }
}
