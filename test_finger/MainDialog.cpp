#include "stdafx.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MainDialog::MainDialog(CWnd* pParent /*=NULL*/)
    : CDialogEx(MainDialog::IDD,pParent){
    m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BEGIN_MESSAGE_MAP(MainDialog,CDialogEx)
    ON_WM_PAINT()
    ON_MESSAGE(WM_GET_RAW_IMAGE,serialResponse)
    ON_MESSAGE(WM_GET_CON_IMAGE,serialResponse)
    ON_MESSAGE(WM_STP_GET_IMAGE,serialResponse)
    ON_MESSAGE(WM_READ_REGISTER,serialResponse)
    ON_MESSAGE(WM_APPEND_CONTROLS,serialResponse)
    ON_MESSAGE(WM_GET_TEST_IMAGE,serialResponse)
    ON_MESSAGE(WM_GET_CON_BKI,serialResponse)
    ON_MESSAGE(WM_STP_GET_BKI,serialResponse)
    ON_WM_QUERYDRAGICON()
    ON_WM_DEVICECHANGE()
    ON_BN_CLICKED(IDC_BTNConnect,&MainDialog::OnBnClickedBtnconnect)
    ON_BN_CLICKED(IDC_BTNSaveLog,&MainDialog::OnBnClickedBtnsavelog)
    ON_BN_CLICKED(IDC_BTNRawImage,&MainDialog::OnBnClickedBtnrawimage)
    ON_BN_CLICKED(IDC_BTNContinueImage,&MainDialog::OnBnClickedBtncontinueimage)
    ON_BN_CLICKED(IDC_BTNdevLog,&MainDialog::OnBnClickedBtndevlog)
    ON_BN_CLICKED(IDC_BTNreadReg,&MainDialog::OnBnClickedBtnreadreg)
    ON_BN_CLICKED(IDC_BTNwriteReg,&MainDialog::OnBnClickedBtnwritereg)
    ON_BN_CLICKED(IDC_BTNOpenImage,&MainDialog::OnBnClickedBtnopenimage)
    ON_BN_CLICKED(IDC_BTNContinueBackGroundImage,&MainDialog::OnBnClickedBtncontinuebackgroundimage)
    ON_BN_CLICKED(IDC_BTNOpenBackGroundImage,&MainDialog::OnBnClickedBtnopenbackgroundimage)
    ON_BN_CLICKED(IDC_BTNTestImage,&MainDialog::OnBnClickedBtnbackgroundimage)
    ON_CBN_CLOSEUP(IDC_CMBLogLevel,&MainDialog::OnCbnCloseupCmbloglevel)
    ON_BN_CLICKED(IDC_BTNAdvDbg,&MainDialog::OnBnClickedBtnadvdbg)
    ON_BN_CLICKED(IDC_BTN0,&MainDialog::OnBnClickedBtn)
    ON_BN_CLICKED(IDC_BTN1,&MainDialog::OnBnClickedBtn)
    ON_BN_CLICKED(IDC_BTN2,&MainDialog::OnBnClickedBtn)
    ON_BN_CLICKED(IDC_BTN3,&MainDialog::OnBnClickedBtn)
    ON_BN_CLICKED(IDC_BTN4,&MainDialog::OnBnClickedBtn)
    ON_BN_CLICKED(IDC_BTN5,&MainDialog::OnBnClickedBtn)
    ON_BN_CLICKED(IDC_BTN6,&MainDialog::OnBnClickedBtn)
    ON_BN_CLICKED(IDC_BTN7,&MainDialog::OnBnClickedBtn)
    ON_BN_CLICKED(IDC_BTNEnroll,&MainDialog::OnBnClickedBtnenroll)
    ON_BN_CLICKED(IDC_BTNMatch,&MainDialog::OnBnClickedBtnmatch)
    ON_BN_CLICKED(IDC_BTNDeviceInfo,&MainDialog::OnBnClickedBtndeviceinfo)
    ON_BN_CLICKED(IDC_BTNViewEnrollIds,&MainDialog::OnBnClickedBtnviewenrollids)
    ON_BN_CLICKED(IDC_BTNDeleteTemplate,&MainDialog::OnBnClickedBtndeletetemplate)
    ON_BN_CLICKED(IDC_BTNCancel,&MainDialog::OnBnClickedBtncancel)
    ON_BN_CLICKED(IDC_BTNClearLog,&MainDialog::OnBnClickedBtnclearlog)
    ON_BN_CLICKED(IDC_BTNSetting,&MainDialog::OnBnClickedBtnsetting)
    ON_CBN_SELCHANGE(IDC_CMBBaud,&MainDialog::OnCbnSelchangeCmbbaud)
    ON_CBN_SELCHANGE(IDC_CMBProtocolType,&MainDialog::OnCbnSelchangeCmbprotocoltype)
END_MESSAGE_MAP()

void MainDialog::OnOK(){}

BOOL MainDialog::OnInitDialog(){
    CDialogEx::OnInitDialog();
    SetIcon(m_hIcon,TRUE);
    SetIcon(m_hIcon,FALSE);

    ///1.ȫ�ֿؼ���ֵ
    initMyControl(this);

    ///2.���ñ���
    int BigVersion=Version/100;
    int SmlVersion=Version%100;
    if(SmlVersion%10==0){
        SmlVersion/=10;
    }
    setText(this,getText(this)+MyString::Format("%d.%d",BigVersion,SmlVersion));

    ///3.���ؼ�����Ȩ��
    CtrlValidity::InitCtrl();
    CtrlValidity::Init();

    ///4.ˢ��ͨ�ŷ�ʽ
    updateCommunityWay();

    ///5.�Զ�������
    if(conf["AutoCheck"]=="true"){
        if(isConnectedNet()){
            if(NetGetVersion()>Version){
                MyLog::user("�пɸ��°汾,�������и���.");
            }
        }
    }


    return TRUE;//���ǽ��������õ��ؼ������򷵻� TRUE
}

void MainDialog::OnPaint(){
    if(IsIconic()){
        CPaintDC dc(this);
        SendMessage(WM_ICONERASEBKGND,reinterpret_cast<WPARAM>(dc.GetSafeHdc()),0);
        int cxIcon=GetSystemMetrics(SM_CXICON);
        int cyIcon=GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x=(rect.Width()-cxIcon+1)/2;
        int y=(rect.Height()-cyIcon+1)/2;
        dc.DrawIcon(x,y,m_hIcon);
    } else{
        CDialogEx::OnPaint();
    }
}

HCURSOR MainDialog::OnQueryDragIcon(){
    return static_cast<HCURSOR>(m_hIcon);
}

//֧�ִ����Ȱβ���豸���ļ�������
BOOL MainDialog::OnDeviceChange(UINT nEventType,DWORD dwData){
    switch(nEventType){
    case DBT_DEVICEREMOVECOMPLETE://�Ƴ��豸
        updateCommunityWay();
        autoDisconnect();
        break;
    case DBT_DEVICEARRIVAL://����豸
        updateCommunityWay();
        autoConnect();
        break;
    }
    return TRUE;
}

//������λ����ť�ĵ���¼�
void MainDialog::OnBnClickedBtnconnect(){
    //���ݰ�ť�ϵ������жϵ�ǰ����״̬
    if(getText(btnConnect)=="������λ��"){
        CtrlValidity::Connecting();

        bool ret;
        if(getText(cmbWay)=="USB"){
            ret=comm.connectUSB();
        } else{
            int com,baud=getInt(cmbBaud);//��ȡ������
            sscanf(getText(cmbWay),"COM%d",&com);//��ȡͨ�ŷ�ʽ
            ret=comm.connect(com,baud);
        }
        if(ret){
            setText(btnConnect,"�Ͽ�����");
            CtrlValidity::AfterConnect();
        } else{
            CtrlValidity::BeforeConnect();
        }
    } else{
        comm.disconnect();
        CtrlValidity::BeforeConnect();
        setText(btnConnect,"������λ��");
    }
}

//��־���水ť����¼�
void MainDialog::OnBnClickedBtnsavelog(){
    //��ȡ�ļ�·����
    LPCTSTR filter=_T("�ı��ļ�(*.txt)|*.txt||");
    CFileDialog dlgFileOpen(0,0,0,0,filter,0);
    if(dlgFileOpen.DoModal()==IDOK){
        MyString path=dlgFileOpen.GetPathName();
        //Add .txt
        if(path.find(".txt",path.length()-4)==-1){
            path=path+".txt";
        }
        //write into file
        FILE* fp=fopen(path,"w");
        fprintf_s(fp,"%s",(const char*)getText(editLog));
        fclose(fp);
    }
}

HANDLE timeoutThread_continueImage_Mutex=CreateMutex(0,0,0);
bool timeoutThread_continueImage;

MyThread ImageTimeout(ThreadFunction__(timeoutFunction)(void){
    Sleep(10*1000);
    WaitForSingleObject(timeoutThread_continueImage_Mutex,-1);
    if(!timeoutThread_continueImage){
        MyLog::user("��ͼ��ʱ");
        CtrlValidity::Work();
    }
    ReleaseMutex(timeoutThread_continueImage_Mutex);
});


MyThread RegisterTimeout(ThreadFunction__(timeoutFunction)(void){
    Sleep(1*1000);
    MyLog::user("���Ĵ�����ʱ");
    CtrlValidity::Work();
});

//ԭʼͼ��ĵ���¼�
void MainDialog::OnBnClickedBtnrawimage(){
    if(getText(cmbProtocolType)=="Syno"){
        MyLog::user("��ʼ��ȡͼ��");
        Flow.clear();
        Flow.push_back(FlowFunction(0)(int& result){
            CtrlValidity::Working();
            comm.request(SII(GetRawImage));
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        });
        Flow.push_back(FlowFunction(1)(int& result){
            if(result==0x00){
                CtrlValidity::Working();
                comm.request(SII(UpImage));
                progress->SetPos(100*++FlowID/Flow.size());
                return false;
            } else{
                FlowID--;
                return true;
            }
        });
        Flow.push_back(FlowFunction(2)(int& result){
            progress->SetPos(100*++FlowID/Flow.size());
            FlowID=0;
            Flow.clear();
            MyLog::user("��ȡͼ�����");
            CtrlValidity::Work();
            return false;
        });
        ExecStart();
        return;
    }
    CtrlValidity::Working();
    comm.request(SII(GetRawImage));
    progress->SetPos(30);
    MyLog::user("�����ָ");
    ImageTimeout.start();
}

//�����߳���Ϣ������
LRESULT MainDialog::serialResponse(WPARAM w,LPARAM l){
    static bool continueImage=false;
    switch(w){
    case WM_GET_CON_IMAGE:
    {
        continueImage=true;
        WaitForSingleObject(timeoutThread_continueImage_Mutex,-1);
        timeoutThread_continueImage=true;
        ReleaseMutex(timeoutThread_continueImage_Mutex);
    }
    case WM_GET_RAW_IMAGE:
    {
        ImageTimeout.terminate();
        if(continueImage){
            comm.request(SII(GetRawImage));
            progress->SetPos(30);
            MyLog::user("�����ָ");
            ImageTimeout.start();
        } else{
            CtrlValidity::Work();
        }
    }break;
    case WM_STP_GET_IMAGE:
    {
        continueImage=false;
        WaitForSingleObject(timeoutThread_continueImage_Mutex,-1);
        timeoutThread_continueImage=false;
        ReleaseMutex(timeoutThread_continueImage_Mutex);
        CtrlValidity::Work();
        ImageTimeout.terminate();
        progress->SetPos(0);
    }break;
    case WM_READ_REGISTER:
    {
        RegisterTimeout.terminate();
        progress->SetPos(100);
    }break;
    case WM_APPEND_CONTROLS:
    {
        advancedDebugDialog->append(MyString::ParseInt(conf["id"]),conf["AdvDbg_ImgId"]);
        conf["AdvDbg_ImgId"]=MyString::IntToMyString(MyString::ParseInt(conf["AdvDbg_ImgId"])+1);
    }break;
    case WM_GET_CON_BKI:
    {
        continueImage=true;
        WaitForSingleObject(timeoutThread_continueImage_Mutex,-1);
        timeoutThread_continueImage=true;
        ReleaseMutex(timeoutThread_continueImage_Mutex);
    }
    case WM_GET_TEST_IMAGE:
    {
        ImageTimeout.terminate();
        if(continueImage){
            comm.request(SII(GetTestImage));
            progress->SetPos(30);
            ImageTimeout.start();
        } else{
            CtrlValidity::Work();
        }
    }break;
    case WM_STP_GET_BKI:
    {
        continueImage=false;
        WaitForSingleObject(timeoutThread_continueImage_Mutex,-1);
        timeoutThread_continueImage=false;
        ReleaseMutex(timeoutThread_continueImage_Mutex);
        CtrlValidity::Work();
        ImageTimeout.terminate();
        progress->SetPos(0);
    }break;
    }
    progress->SetPos(0);
    return 1;
}

//������ȡͼ��ĵ���¼�
void MainDialog::OnBnClickedBtncontinueimage(){
    if(getText(cmbProtocolType)=="Syno"){
        MyLog::user("��ʼ������ȡͼ��");
        Flow.clear();
        Flow.push_back(FlowFunction(0)(int& result){
            CtrlValidity::Working();
            comm.request(SII(GetRawImage));
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        });
        Flow.push_back(FlowFunction(1)(int& result){
            if(result==0x00){
                CtrlValidity::Working();
                comm.request(SII(UpImage));
                progress->SetPos(100*++FlowID/Flow.size());
                return false;
            } else{
                FlowID--;
                return true;
            }
        });
        Flow.push_back(FlowFunction(2)(int& result){
            progress->SetPos(100*++FlowID/Flow.size());
            FlowID=0;
            return true;
        });
        Flow.push_back(FlowFunction(3)(int& result){
            progress->SetPos(100*++FlowID/Flow.size());
            FlowID=0;
            Flow.clear();
            MyLog::user("ֹͣ������ȡͼ��");
            CtrlValidity::Work();
            return false;
        });
        ExecStart();
        return;
    }
    //���ݰ�ť�ϵ������жϵ�ǰ����״̬
    if(getText(btnContinueImage)=="������ȡͼ��"){
        MyLog::user("��ʼ������ȡͼ��");
        CtrlValidity::Working(CtrlValidity::vec{btnContinueImage});
        setText(btnContinueImage,"ֹͣ��ȡͼ��");
        SendMessage(WM_GET_CON_IMAGE,WM_GET_CON_IMAGE,0);
    } else{
        MyLog::user("ֹͣ������ȡͼ��");
        CtrlValidity::Work();
        setText(btnContinueImage,"������ȡͼ��");
        SendMessage(WM_STP_GET_IMAGE,WM_STP_GET_IMAGE,0);
    }
}


void MainDialog::OnBnClickedBtndevlog(){
    MyLog::DevelopLog();
}

void MainDialog::OnBnClickedBtnreadreg(){
    if(getText(cmbProtocolType)=="Syno"){
        progress->SetPos(0);
        MyLog::user("��֧�ֵĲ���");
        return;
    }
    Flow.clear();
    Flow.push_back(FlowFunction(0)(int& result){
        CtrlValidity::Working();
        MyLog::debug("��ʼ���Ĵ���");
        uint8_t address=getHex(editReadRegAddr);
        comm.request(SII(ReadRegister),&address,1);
        progress->SetPos(100*++FlowID/Flow.size());
        return false;
    });
    Flow.push_back(FlowFunction(1)(int& result){
        CtrlValidity::Work();
        progress->SetPos(100*++FlowID/Flow.size());
        FlowID=0;
        Flow.clear();
        return false;
    });
    ExecStart();
}


void MainDialog::OnBnClickedBtnwritereg(){
    if(getText(cmbProtocolType)=="Syno"){
        progress->SetPos(0);
        MyLog::user("��֧�ֵĲ���");
        return;
    }
    CtrlValidity::Working();
    progress->SetPos(50);
    MyLog::debug("��ʼд�Ĵ���");

    uint8_t addrVal[2];
    addrVal[0]=getHex(editWriteRegAddr);
    addrVal[1]=getHex(editWriteRegVal);

    comm.request(SII(WriteRegister),addrVal,2);

    progress->SetPos(100);
    CtrlValidity::Work();
}


void MainDialog::OnBnClickedBtncontinuebackgroundimage(){
    if(getText(cmbProtocolType)=="Syno"){
        progress->SetPos(0);
        MyLog::user("��֧�ֵĲ���");
        return;
    }
    //���ݰ�ť�ϵ������жϵ�ǰ����״̬
    if(getText(btnContinueBackGroundImage)=="������ȡ����"){
        MyLog::user("��ʼ������ȡ����");
        CtrlValidity::Working(CtrlValidity::vec{btnContinueBackGroundImage});
        setText(btnContinueBackGroundImage,"ֹͣ��ȡ����");
        SendMessage(WM_GET_CON_BKI,WM_GET_CON_BKI,0);
    } else{
        MyLog::user("ֹͣ������ȡ����");
        CtrlValidity::Work();
        setText(btnContinueBackGroundImage,"������ȡ����");
        SendMessage(WM_STP_GET_BKI,WM_STP_GET_BKI,0);
    }
}


void MainDialog::OnBnClickedBtnopenimage(){
    if(access("collectedImage",0)){
        MyLog::user("ͼƬ�ļ��в�����,���Ȳ�һ��ͼƬ");
    } else{
        ShellExecuteA(NULL,"explore","collectedImage",NULL,NULL,SW_NORMAL);
    }
}


void MainDialog::OnBnClickedBtnopenbackgroundimage(){
    if(access("collectedBGI",0)){
        MyLog::user("�����ļ��в�����,���Ȳ�һ�ű���");
    } else{
        ShellExecuteA(NULL,"explore","collectedBGI",NULL,NULL,SW_NORMAL);
    }
}


void MainDialog::OnBnClickedBtnbackgroundimage(){
    if(getText(cmbProtocolType)=="Syno"){
        progress->SetPos(0);
        MyLog::user("��֧�ֵĲ���");
        return;
    }
    CtrlValidity::Working();
    progress->SetPos(30);
    MyLog::debug("��ʼ�ɼ�����");
    comm.request(SII(GetTestImage));
    progress->SetPos(60);
}


void MainDialog::OnCbnCloseupCmbloglevel(){
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
                conf["AdvDbg"]="true";
                btnAdvDbg->ShowWindow(SW_SHOW);
            }
        }
    }
}


