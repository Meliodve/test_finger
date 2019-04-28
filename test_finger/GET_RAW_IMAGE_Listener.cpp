#pragma once
#include "stdafx.h"
#include "GET_RAW_IMAGE_Listener.h"

void GET_RAW_IMAGE_Listener::listen(DataPacket response){
    SendMessage(hwnd,WM_GET_RAW_IMAGE,WM_GET_RAW_IMAGE,0);
    progress->SetPos(50);
    MyLog.print(Log::LOGD,"Serial Thread:4���յ����ݰ�,��СΪ%d",response.len);
    MyLog.print(Log::LOGD,"Serial Thread:5�߳������̷߳�����ϢWM_GET_RAW_IMAGE");
    progress->SetPos(75);
    MyLog.print(Log::LOGD,"Main Thread:6��Ϣ�������յ���ϢWM_GET_RAW_IMAGE");

    if(response.len==0){
        MyLog.print(Log::LOGU,"�������ݳ�ʱ");
    } else{
        saveImage(_T("collectedImage"),response);
        progress->SetPos(100);
        MyLog.print(Log::LOGD,"Main Thread:7����ͼƬ���");
        MyLog.print(Log::LOGU,"�������ݳɹ�");
    }
}
