#include "stdafx.h"

// ��־���水ť����¼�
void MainDialog::OnBnClickedBtnSaveLog(){
    MyFile::LogSaveAs(
        [&](FILE* fp){
            fprintf_s(fp,"%s",(const char*)getText(editLog));
        }
    );
}

// ������־��ť����¼�
void MainDialog::OnBnClickedBtnDevLog(){
    MyLog::DevelopLog();
}

// �����Կ���¼�
void MainDialog::OnCbnCloseupCmbLogLevel(){
    static clock_t firstTime=0,secondTime=0;
    if(firstTime==0){
        firstTime=clock();
    } else{
        if(secondTime==0){
            secondTime=clock();
        } else{
            clock_t now=clock();
            if(now-firstTime>2000){
                firstTime=secondTime;
                secondTime=now;
            } else{
                // �����߼�����ģʽ
                conf["AdvDbg"]=Stringify(true);
                btnAdvDbg->ShowWindow(SW_SHOW);
            }
        }
    }
}

// �豸��Ϣ��ť����¼�
void MainDialog::OnBnClickedBtnDeviceInfo(){
    // ��������
    flow.clear();
    // ���� 0:����<����豸��Ϣ>����
    flow.add(0,[](int& result){
        MainDialogCtrlValidity::Working();
        comm.request(SII(DeviceInfo));
        setProgress(100*flow.percent());
        flow.next();
        return false;
    });
    // ���� 1:����豸��Ϣ����,�ƺ���
    flow.add(1,[](int& result){
        setProgress(100*flow.percent());
        MyLog::user("��ȡ�豸��Ϣ����");
        flow.clear();
        MainDialogCtrlValidity::Work();
        return false;
    });
    // ��ʼִ������
    flow.start();
}

// ������������¼�
void MainDialog::OnBnClickedBtnCancel(){
    flow.terminate();
    setProgress(0);
    MyLog::user("ȡ���˲���");
    MainDialogCtrlValidity::Work();
}

// ������־�����¼�
void MainDialog::OnBnClickedBtnClearLog(){
    setText(editLog,"");
}

// ���ð�ť����¼�
void MainDialog::OnBnClickedBtnSetting(){
    static SettingDialog* dialog;
    if(dialog){
        delete dialog;
    }
    dialog=new SettingDialog();
    dialog->Create(IDD_SETTING_DIALOG,this);
    dialog->ShowWindow(SW_SHOW);
}
