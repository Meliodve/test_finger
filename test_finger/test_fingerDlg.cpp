#include "stdafx.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND hwnd;
// Ctest_fingerDlg �Ի���

Ctest_fingerDlg::Ctest_fingerDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(Ctest_fingerDlg::IDD,pParent){
    m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctest_fingerDlg::DoDataExchange(CDataExchange* pDX){
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctest_fingerDlg,CDialogEx)
    ON_WM_PAINT()
    ON_MESSAGE(WM_GET_RAW_IMAGE,serialResponse)
    ON_MESSAGE(WM_GET_CON_IMAGE,serialResponse)
    ON_MESSAGE(WM_STP_GET_IMAGE,serialResponse)
    ON_MESSAGE(WM_READ_REGISTER,serialResponse)
    ON_MESSAGE(WM_WRITE_REGISTER,serialResponse)
    ON_MESSAGE(WM_GET_TEST_IMAGE,serialResponse)
    ON_MESSAGE(WM_GET_CON_BKI,serialResponse)
    ON_MESSAGE(WM_STP_GET_BKI,serialResponse)
    ON_WM_QUERYDRAGICON()
    ON_WM_DEVICECHANGE()
    ON_BN_CLICKED(IDC_BTNConnect,&Ctest_fingerDlg::OnBnClickedBtnconnect)
    ON_BN_CLICKED(IDC_BTNSaveLog,&Ctest_fingerDlg::OnBnClickedBtnsavelog)
    ON_BN_CLICKED(IDC_BTNRawImage,&Ctest_fingerDlg::OnBnClickedBtnrawimage)
    ON_BN_CLICKED(IDC_BTNContinueImage,&Ctest_fingerDlg::OnBnClickedBtncontinueimage)
    ON_BN_CLICKED(IDC_BTNdevLog,&Ctest_fingerDlg::OnBnClickedBtndevlog)
    ON_BN_CLICKED(IDC_BTNreadReg,&Ctest_fingerDlg::OnBnClickedBtnreadreg)
    ON_BN_CLICKED(IDC_BTNwriteReg,&Ctest_fingerDlg::OnBnClickedBtnwritereg)
    ON_BN_CLICKED(IDC_BTNSetCmos,&Ctest_fingerDlg::OnBnClickedBtnsetcmos)
    ON_BN_CLICKED(IDC_BTNSetBaud,&Ctest_fingerDlg::OnBnClickedBtnsetbaud)
    ON_BN_CLICKED(IDC_BTNSetPassword,&Ctest_fingerDlg::OnBnClickedBtnsetpassword)
    ON_BN_CLICKED(IDC_BTNSetAddress,&Ctest_fingerDlg::OnBnClickedBtnsetaddress)
    ON_BN_CLICKED(IDC_BTNOpenImage,&Ctest_fingerDlg::OnBnClickedBtnopenimage)
    ON_BN_CLICKED(IDC_BTNContinueBackGroundImage,&Ctest_fingerDlg::OnBnClickedBtncontinuebackgroundimage)
    ON_BN_CLICKED(IDC_BTNOpenBackGroundImage,&Ctest_fingerDlg::OnBnClickedBtnopenbackgroundimage)
    ON_BN_CLICKED(IDC_BTNTestImage,&Ctest_fingerDlg::OnBnClickedBtnbackgroundimage)
END_MESSAGE_MAP()


// Ctest_fingerDlg ��Ϣ�������

BOOL Ctest_fingerDlg::OnInitDialog(){
    CDialogEx::OnInitDialog();

    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon,TRUE);// ���ô�ͼ��
    SetIcon(m_hIcon,FALSE);// ����Сͼ��

    // TODO: �ڴ���Ӷ���ĳ�ʼ������

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

    ///4.�߳̾������
    serialThread=0;

    ///5.����������
    progress->SetRange(0,100);
    progress->SetPos(0);

    hwnd=m_hWnd;

    ///0.����

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//�����Ի��������С����ť������Ҫ����Ĵ���
//�����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//�⽫�ɿ���Զ���ɡ�
void Ctest_fingerDlg::OnPaint(){
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR Ctest_fingerDlg::OnQueryDragIcon(){
    return static_cast<HCURSOR>(m_hIcon);
}

//֧�ִ����Ȱβ���豸���ļ�������
BOOL Ctest_fingerDlg::OnDeviceChange(UINT nEventType,DWORD dwData){
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
void Ctest_fingerDlg::OnBnClickedBtnconnect(){
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
void Ctest_fingerDlg::OnBnClickedBtnsavelog(){
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
void Ctest_fingerDlg::OnBnClickedBtnrawimage(){
    updateControlDisable(actGetingImage);
    comm.request(CMD_GET_RAW_IMAGE);
    progress->SetPos(30);
    MyLog.print(Log::LOGU,"�����ָ");
    ImageTimeout.start();
}

//�����߳���Ϣ������
LRESULT Ctest_fingerDlg::serialResponse(WPARAM w,LPARAM l){
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
                comm.request(CMD_GET_RAW_IMAGE);//line 289 �غ�
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
        case WM_WRITE_REGISTER:
        {
            progress->SetPos(100);
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
void Ctest_fingerDlg::OnBnClickedBtncontinueimage(){
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


void Ctest_fingerDlg::OnBnClickedBtndevlog(){
    MyLog.DevelopLog();
}

void Ctest_fingerDlg::OnBnClickedBtnreadreg(){
    updateControlDisable(actReadingReg);
    progress->SetPos(30);
    MyLog.print(Log::LOGD,"��ʼ���Ĵ���");

    uint8_t address=getHex(editReadRegAddr);

    comm.request(CMD_READ_NOTE_BOOK,&address,1);

    progress->SetPos(60);
    RegisterTimeout.start();
}


void Ctest_fingerDlg::OnBnClickedBtnwritereg(){
    updateControlDisable(actWritingReg);
    progress->SetPos(50);
    MyLog.print(Log::LOGD,"��ʼд�Ĵ���");

    uint8_t addrVal[2];
    addrVal[0]=getHex(editWriteRegAddr);
    addrVal[1]=getHex(editWriteRegVal);

    comm.request(CMD_WRITE_NOTE_BOOK,addrVal,2);
    SendMessage(WM_WRITE_REGISTER,WM_WRITE_REGISTER,0);

    progress->SetPos(100);
    updateControlDisable(actWritedReg);
}


void Ctest_fingerDlg::OnBnClickedBtnsetcmos(){
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


void Ctest_fingerDlg::OnBnClickedBtnsetbaud(){
    MyLog.print(Log::LOGU,MyString("���ô���ͨ������Ϊ")+getText(cmbBaudSet));
    progress->SetPos(100);
}


void Ctest_fingerDlg::OnBnClickedBtnsetpassword(){
    MyLog.print(Log::LOGU,MyString("���ô���ͨ������Ϊ")+getText(editPasswordSet));
    progress->SetPos(100);
}


void Ctest_fingerDlg::OnBnClickedBtnsetaddress(){
    MyLog.print(Log::LOGU,MyString("���ô���ͨ�ŵ�ַΪ")+getText(editAddressSet));
    progress->SetPos(100);
}


void Ctest_fingerDlg::OnBnClickedBtncontinuebackgroundimage(){
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


void Ctest_fingerDlg::OnBnClickedBtnopenimage(){
    if(access("collectedImage",0)){
        MyLog.print(Log::LOGU,"ͼƬ�ļ��в�����,���Ȳ�һ��ͼƬ");
    } else{
        ShellExecuteA(NULL,"explore","collectedImage",NULL,NULL,SW_NORMAL);
    }
}


void Ctest_fingerDlg::OnBnClickedBtnopenbackgroundimage(){
    if(access("collectedBGI",0)){
        MyLog.print(Log::LOGU,"�����ļ��в�����,���Ȳ�һ�ű���");
    } else{
        ShellExecuteA(NULL,"explore","collectedBGI",NULL,NULL,SW_NORMAL);
    }
}


void Ctest_fingerDlg::OnBnClickedBtnbackgroundimage(){
    updateControlDisable(actGetingImage);
    progress->SetPos(30);
    MyLog.print(Log::LOGD,"��ʼ�ɼ�����");
    comm.request(CMD_GET_TEST_IMAGE);
    progress->SetPos(60);
}