void MainDialog::OnBnClickedBtnadvdbg(){
    if(advancedDebugDialog){
        delete advancedDebugDialog;
        advancedDebugDialog=0;
    } else{
        advancedDebugDialog=new AdvancedDebugDialog();
        advancedDebugDialog->Create(IDD_ADVANCED_DEBUG_DIALOG,this);
        advancedDebugDialog->ShowWindow(SW_SHOW);
    }
}


void MainDialog::OnBnClickedBtn(){
    setText(editFingerId,getText(GetFocus()));
}


void MainDialog::OnBnClickedBtnenroll(){
    if(getText(editFingerId)==""){
        MyLog::user("��Ų���Ϊ��");
        return;
    }
    static uint8_t FingerID=MyString::ParseInt(getText(editFingerId));
    static uint8_t BufferID;
    BufferID=1;
    static const int EnrollCount=3;
    Flow.clear();
    Flow.push_back(FlowFunction(0)(int& result){
        CtrlValidity::Working();
        comm.request(SII(GetEnrollImage));//��ȡͼ��
        progress->SetPos(100*++FlowID/Flow.size());
        return false;
    });
    Flow.push_back(FlowFunction(1)(int& result){
        if(result==0x00){//ȡ��ͼ��
            MyLog::debug("ȡ��ָ��ͼ��(%d/%d)",BufferID,EnrollCount);
            comm.request(SII(UpImage));//�ϴ�ͼ��
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{//ûȡ��ͼ��
            FlowID--;
            return true;
        }
    });
    Flow.push_back(FlowFunction(2)(int& result){
        if(result==0x00){//�ϴ�ͼ��ɹ�
            comm.request(SII(GenChar),&BufferID,1);//��������
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{//�ϴ�ͼ��ʧ��
            MyLog::debug("�ϴ�ͼ��ʧ��");
            FlowID=11;
            MyLog::user("ע��ʧ��");
            return true;
        }
    });
    Flow.push_back(FlowFunction(3)(int& result){
        if(result==0x00){//���������ɹ�
            FlowID++;
            MyLog::debug("���������ɹ�(%d/%d)",BufferID,EnrollCount);

            uint8_t x[]={BufferID,0,0,0,0x87};
            comm.request(SII(Search),x,sizeof x);//����ָ��
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{//��������ʧ��
            FlowID=0;
            return true;
        }
    });
    Flow.push_back(FlowFunction(4)(int& result){
        if(result==0x09){//û�ѵ�ָ��
            MyLog::debug("�ȴ���ָ�ƿ�");
            comm.request(SII(GetRawImage));//�ȴ�����ָ�ƿ�
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{//�ѵ�ָ��
            MyLog::debug("����ָ��");
            FlowID=11;
            MyLog::user("ע��ʧ��");
            return true;
        }
    });
    Flow.push_back(FlowFunction(5)(int& result){
        if(result==0x02){//ûָ��
            FlowID++;
        } else{//��ָ��
            result=0x09;
            FlowID--;
        }
        return true;
    });
    Flow.push_back(FlowFunction(6)(int& result){
        if(BufferID>=EnrollCount){//�ﵽ¼�����
            FlowID++;
        } else{//û�ﵽ¼�����
            BufferID++;
            FlowID=0;
        }
        return true;
    });
    Flow.push_back(FlowFunction(7)(int& result){
        comm.request(SII(RegModel));//�ϲ�����
        progress->SetPos(100*++FlowID/Flow.size());
        return false;
    });
    Flow.push_back(FlowFunction(8)(int& result){
        if(result==0x00){//�ϲ������ɹ�
            FlowID++;
            MyLog::debug("�ϲ������ɹ�");
        } else{//�ϲ�ʧ��
            FlowID=11;
            MyLog::user("ע��ʧ��");
        }
        return true;
    });
    Flow.push_back(FlowFunction(9)(int& result){
        uint8_t data[]={1,0,FingerID};
        comm.request(SII(StoreChar),data,sizeof data);//�洢ģ��
        progress->SetPos(100*++FlowID/Flow.size());
        return false;
    });
    Flow.push_back(FlowFunction(10)(int& result){
        if(result==0x00){//�洢ģ��ɹ�
            FlowID++;
            MyLog::debug("�洢ģ��ɹ�");
        } else{//�洢ʧ��
            FlowID=11;
            MyLog::user("ע��ʧ��");
        }
        return true;
    });
    Flow.push_back(FlowFunction(11)(int& result){//ע�����
        progress->SetPos(100*++FlowID/Flow.size());
        FlowID=0;
        BufferID=1;
        MyLog::user("ע�����");
        Flow.clear();
        CtrlValidity::Work();
        return false;
    });
    ExecStart();
}


void MainDialog::OnBnClickedBtnmatch(){
    if(getText(editFingerId)==""){
        MyLog::user("��Ų���Ϊ��");
        return;
    }
    static uint8_t FingerID=MyString::ParseInt(getText(editFingerId));
    Flow.clear();
    Flow.push_back(FlowFunction(0)(int& result){
        CtrlValidity::Working();
        uint8_t data[]={02,00,FingerID};
        comm.request(SII(LoadChar),data,sizeof data);
        FlowID++;
        MyLog::user("����ָ��ģ����...");
        return false;
    });
    Flow.push_back(FlowFunction(1)(int& result){
        if(result==0x00){
            comm.request(SII(GetRawImage));
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{
            FlowID=5;
            return true;
        }
    });
    Flow.push_back(FlowFunction(2)(int& result){
        if(result==0x00){
            MyLog::user("ȡָ��ͼ�ɹ�");
            uint8_t data[]={02};
            comm.request(SII(GenChar),data,sizeof data);
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{
            result=0x00;
            FlowID--;
            return true;
        }
    });
    Flow.push_back(FlowFunction(3)(int& result){
        if(result==0x00){
            MyLog::user("ָ�����������ɹ�");
            comm.request(SII(Match));
            progress->SetPos(100*++FlowID/Flow.size());
            return false;
        } else{
            MyLog::user("ָ����������ʧ��");
            result=0x00;
            FlowID--;//��������
            FlowID--;//��������
            return true;
        }
    });
    Flow.push_back(FlowFunction(4)(int& result){
        if(result==0x00){
            MyLog::user("ָ��ƥ��ɹ�");
            FlowID++;
            return true;
        } else{
            MyLog::user("ָ�Ʋ�ƥ��");
            FlowID++;
            return true;
        }
    });
    Flow.push_back(FlowFunction(5)(int& result){
        progress->SetPos(100*++FlowID/Flow.size());
        CtrlValidity::Work();
        MyLog::user("�ȶԽ���");
        FlowID=0;
        Flow.clear();
        return false;
    });
    ExecStart();
}


void MainDialog::OnBnClickedBtndeviceinfo(){
    Flow.clear();
    Flow.push_back(FlowFunction(0)(int& result){
        CtrlValidity::Working();
        comm.request(SII(DeviceInfo));
        progress->SetPos(100*++FlowID/Flow.size());
        return false;
    });
    Flow.push_back(FlowFunction(1)(int& result){
        progress->SetPos(100*++FlowID/Flow.size());
        CtrlValidity::Work();
        MyLog::user("��ȡ�豸��Ϣ����");
        FlowID=0;
        Flow.clear();
        return false;
    });
    ExecStart();
}


void MainDialog::OnBnClickedBtnviewenrollids(){
    Flow.clear();
    Flow.push_back(FlowFunction(0)(int& result){
        CtrlValidity::Working();
        uint8_t data[]={0};
        comm.request(SII(ReadIndexTable),data,sizeof data);
        progress->SetPos(100*++FlowID/Flow.size());
        return false;
    });
    Flow.push_back(FlowFunction(1)(int& result){
        progress->SetPos(100*++FlowID/Flow.size());
        CtrlValidity::Work();
        FlowID=0;
        Flow.clear();
        return false;
    });
    ExecStart();
}


void MainDialog::OnBnClickedBtndeletetemplate(){
    if(getText(editFingerId)==""){
        MyLog::user("��Ų���Ϊ��");
        return;
    }
    static uint8_t FingerID=MyString::ParseInt(getText(editFingerId));
    Flow.clear();
    Flow.push_back(FlowFunction(0)(int& result){
        CtrlValidity::Working();
        uint8_t data[]={0,FingerID,0,1};
        comm.request(SII(DeleteChar),data,sizeof data);
        progress->SetPos(100*++FlowID/Flow.size());
        return false;
    });
    Flow.push_back(FlowFunction(1)(int& result){
        if(result==0x00){
            MyLog::user("ɾ��ָ��%d�ɹ�",FingerID);
        }
        progress->SetPos(100*++FlowID/Flow.size());
        CtrlValidity::Work();
        FlowID=0;
        Flow.clear();
        return false;
    });
    ExecStart();
}


void MainDialog::OnBnClickedBtncancel(){
    progress->SetPos(0);
    ExecEnd();
    MyLog::user("ȡ���˲���");
    CtrlValidity::Work();
    if(lastCmdCode.size()){
        lastCmdCode.pop();
    }
}


void MainDialog::OnBnClickedBtnclearlog(){
    MyLog::ClearLog();
}


void MainDialog::OnBnClickedBtnsetting(){
    static SettingDialog* dialog;
    if(dialog){
        delete dialog;
    }
    dialog=new SettingDialog();
    dialog->Create(IDD_SETTING_DIALOG,this);
    dialog->ShowWindow(SW_SHOW);
}


void MainDialog::OnCbnSelchangeCmbbaud(){
    conf["Baud"]=MyString::Format("%d",cmbBaud->GetCurSel());
}


void MainDialog::OnCbnSelchangeCmbprotocoltype(){
    conf["ProtocolType"]=MyString::Format("%d",cmbProtocolType->GetCurSel());
}
