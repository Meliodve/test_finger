#pragma once
#include "stdafx.h"

// �ؼ�ָ��Ⱥ
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
CButton* btnDeleteTemplate;
CStatic* image;
CProgressCtrl* progress;

HWND hwnd;

AdvancedDebugDialog* advancedDebugDialog;

// ��ʼ��MainDialog�Ŀؼ�ָ��,�Լ���ʼ��һЩ�ؼ�����
void initMainControl(MainDialog* Dlg){
    progress=(CProgressCtrl*)Dlg->GetDlgItem(IDC_PROGRESS);

    //����������
    progress->SetRange(0,100);
    setProgress(10);

    // �ؼ�ָ��Ⱥ��ʼ��
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
    btnDeleteTemplate=(CButton*)Dlg->GetDlgItem(IDC_BTNDeleteTemplate);
    image=(CStatic*)Dlg->GetDlgItem(IDC_IMAGE);
    hwnd=Dlg->m_hWnd;

    (new MyThread(
        [&](){
            MyString last="";
            while(1){
                MyString log=MyLog::MsgQueue.pop();
                MyString WithTime=log.Format<const char*>(
                    MyString::Time("%Y-%m-%d %H:%M:%S"));
                if(last!=log){
                    int len=editLog->GetWindowTextLength();
                    MyString old_content=getText(editNow);
                    editLog->SetSel(len,len,0);
                    editLog->ReplaceSel(old_content+"\r");
                    MyLog::appendLog(old_content+"\n");
                }
                if(getText(editNow)!=WithTime){
                    setText(editNow,WithTime);
                }
            }
        }
    ,true))->start();

    setProgress(20);

    //���ؼ�����Ȩ��
    MainDialogCtrlValidity::InitCtrl();

    setProgress(30);

    // ������־��
    editLog->SetLimitText(-1);
    setText(editNow,MyString::Format("�Զ������Ƿ���:%s\r\n",conf["AutoCheck"].c_str()));

    // ���ø߼����԰�ť�ɼ���
    if(conf["AdvDbg"]==Stringify(true)){
        btnAdvDbg->ShowWindow(SW_SHOW);
    }
    advancedDebugDialog=0;

    setProgress(40);

    //���ò�����
    MyString baud[]={"9600","19200","57600","115200","230400","460800","921600"};
    for(int i=0;i<sizeof(baud)/sizeof(baud[0]);i++){
        cmbBaud->InsertString(i,baud[i]);
    }
    cmbBaud->SetCurSel(MyString::ParseInt(conf["Baud"]));

    setProgress(50);

    //оƬ����
    MyString chipType[]={GD32,SYNO};
    for(int i=0;i<sizeof(chipType)/sizeof(chipType[0]);i++){
        cmbProtocolType->InsertString(i,chipType[i]);
    }
    //max��Ϊ������֮��,������ǰ���ڵ���2�����
    cmbProtocolType->SetCurSel(max(1,MyString::ParseInt(conf["ProtocolType"])));

    setProgress(60);

    //��־��Ϣ�ȼ�
    MyString logLevel[]={"�û�","����","����","����","��ʱ"};
    for(int i=0;i<sizeof(logLevel)/sizeof(logLevel[0]);i++){
        cmbLogLevel->InsertString(i,logLevel[i]);
    }
    cmbLogLevel->SetCurSel(3);

    setProgress(70);

    //���ñ���
    int BigVersion=Version/100;
    int SmlVersion=Version%100;
    if(SmlVersion%10==0){
        SmlVersion/=10;
    }
    setText(Dlg,getText(Dlg)+MyString::Format(" Ver%d.%d",BigVersion,SmlVersion));

    setProgress(80);

    //ˢ��ͨ�ŷ�ʽ
    updateCommunityWay();

    setProgress(90);

    //�Զ�������
    if(conf["AutoCheck"]==Stringify(true)){
        if(isConnectedNet()){
            if(NetGetVersion()>Version){
                MyLog::user("�пɸ��°汾,�������и���.");
            }
        }
    }

    setProgress(100);
    MyLog::user("��ʼ�����");
    MainDialogCtrlValidity::Init();
}

// ��MainDialog����Ϣ������������Ϣ
void sendMainDialogMessage(int Message){
    if(test.isTest(test.UI)){
        return;
    }
    SendMessage(hwnd,Message,Message,0);
}

// ���ڴ�ŵ�ǰ�������
std::vector<int>* idle=new std::vector<int>();
// ���ڴ��֮ǰ�Ĵ������,����ʵ�ּ򵥵��Զ�����
std::vector<int>* lastIdle=NULL;

// ���ͨ�ŷ�ʽ��ѡ���Com��,USB����=0,���ڷ���>0
int getComID(){
    if(!cmbWay->GetCurSel()){
        return 0;
    }
    return (*idle)[idle->size()-cmbWay->GetCurSel()];
}

void setProgress(int percent){
    if(test.isTest(test.UI)){
        test.uiTest.UI_progress=percent;
        return;
    }
    if(percent<0){
        progress->SetPos(0);
    } else if(percent>100){
        progress->SetPos(100);
    } else{
        progress->SetPos(percent);
    }
}

