#pragma once
#include "stdafx.h"

CEdit* editLog;
CEdit* editNow;
CEdit* editAddress;
CEdit* editPassword;
CEdit* editReadRegAddr;
CEdit* editReadRegVal;
CEdit* editWriteRegAddr;
CEdit* editWriteRegVal;
CEdit* editFingerId;
CComboBox* cmbWay;
CComboBox* cmbBaud;
CComboBox* cmbProtocolType;
CComboBox* cmbLogLevel;
CButton* btnConnect;
CButton* btnAdvDbg;
CButton* btnRawImage;
CButton* btnTestImage;
CButton* btnContinueImage;
CButton* btnContinueBGImg;
CButton* btnSaveLog;
CButton* btnReadReg;
CButton* btnWriteReg;
CButton* btnEnroll;
CButton* btnMatch;
CButton* btnDeviceInfo;
CButton* btnViewEnrollIds;
CButton* btnCancel;
CButton* btnClearLog;
CStatic* image;
CProgressCtrl* progress;

HWND hwnd;

AdvancedDebugDialog* advancedDebugDialog;

void initMainControl(MainDialog* Dlg){
    editLog=(CEdit*)Dlg->GetDlgItem(IDC_EDITLog);
    editNow=(CEdit*)Dlg->GetDlgItem(IDC_EDITNow);
    editAddress=(CEdit*)Dlg->GetDlgItem(IDC_EDITAddress);
    editPassword=(CEdit*)Dlg->GetDlgItem(IDC_EDITPassword);
    editReadRegAddr=(CEdit*)Dlg->GetDlgItem(IDC_EDITreadRegAddr);
    editReadRegVal=(CEdit*)Dlg->GetDlgItem(IDC_EDITreadRegVal);
    editWriteRegAddr=(CEdit*)Dlg->GetDlgItem(IDC_EDITwriteRegAddr);
    editWriteRegVal=(CEdit*)Dlg->GetDlgItem(IDC_EDITwriteRegVal);
    editFingerId=(CEdit*)Dlg->GetDlgItem(IDC_EDITFingerId);
    cmbWay=(CComboBox*)Dlg->GetDlgItem(IDC_CMBWay);
    cmbBaud=(CComboBox*)Dlg->GetDlgItem(IDC_CMBBaud);
    cmbProtocolType=(CComboBox*)Dlg->GetDlgItem(IDC_CMBProtocolType);
    cmbLogLevel=(CComboBox*)Dlg->GetDlgItem(IDC_CMBLogLevel);
    btnConnect=(CButton*)Dlg->GetDlgItem(IDC_BTNConnect);
    btnAdvDbg=(CButton*)Dlg->GetDlgItem(IDC_BTNAdvDbg);
    btnRawImage=(CButton*)Dlg->GetDlgItem(IDC_BTNRawImage);
    btnTestImage=(CButton*)Dlg->GetDlgItem(IDC_BTNTestImage);
    btnContinueImage=(CButton*)Dlg->GetDlgItem(IDC_BTNContinueImage);
    btnContinueBGImg=(CButton*)Dlg->GetDlgItem(IDC_BTNContinueBGImg);
    btnSaveLog=(CButton*)Dlg->GetDlgItem(IDC_BTNSaveLog);
    btnReadReg=(CButton*)Dlg->GetDlgItem(IDC_BTNreadReg);
    btnWriteReg=(CButton*)Dlg->GetDlgItem(IDC_BTNwriteReg);
    btnEnroll=(CButton*)Dlg->GetDlgItem(IDC_BTNEnroll);
    btnMatch=(CButton*)Dlg->GetDlgItem(IDC_BTNMatch);
    btnDeviceInfo=(CButton*)Dlg->GetDlgItem(IDC_BTNDeviceInfo);
    btnViewEnrollIds=(CButton*)Dlg->GetDlgItem(IDC_BTNViewEnrollIds);
    btnCancel=(CButton*)Dlg->GetDlgItem(IDC_BTNCancel);
    btnClearLog=(CButton*)Dlg->GetDlgItem(IDC_BTNClearLog);
    image=(CStatic*)Dlg->GetDlgItem(IDC_IMAGE);
    progress=(CProgressCtrl*)Dlg->GetDlgItem(IDC_PROGRESS);

    editLog->SetLimitText(-1);
    setText(editNow,MyString::Format("�Զ������Ƿ���:%s\r\n",conf["AutoCheck"].c_str()));
    hwnd=Dlg->m_hWnd;

    if(conf["AdvDbg"]=="true"){
        btnAdvDbg->ShowWindow(SW_SHOW);
    }
    advancedDebugDialog=0;

    //���ò�����
    MyString baud[]={"9600","19200","57600","115200","230400","460800","921600"};
    for(int i=0;i<7;i++){
        cmbBaud->InsertString(i,baud[i]);
    }
    cmbBaud->SetCurSel(MyString::ParseInt(conf["Baud"]));

    //оƬ����
    MyString chipType[]={"GD32F30","ASFComm","Syno","SuUSB"};
    for(int i=0;i<4;i++){
        cmbProtocolType->InsertString(i,chipType[i]);
    }
    cmbProtocolType->SetCurSel(MyString::ParseInt(conf["ProtocolType"]));

    //��־��Ϣ�ȼ�
    MyString logLevel[]={"�û�","����","����","����","��ʱ"};
    for(int i=0;i<5;i++){
        cmbLogLevel->InsertString(i,logLevel[i]);
    }
    cmbLogLevel->SetCurSel(3);

    //����������
    progress->SetRange(0,100);
    progress->SetPos(0);

    //���ñ���
    int BigVersion=Version/100;
    int SmlVersion=Version%100;
    if(SmlVersion%10==0){
        SmlVersion/=10;
    }
    setText(Dlg,getText(Dlg)+MyString::Format(" Ver%d.%d",BigVersion,SmlVersion));

    //���ؼ�����Ȩ��
    MainDialogCtrlValidity::InitCtrl();
    MainDialogCtrlValidity::Init();

    //ˢ��ͨ�ŷ�ʽ
    updateCommunityWay();

    //�Զ�������
    if(conf["AutoCheck"]=="true"){
        if(isConnectedNet()){
            if(NetGetVersion()>Version){
                MyLog::user("�пɸ��°汾,�������и���.");
            }
        }
    }
}

