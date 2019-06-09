#include"stdafx.h"

__ILC(ASFComm,GetRawImage){
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

__ILC(ASFComm,GetTestImage){
    progress->SetPos(50);
    MyLog::debug("���յ����ݰ�,��СΪ%d",response.size());
    MyLog::debug("�߳������̷߳�����ϢCMD_GET_TEST_IMAGE");
    sendMainDialogMessage(WM_GET_TEST_IMAGE);
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

__ILC(ASFComm,ReadRegister){
    if(response.size()==0){
        MyLog::user("�������ݳ�ʱ");
    } else{
        setText(editReadRegVal,MyString::Format("%X",response.getPointer()[0]));
        MyLog::user("�������ݳɹ�");
    }
    sendMainDialogMessage(WM_READ_REGISTER);
    MainDialogCtrlValidity::Work();
}

__ILC(ASFComm,WriteRegister){
    //DoNothing
}

__ILC(ASFComm,ToSleep){
    //DoNothing
}

__ILC(ASFComm,ToIdle){
    //DoNothing
}

__ILC(ASFComm,MyLog){
    int level=response.getPointer()[0];
    response.readData(1);
    MyLog::print((MyLog::LogLevel)level,(char*)response.getPointer());
}

__ILC(ASFComm,AdjustingImage){
    int imgSize=MyString::ParseInt(MyString((char*)response.getPointer(),2));
    response.readData(2);
    conf["id"]=MyString((char*)response.getPointer(),response.size()-imgSize*imgSize);
    response.readData(response.size()-imgSize*imgSize);
    uint8_t img64[64*64],img32[32*32];
    if(imgSize==16){
        imgSizeX2(response.getPointer(),imgSize,imgSize,img32);
        imgSize=imgSize+imgSize;
        imgSizeX2(img32,imgSize,imgSize,img64);
    } else if(imgSize==32){
        imgSizeX2(response.getPointer(),imgSize,imgSize,img64);
    } else{
        memcpy(img64,response.getPointer(),imgSize*imgSize);
    }
    saveBmp(64,64,img64,"collectedTempImage",conf["AdvDbg_ImgId"]);
    uint8_t Histogram[256*64];
    generateHistogram(Histogram,256,64,response.getPointer(),32,32);
    saveBmp(256,64,Histogram,"collectedTempImage",MyString("Histogram")+conf["AdvDbg_ImgId"]);
    sendMainDialogMessage(WM_APPEND_CONTROLS);
    response.readData(32*32);
}
