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
    ON_BN_CLICKED(IDC_BTNSetCmos,&MainDialog::OnBnClickedBtnsetcmos)
    ON_BN_CLICKED(IDC_BTNSetBaud,&MainDialog::OnBnClickedBtnsetbaud)
    ON_BN_CLICKED(IDC_BTNSetPassword,&MainDialog::OnBnClickedBtnsetpassword)
    ON_BN_CLICKED(IDC_BTNSetAddress,&MainDialog::OnBnClickedBtnsetaddress)
    ON_BN_CLICKED(IDC_BTNOpenImage,&MainDialog::OnBnClickedBtnopenimage)
    ON_BN_CLICKED(IDC_BTNContinueBackGroundImage,&MainDialog::OnBnClickedBtncontinuebackgroundimage)
    ON_BN_CLICKED(IDC_BTNOpenBackGroundImage,&MainDialog::OnBnClickedBtnopenbackgroundimage)
    ON_BN_CLICKED(IDC_BTNTestImage,&MainDialog::OnBnClickedBtnbackgroundimage)
    ON_CBN_CLOSEUP(IDC_CMBLogLevel,&MainDialog::OnCbnCloseupCmbloglevel)
    ON_BN_CLICKED(IDC_BTNAdvDbg,&MainDialog::OnBnClickedBtnadvdbg)
END_MESSAGE_MAP()

void MainDialog::OnOK(){}

BOOL MainDialog::OnInitDialog(){
    CDialogEx::OnInitDialog();
    SetIcon(m_hIcon,TRUE);
    SetIcon(m_hIcon,FALSE);

    ///1.ȫ�ֿؼ���ֵ
    initMyControl(this);

    ///2.����Ͽ�ĳ�ʼ��
    updateCommunityWay();

    ////ͨѶ��ʽ
    //const WCHAR* way[]={0};
    //for(int i=0;way[i];i++){
    //    cmbWay->InsertString(i,way[i]);
    //}

    //���ò�����
    MyString baud[]={"9600","115200","256000"};
    for(int i=0;i<3;i++){
        cmbBaud->InsertString(i,baud[i]);
        cmbBaudSet->InsertString(i,baud[i]);
    }
    cmbBaud->SetCurSel(1);

    ////оƬ����
    //const WCHAR* chipType[]={_T("Ĭ��"),_T("��о"),0};
    //for(int i=0;chipType[i];i++){
    //    cmbChipType->InsertString(i,chipType[i]);
    //}
    //cmbChipType->SetCurSel(0);

    //��־��Ϣ�ȼ�
    MyString logLevel[]={"�û�","����","����","����","��ʱ"};
    for(int i=0;i<5;i++){
        cmbLogLevel->InsertString(i,logLevel[i]);
    }
    cmbLogLevel->SetCurSel(3);

    ///3.���� ���ؼ�����Ȩ��
    updateControlDisable(actInit);

    ///5.����������
    progress->SetRange(0,100);
    progress->SetPos(0);

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
        updateControlDisable(actOpeningPort);

        int com,baud=getInt(cmbBaud);//��ȡ������
        sscanf(getText(cmbWay),"COM%d",&com);//��ȡͨ�ŷ�ʽ

        bool ret=comm.connect(com,baud);
        if(ret){
            setText(btnConnect,"�Ͽ�����");
            updateControlDisable(actOpenedPort);
        } else{
            updateControlDisable(actClosedPort);
        }
    } else{
        comm.disconnect();
        updateControlDisable(actClosedPort);
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
        MyLog.print(Log::LOGU,"��ͼ��ʱ");
        updateControlDisable(actGotImage);
    }
    ReleaseMutex(timeoutThread_continueImage_Mutex);
});


MyThread RegisterTimeout(ThreadFunction__(timeoutFunction)(void){
    Sleep(1*1000);
    MyLog.print(Log::LOGU,"���Ĵ�����ʱ");
    updateControlDisable(actReadedReg);
});

//ԭʼͼ��ĵ���¼�
void MainDialog::OnBnClickedBtnrawimage(){
    updateControlDisable(actGetingImage);
    comm.request(CMD_GET_RAW_IMAGE);
    progress->SetPos(30);
    MyLog.print(Log::LOGU,"�����ָ");
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
                comm.request(CMD_GET_RAW_IMAGE);
                progress->SetPos(30);
                MyLog.print(Log::LOGU,"�����ָ");
                ImageTimeout.start();
            } else{
                updateControlDisable(actGotImage);
            }
        }break;
        case WM_STP_GET_IMAGE:
        {
            continueImage=false;
            WaitForSingleObject(timeoutThread_continueImage_Mutex,-1);
            timeoutThread_continueImage=false;
            ReleaseMutex(timeoutThread_continueImage_Mutex);
            updateControlDisable(actGotImage);
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
            advancedDebugDialog->append(MyString::ParseInt($::conf["id"]),$::conf["AdvDbg_ImgId"]);
            $::conf["AdvDbg_ImgId"]=MyString::IntToMyString(MyString::ParseInt($::conf["AdvDbg_ImgId"])+1);
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
                comm.request(CMD_GET_TEST_IMAGE);
                progress->SetPos(30);
                ImageTimeout.start();
            } else{
                updateControlDisable(actGotImage);
            }
        }break;
        case WM_STP_GET_BKI:
        {
            continueImage=false;
            WaitForSingleObject(timeoutThread_continueImage_Mutex,-1);
            timeoutThread_continueImage=false;
            ReleaseMutex(timeoutThread_continueImage_Mutex);
            updateControlDisable(actGotImage);
            ImageTimeout.terminate();
            progress->SetPos(0);
        }break;
    }
    progress->SetPos(0);
    return 1;
}

