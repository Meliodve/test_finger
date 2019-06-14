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
CButton* btnDeleteTemplate;
CStatic* image;
CProgressCtrl* progress;

HWND hwnd;

AdvancedDebugDialog* advancedDebugDialog;

void initMainControl(MainDialog* Dlg){
    progress=(CProgressCtrl*)Dlg->GetDlgItem(IDC_PROGRESS);

    //����������
    progress->SetRange(0,100);
    progress->SetPos(10);

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

    progress->SetPos(20);

    //���ؼ�����Ȩ��
    MainDialogCtrlValidity::InitCtrl();

    progress->SetPos(30);

    editLog->SetLimitText(-1);
    setText(editNow,MyString::Format("�Զ������Ƿ���:%s\r\n",conf["AutoCheck"].c_str()));
    hwnd=Dlg->m_hWnd;

    if(conf["AdvDbg"]=="true"){
        btnAdvDbg->ShowWindow(SW_SHOW);
    }
    advancedDebugDialog=0;

    progress->SetPos(40);

    //���ò�����
    MyString baud[]={"9600","19200","57600","115200","230400","460800","921600"};
    for(int i=0;i<sizeof(baud)/sizeof(baud[0]);i++){
        cmbBaud->InsertString(i,baud[i]);
    }
    cmbBaud->SetCurSel(MyString::ParseInt(conf["Baud"]));

    progress->SetPos(50);

    //оƬ����
    MyString chipType[]={GD32,SYNO};
    for(int i=0;i<sizeof(chipType)/sizeof(chipType[0]);i++){
        cmbProtocolType->InsertString(i,chipType[i]);
    }
    //max��Ϊ������֮��,������ǰ���ڵ���2�����
    cmbProtocolType->SetCurSel(max(1,MyString::ParseInt(conf["ProtocolType"])));

    progress->SetPos(60);

    //��־��Ϣ�ȼ�
    MyString logLevel[]={"�û�","����","����","����","��ʱ"};
    for(int i=0;i<sizeof(logLevel)/sizeof(logLevel[0]);i++){
        cmbLogLevel->InsertString(i,logLevel[i]);
    }
    cmbLogLevel->SetCurSel(3);

    progress->SetPos(70);

    //���ñ���
    int BigVersion=Version/100;
    int SmlVersion=Version%100;
    if(SmlVersion%10==0){
        SmlVersion/=10;
    }
    setText(Dlg,getText(Dlg)+MyString::Format(" Ver%d.%d",BigVersion,SmlVersion));

    progress->SetPos(80);

    //ˢ��ͨ�ŷ�ʽ
    updateCommunityWay();

    progress->SetPos(90);

    //�Զ�������
    if(conf["AutoCheck"]=="true"){
        if(isConnectedNet()){
            if(NetGetVersion()>Version){
                MyLog::user("�пɸ��°汾,�������и���.");
            }
        }
    }

    progress->SetPos(100);
    MyLog::user("��ʼ�����");
    MainDialogCtrlValidity::Init();

}

void sendMainDialogMessage(int Message){
    SendMessage(hwnd,Message,Message,0);
}

std::vector<int>* idle=new std::vector<int>();
std::vector<int>* lastIdle=NULL;


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
        sscanf(str,"(COM%d)",&COM);

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


void updateCommunityWay(){
    if(lastIdle){
        delete lastIdle;
    }
    lastIdle=idle;
    idle=new std::vector<int>();

    //���������������
    idle->clear();
#define FastEnum
    //ԭ��������ʾ���ֵ�ö�ٷ�ʽ:
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
                for(int i=0;i<idle->size();i++){
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
    if(id>0){
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
