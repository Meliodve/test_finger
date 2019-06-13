#include "stdafx.h"

//GD32's ���ԭʼͼ�������
__ILC(GD32F30,GetRawImage){
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
    ExecFlowVal();
}

__ILC(GD32F30,GetTestImage){
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
    ExecFlowVal();
}

__ILC(GD32F30,ReadRegister){
    if(response.size()==0){
        MyLog::user("�������ݳ�ʱ");
    } else{
        setText(editReadRegVal,MyString::Format("%X",response.getPointer()[0]));
        MyLog::user("�������ݳɹ�");
    }
    sendMainDialogMessage(WM_READ_REGISTER);
    MainDialogCtrlValidity::Work();
    ExecFlowVal();
}

__ILC(GD32F30,DeviceInfo){
    /*
    [02] 44 30 30 2E 30 30 2E 30 31 00 [4D 61 79 20 32 37 20 32 30 31 39] 00 31 38 3A 33 30 3A 34 34 00
    PC Application log dialog display:
      Finger Chip Version: 03           (if 0xFF then directly display "Unknown Type")
      Firmware Version: D00.00.01       (un-available for parter/customer)
      Build Time: May 27 2019 15:48:56  (un-available for parter/customer)
    */
    char ChipVersion;
    char* FirmwareVersion;
    char* BuildDate;
    char* BuildTime;
    uint8_t* ptr=response.getPointer();
    ChipVersion=*ptr;
    FirmwareVersion=(char*)++ptr;
    while(*ptr)ptr++;
    BuildDate=(char*)++ptr;
    while(*ptr)ptr++;
    BuildTime=(char*)++ptr;
    if(ChipVersion==-1){
        MyLog::user("Finger Chip Version: Unknown Type");
    } else{
        MyLog::user("Finger Chip Version: %x",ChipVersion);
    }
    MyLog::user("Firmware Version: %s",FirmwareVersion);
    MyLog::user("Build Time: %s %s",BuildDate,BuildTime);
    
    ExecFlowVal();
}