//������ȡͼ��ĵ���¼�
void MainDialog::OnBnClickedBtncontinueimage(){
    //���ݰ�ť�ϵ������жϵ�ǰ����״̬
    if(getText(btnContinueImage)=="������ȡͼ��"){
        MyLog.print(Log::LOGU,"��ʼ������ȡͼ��");
        updateControlDisable(actGetConImage);
        setText(btnContinueImage,"ֹͣ��ȡͼ��");
        SendMessage(WM_GET_CON_IMAGE,WM_GET_CON_IMAGE,0);
    } else{
        MyLog.print(Log::LOGU,"ֹͣ������ȡͼ��");
        updateControlDisable(actStpGetImage);
        setText(btnContinueImage,"������ȡͼ��");
        SendMessage(WM_STP_GET_IMAGE,WM_STP_GET_IMAGE,0);
    }
}


void MainDialog::OnBnClickedBtndevlog(){
    MyLog.DevelopLog();
}

void MainDialog::OnBnClickedBtnreadreg(){
    updateControlDisable(actReadingReg);
    progress->SetPos(30);
    MyLog.print(Log::LOGD,"��ʼ���Ĵ���");

    uint8_t address=getHex(editReadRegAddr);

    comm.request(CMD_READ_NOTE_BOOK,&address,1);

    progress->SetPos(60);
    RegisterTimeout.start();
}


void MainDialog::OnBnClickedBtnwritereg(){
    updateControlDisable(actWritingReg);
    progress->SetPos(50);
    MyLog.print(Log::LOGD,"��ʼд�Ĵ���");

    uint8_t addrVal[2];
    addrVal[0]=getHex(editWriteRegAddr);
    addrVal[1]=getHex(editWriteRegVal);

    comm.request(CMD_WRITE_NOTE_BOOK,addrVal,2);

    progress->SetPos(100);
    updateControlDisable(actWritedReg);
}


void MainDialog::OnBnClickedBtnsetcmos(){
    MyString a=getText(editLightTime);
    if(a.length())
        a=MyString("�����ع�ʱ��Ϊ")+a;
    MyString b=getText(editSensitivity);
    if(b.length())
        b=MyString("����������Ϊ")+b;
    if(a.length()&&b.length())
        MyLog.print(Log::LOGU,a+b);
    else if(a.length())
        MyLog.print(Log::LOGU,a);
    else if(b.length())
        MyLog.print(Log::LOGU,b);
    else
        MyLog.print(Log::LOGU,"����ʧ��,������Ϊ��");
    progress->SetPos(100);
}


void MainDialog::OnBnClickedBtnsetbaud(){
    MyLog.print(Log::LOGU,MyString("���ô���ͨ������Ϊ")+getText(cmbBaudSet));
    progress->SetPos(100);
}


void MainDialog::OnBnClickedBtnsetpassword(){
    MyLog.print(Log::LOGU,MyString("���ô���ͨ������Ϊ")+getText(editPasswordSet));
    progress->SetPos(100);
}


void MainDialog::OnBnClickedBtnsetaddress(){
    MyLog.print(Log::LOGU,MyString("���ô���ͨ�ŵ�ַΪ")+getText(editAddressSet));
    progress->SetPos(100);
}


void MainDialog::OnBnClickedBtncontinuebackgroundimage(){
    //���ݰ�ť�ϵ������жϵ�ǰ����״̬
    if(getText(btnContinueBackGroundImage)=="������ȡ����"){
        MyLog.print(Log::LOGU,"��ʼ������ȡ����");
        updateControlDisable(actGetConBKI);
        setText(btnContinueBackGroundImage,"ֹͣ��ȡ����");
        SendMessage(WM_GET_CON_BKI,WM_GET_CON_BKI,0);
    } else{
        MyLog.print(Log::LOGU,"ֹͣ������ȡ����");
        updateControlDisable(actStpGetBKI);
        setText(btnContinueBackGroundImage,"������ȡ����");
        SendMessage(WM_STP_GET_BKI,WM_STP_GET_BKI,0);
    }
}


void MainDialog::OnBnClickedBtnopenimage(){
    if(access("collectedImage",0)){
        MyLog.print(Log::LOGU,"ͼƬ�ļ��в�����,���Ȳ�һ��ͼƬ");
    } else{
        ShellExecuteA(NULL,"explore","collectedImage",NULL,NULL,SW_NORMAL);
    }
}


void MainDialog::OnBnClickedBtnopenbackgroundimage(){
    if(access("collectedBGI",0)){
        MyLog.print(Log::LOGU,"�����ļ��в�����,���Ȳ�һ�ű���");
    } else{
        ShellExecuteA(NULL,"explore","collectedBGI",NULL,NULL,SW_NORMAL);
    }
}


void MainDialog::OnBnClickedBtnbackgroundimage(){
    updateControlDisable(actGetingImage);
    progress->SetPos(30);
    MyLog.print(Log::LOGD,"��ʼ�ɼ�����");
    comm.request(CMD_GET_TEST_IMAGE);
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
                $::conf["AdvDbg"]="true";
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
