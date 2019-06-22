#include "stdafx.h"

// GD32's ���ԭʼͼ�������
__ILC(GD32F30,GetRawImage){
    setProgress(50);
    MyLog::trace("���յ����ݰ�,��СΪ%d",response.size());
    MyLog::trace("�߳������̷߳�����ϢWM_GET_RAW_IMAGE");
    sendMainDialogMessage(WM_GET_RAW_IMAGE);
    setProgress(75);

    if(response.size()==0){
        MyLog::user("�������ݳ�ʱ");
    } else{
        saveImage(response);
        setProgress(100);
        MyLog::trace("����ͼƬ���");
        MyLog::user("�������ݳɹ�");
    }
    flow.execVal();
}

// GD32's ��ò���ͼ�������
__ILC(GD32F30,GetTestImage){
    setProgress(50);
    MyLog::trace("���յ����ݰ�,��СΪ%d",response.size());
    MyLog::trace("�߳������̷߳�����ϢWM_GET_TEST_IMAGE");
    sendMainDialogMessage(WM_GET_TEST_IMAGE);
    setProgress(75);

    if(response.size()==0){
        MyLog::user("���ձ������ݳ�ʱ");
    } else{
        saveBGImg(response);
        setProgress(100);
        MyLog::trace("����ͼƬ���");
        MyLog::user("���ձ������ݳɹ�");
    }
    flow.execVal();
}

// GD32's ���Ĵ���������
__ILC(GD32F30,ReadRegister){
    setProgress(50);
    MyLog::trace("���յ����ݰ�,��СΪ%d",response.size());
    MyLog::trace("�߳������̷߳�����ϢWM_READ_REGISTER");
    sendMainDialogMessage(WM_READ_REGISTER);
    setProgress(75);

    if(response.size()==0){
        MyLog::user("�������ݳ�ʱ");
    } else{
        // �ó�response��ĵ�һ���ֽ�,�������,��ֵ��EditReadRegVal
        setText(editReadRegVal,MyString::Format("%X",response.getPointer()[0]));
        MyLog::user("�������ݳɹ�");
    }
    flow.execVal();
}

//GD32's ����豸��Ϣ������
__ILC(GD32F30,DeviceInfo){
    /*
    [02] 44 30 30 2E 30 30 2E 30 31 00 [4D 61 79 20 32 37 20 32 30 31 39] 00 31 38 3A 33 30 3A 34 34 00
    PC Application log dialog display:
      Finger Chip Version: 03           (if 0xFF then directly display "Unknown Type")
      Firmware Version: D00.00.01       (un-available for parter/customer)
      Build Time: May 27 2019 15:48:56  (un-available for parter/customer)
    */
    // оƬ�汾
    char ChipVersion;
    // �̼��汾
    char* FirmwareVersion;
    // ��������
    char* BuildDate;
    // ����ʱ��
    char* BuildTime;
    // response���ֽ�����ͷ
    uint8_t* ptr=response.getPointer();

    // ��һ���ֽ�ΪоƬ�汾 ChipVersion
    ChipVersion=*ptr;

    // ������һ���ַ���Ϊ�̼��汾 FirmwareVersion
    FirmwareVersion=(char*)++ptr;
    while(*ptr)ptr++;

    // ������һ���ַ���Ϊ�������� BuildDate
    BuildDate=(char*)++ptr;
    while(*ptr)ptr++;

    // ������һ���ַ���Ϊ����ʱ�� BuildTime
    BuildTime=(char*)++ptr;

    // ���ChipVersionΪ0xFF(��char��Ϊ-1),����δ֪�汾
    if(ChipVersion==-1){
        MyLog::user("Finger Chip Version: Unknown Type");
    } else{
        MyLog::user("Finger Chip Version: %x",ChipVersion);
    }
    MyLog::user("Firmware Version: %s",FirmwareVersion);
    MyLog::user("Build Time: %s %s",BuildDate,BuildTime);

    flow.execVal();
}