void setProgress(double percent){
    setProgress((int)percent);
}

#pragma region ö�ٴ��ڵĸ��Ӵ���

#include <initguid.h>
// ���¶�������DDK�е�<ntddser.h>,���ж˿�ö��Ҳ��Ҫ��
#ifndef GUID_CLASS_COMPORT
DEFINE_GUID(GUID_CLASS_COMPORT,0x86e0d1e0L,0x8089,0x11d0,0x9c,0xe4,0x08,0x00,0x3e,0x30,0x1f,0x73);
#endif
BOOL EnumPortsWdm(){
    cmbWay->ResetContent();

    GUID *guidDev=(GUID*)&GUID_CLASS_COMPORT;
    HDEVINFO hDevInfo=SetupDiGetClassDevs(guidDev,NULL,NULL,DIGCF_DEVICEINTERFACE);
    if(INVALID_HANDLE_VALUE==hDevInfo){
        return FALSE;
    }
    BOOL returnVal=TRUE;
    SP_DEVICE_INTERFACE_DATA ifcData;
    const int dwDetDataSize=1024;
    char __pDetData[dwDetDataSize];
    SP_DEVICE_INTERFACE_DETAIL_DATA* pDetData=(SP_DEVICE_INTERFACE_DETAIL_DATA*)__pDetData;
    ifcData.cbSize=sizeof(SP_DEVICE_INTERFACE_DATA);
    pDetData->cbSize=sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
    for(int i=0;;i++){
        if(!SetupDiEnumDeviceInterfaces(hDevInfo,NULL,guidDev,i,&ifcData)){
            returnVal=FALSE;
            break;
        }
        SP_DEVINFO_DATA devdata={sizeof(SP_DEVINFO_DATA)};
        if(!SetupDiGetDeviceInterfaceDetail(hDevInfo,&ifcData,pDetData,dwDetDataSize,NULL,&devdata)){
            returnVal=FALSE;
            break;
        }
        WCHAR fname[256]={0};
        if(!SetupDiGetDeviceRegistryProperty(
            hDevInfo,&devdata,SPDRP_FRIENDLYNAME,NULL,(PBYTE)fname,sizeof(fname),NULL)){
            //�޷���ô��豸�Ѻ�����
        }
        MyString friendlyName=fname;
        const char* str=friendlyName;
        for(str=str+strlen(str);*str!='(';str--);
        int COM=0;
        sscanf_s(str,"(COM%d)",&COM);

        HANDLE hPort=::CreateFile(MyString::Format("\\\\.\\COM%d",COM),
            GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,0,0);
        if(hPort!=INVALID_HANDLE_VALUE){
            idle->push_back(COM);
            CloseHandle(hPort);
            cmbWay->InsertString(0,friendlyName);
        }
    }
    if(hDevInfo!=INVALID_HANDLE_VALUE){
        SetupDiDestroyDeviceInfoList(hDevInfo);
    }
    MyLog::user("����%d������",idle->size());
    return returnVal;
}

#pragma endregion

// ����ͨ�ŷ�ʽ��Ͽ�
void updateCommunityWay(){
    if(lastIdle){
        delete lastIdle;
    }
    lastIdle=idle;
    idle=new std::vector<int>();

    //���������������
    idle->clear();
#define FastEnum
    //ԭ��������ʾ���ֵ�ö�ٷ�ʽ,����û��,���ǲ���ǿ:
#ifndef FastEnum
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
#else
    EnumPortsWdm();
#endif
#undef FastEnum
    //��USB��֧��
    cmbWay->InsertString(0,_T("USB"));
}

// �����Զ�����
void autoConnect(){
    int id=comm.getConnectId();
    //�Զ�����ֻ��δ����״̬��Ч
    if(id>0){
        if(idle->size()==lastIdle->size()+1){ //Ӧ�û�����һ�������豸
            std::vector<int> diff;
            std::sort(idle->begin(),idle->end());
            std::sort(lastIdle->begin(),lastIdle->end());
            std::set_difference(
                idle->begin(),idle->end(),
                lastIdle->begin(),lastIdle->end(),
                std::inserter(diff,diff.begin())
            );//��idle-lastIdle
            if(diff.size()==1){ //�Ӧ��ֻ��һ��Ԫ��
                int needConnectId=diff[0];
                for(uint i=0;i<idle->size();i++){
                    if((*idle)[i]==needConnectId){
                        cmbWay->SetCurSel(i+1);
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
                        error+=MyString::IntToMyString(*it);
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
                    error+=MyString::IntToMyString(*it);
                }
                MyLog::error(error);
            }
            {
                MyString error="lastIdle:";
                for(std::vector<int>::iterator it=lastIdle->begin();it!=lastIdle->end();it++){
                    error+=MyString::IntToMyString(*it);
                }
                MyLog::error(error);
            }
        }
    }
}

// �Զ��Ͽ�����
void autoDisconnect(){
    int id=comm.getConnectId();
    //�Զ��Ͽ���������״̬��
    if(id>0){
        bool needDisconnect=true;
        for(uint i=0;i<idle->size();i++){
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