void sendMainDialogMessage(int Message){
    SendMessage(hwnd,Message,Message,0);
}

std::vector<int>* idle=new std::vector<int>();
std::vector<int>* lastIdle=NULL;

void updateCommunityWay(){
    if(lastIdle){
        delete lastIdle;
    }
    lastIdle=idle;
    idle=new std::vector<int>();

    //���������������
    idle->clear();
    //��Ϊ������255�����ڣ��������μ��������Ƿ����
    //����ܴ�ĳһ���ڣ���򿪴��ڲ��ɹ��������ص��� ERROR_ACCESS_DENIED������Ϣ��
    //����Ϊ���ڴ��ڣ�ֻ�������߱��������Ѿ���ռ��,���򴮿ڲ�����
    //���255��̫��ʱ��,����ǰ30���ļ��ʽϴ�
    for(int i=1; i<30; i++){
        //����ԭʼ�豸��
        CString sPort;
        sPort.Format(_T("\\\\.\\COM%d"),i);

        HANDLE hPort=::CreateFile(sPort,GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,0,0);
        if(hPort!=INVALID_HANDLE_VALUE){
            idle->push_back(i);
            CloseHandle(hPort);
        }
    }

    //UI:��Ͽ� ����
    cmbWay->ResetContent();
    if(idle->size()==0){
        MyLog::user("δ���ֿ��еĴ���");
        return;
    } else{
        MyLog::user("����%d������",idle->size());
        for(int i=0;i<idle->size();i++){
            CString name;
            name.Format(_T("COM%d"),(*idle)[i]);
            cmbWay->InsertString(i,name);
        }
    }
    //��USB��֧��
    cmbWay->InsertString(0,_T("USB"));
}


void autoConnect(){
    int id=comm.getConnectId();
    //�Զ�����ֻ��δ����״̬��Ч
    if(id==0){
        if(idle->size()==lastIdle->size()+1){ //Ӧ�û�����һ�������豸
            std::vector<int> diff;
            std::set_difference(
                idle->begin(),idle->end(),
                lastIdle->begin(),lastIdle->end(),
                std::inserter(diff,diff.begin())
            );//��idle-lastIdle
            if(diff.size()==1){ //�Ӧ��ֻ��һ��Ԫ��
                int needConnectId=diff[0];
                for(int i=0;i<idle->size();i++){
                    if((*idle)[i]==needConnectId){
                        cmbWay->SetCurSel(i);
                        bool ret=comm.connect(needConnectId,getInt(cmbBaud));
                        if(ret){
                            setText(btnConnect,"�Ͽ�����");
                            MainDialogCtrlValidity::AfterConnect();
                        } else{
                            MainDialogCtrlValidity::BeforeConnect();
                        }
                    }
                }
            } else{
                MyLog::error("����Bug,��ǰ���ڴ���δ����״̬,����һ�δ���ö��,����idle��lastIdle�ĲԪ�ظ�������һ��,��ϸ��Ϣ:");
                {
                    MyString error="diff:";
                    for(std::vector<int>::iterator it=diff.begin();it!=diff.end();it++){
                        char number[20];
                        sprintf(number," %d",*it);
                        error+=number;
                    }
                    MyLog::error(error);
                }
            }
        } else{
            //�����쳣���
            MyLog::error("����Bug,��ǰ���ڴ���δ����״̬,����һ�δ���ö��,����idle������lastIdle��,��ϸ��Ϣ:");
            {
                MyString error="idle:";
                for(std::vector<int>::iterator it=idle->begin();it!=idle->end();it++){
                    char number[20];
                    sprintf(number," %d",*it);
                    error+=number;
                }
                MyLog::error(error);
            }
            {
                MyString error="lastIdle:";
                for(std::vector<int>::iterator it=lastIdle->begin();it!=lastIdle->end();it++){
                    char number[20];
                    sprintf(number," %d",*it);
                    error+=number;
                }
                MyLog::error(error);
            }
        }
    }
}

void autoDisconnect(){
    int id=comm.getConnectId();
    //�Զ��Ͽ���������״̬��
    if(id!=0){
        bool needDisconnect=true;
        for(int i=0;i<idle->size();i++){
            if((*idle)[i]==id){
                needDisconnect=false;
            }
        }
        if(needDisconnect){
            comm.disconnect();
            MainDialogCtrlValidity::BeforeConnect();
            btnConnect->SetWindowText(_T("������λ��"));
        }
    }
}
