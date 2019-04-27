#include "stdafx.h"
#include "afxdialogex.h"
#include "test_fingerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




CEdit* editLog;
CEdit* editAddress;
CEdit* editPassword;
CEdit* editAddressSet;
CEdit* editPasswordSet;
CEdit* editLightTime;
CEdit* editSensitivity;
CEdit* editReadRegAddr;
CEdit* editReadRegVal;
CEdit* editWriteRegAddr;
CEdit* editWriteRegVal;
CComboBox* cmbWay;
CComboBox* cmbBaud;
CComboBox* cmbBaudSet;
CComboBox* cmbChipType;
CComboBox* cmbLogLevel;
CButton* btnConnect;
CButton* btnRawImage;
CButton* btnTestImage;
CButton* btnContinueImage;
CButton* btnContinueBackGroundImage;
CButton* btnSetCmos;
CButton* btnSetBaud;
CButton* btnSetPassword;
CButton* btnSetAddress;
CButton* btnSaveLog;
CButton* btnReadReg;
CButton* btnWriteReg;
CButton* chkTimeoutContinue;
CStatic* textDevice;
CStatic* image;
CProgressCtrl* progress;
BYTE packet[65536];
DWORD packetCnt;
BYTE packetData[65536];
DWORD packetDataLen;


// Ctest_fingerDlg �Ի���

Ctest_fingerDlg::Ctest_fingerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctest_fingerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctest_fingerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctest_fingerDlg, CDialogEx)
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
	ON_BN_CLICKED(IDC_BTNConnect, &Ctest_fingerDlg::OnBnClickedBtnconnect)
	ON_BN_CLICKED(IDC_BTNSaveLog, &Ctest_fingerDlg::OnBnClickedBtnsavelog)
	ON_BN_CLICKED(IDC_BTNRawImage, &Ctest_fingerDlg::OnBnClickedBtnrawimage)
	ON_BN_CLICKED(IDC_BTNContinueImage, &Ctest_fingerDlg::OnBnClickedBtncontinueimage)
	ON_BN_CLICKED(IDC_BTNdevLog, &Ctest_fingerDlg::OnBnClickedBtndevlog)
	ON_BN_CLICKED(IDC_BTNreadReg, &Ctest_fingerDlg::OnBnClickedBtnreadreg)
	ON_BN_CLICKED(IDC_BTNwriteReg, &Ctest_fingerDlg::OnBnClickedBtnwritereg)
	ON_BN_CLICKED(IDC_BTNSetCmos, &Ctest_fingerDlg::OnBnClickedBtnsetcmos)
	ON_BN_CLICKED(IDC_BTNSetBaud, &Ctest_fingerDlg::OnBnClickedBtnsetbaud)
	ON_BN_CLICKED(IDC_BTNSetPassword, &Ctest_fingerDlg::OnBnClickedBtnsetpassword)
	ON_BN_CLICKED(IDC_BTNSetAddress, &Ctest_fingerDlg::OnBnClickedBtnsetaddress)
	ON_BN_CLICKED(IDC_BTNOpenImage, &Ctest_fingerDlg::OnBnClickedBtnopenimage)
	ON_BN_CLICKED(IDC_BTNContinueBackGroundImage, &Ctest_fingerDlg::OnBnClickedBtncontinuebackgroundimage)
	ON_BN_CLICKED(IDC_BTNOpenBackGroundImage, &Ctest_fingerDlg::OnBnClickedBtnopenbackgroundimage)
	ON_BN_CLICKED(IDC_BTNTestImage, &Ctest_fingerDlg::OnBnClickedBtnbackgroundimage)
END_MESSAGE_MAP()


// Ctest_fingerDlg ��Ϣ�������

BOOL Ctest_fingerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	///1.ȫ�ֿؼ���ֵ
	editLog			= (CEdit*) GetDlgItem(IDC_EDITLog);
	editAddress		= (CEdit*) GetDlgItem(IDC_EDITAddress);
	editPassword	= (CEdit*) GetDlgItem(IDC_EDITPassword);
	editAddressSet	= (CEdit*) GetDlgItem(IDC_EDITAddressSet);
	editPasswordSet	= (CEdit*) GetDlgItem(IDC_EDITPasswordSet);
	editLightTime	= (CEdit*) GetDlgItem(IDC_EDITLightTime);
	editSensitivity	= (CEdit*) GetDlgItem(IDC_EDITSensitivity);
	editReadRegAddr	= (CEdit*) GetDlgItem(IDC_EDITreadRegAddr);
	editReadRegVal	= (CEdit*) GetDlgItem(IDC_EDITreadRegVal);
	editWriteRegAddr= (CEdit*) GetDlgItem(IDC_EDITwriteRegAddr);
	editWriteRegVal	= (CEdit*) GetDlgItem(IDC_EDITwriteRegVal);
	cmbWay			= (CComboBox*) GetDlgItem(IDC_CMBWay);
	cmbBaud			= (CComboBox*) GetDlgItem(IDC_CMBBaud);
	cmbBaudSet		= (CComboBox*) GetDlgItem(IDC_CMBBaudSet);
	cmbChipType		= (CComboBox*) GetDlgItem(IDC_CMBChipType);
	cmbLogLevel		= (CComboBox*) GetDlgItem(IDC_CMBLogLevel);
	btnConnect		= (CButton*) GetDlgItem(IDC_BTNConnect);
	btnRawImage		= (CButton*) GetDlgItem(IDC_BTNRawImage);
	btnTestImage	= (CButton*) GetDlgItem(IDC_BTNTestImage);
	btnContinueImage= (CButton*) GetDlgItem(IDC_BTNContinueImage);
	btnContinueBackGroundImage=(CButton*) GetDlgItem(IDC_BTNContinueBackGroundImage);
	btnSetCmos		= (CButton*) GetDlgItem(IDC_BTNSetCmos);
	btnSetBaud		= (CButton*) GetDlgItem(IDC_BTNSetBaud);
	btnSetPassword	= (CButton*) GetDlgItem(IDC_BTNSetPassword);
	btnSetAddress	= (CButton*) GetDlgItem(IDC_BTNSetAddress);
	btnSaveLog		= (CButton*) GetDlgItem(IDC_BTNSaveLog);
	btnReadReg		= (CButton*) GetDlgItem(IDC_BTNreadReg);
	btnWriteReg		= (CButton*) GetDlgItem(IDC_BTNwriteReg);
	chkTimeoutContinue=(CButton*) GetDlgItem(IDC_CHKTimeoutContinue);
	textDevice		= (CStatic*) GetDlgItem(IDC_TEXTDevice);
	image			= (CStatic*) GetDlgItem(IDC_IMAGE);
	progress		= (CProgressCtrl*) GetDlgItem(IDC_PROGRESS);

	///2.����Ͽ�ĳ�ʼ��
	updateCommunityWay();
	//ͨѶ��ʽ
	const WCHAR* way[]={_T("USB"),0};
	for(int i=0;way[i];i++){
		cmbWay->InsertString(i,way[i]);
	}
	//���ò�����
	const WCHAR* baud[]={_T("9600"),_T("115200"),_T("256000"),0};
	for(int i=0;baud[i];i++){
		cmbBaud->InsertString(i,baud[i]);
		cmbBaudSet->InsertString(i,baud[i]);
	}
	cmbBaud->SetCurSel(1);
	//оƬ����
	const WCHAR* chipType[]={_T("Ĭ��"),_T("��о"),0};
	for(int i=0;chipType[i];i++){
		cmbChipType->InsertString(i,chipType[i]);
	}
	cmbChipType->SetCurSel(0);
	//��־��Ϣ�ȼ�
	const WCHAR* logLevel[]={_T("�û�"),_T("����"),_T("����"),_T("����"),_T("��ʱ"),0};
	for(int i=0;logLevel[i];i++){
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

	///0.����
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//�����Ի��������С����ť������Ҫ����Ĵ���
//�����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//�⽫�ɿ���Զ���ɡ�
void Ctest_fingerDlg::OnPaint(){
	if(IsIconic()){
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x=(rect.Width()-cxIcon+1)/2;
		int y=(rect.Height()-cyIcon+1)/2;
		dc.DrawIcon(x, y, m_hIcon);
	}else{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR Ctest_fingerDlg::OnQueryDragIcon(){
	return static_cast<HCURSOR>(m_hIcon);
}

//֧�ִ����Ȱβ���豸���ļ�������
BOOL Ctest_fingerDlg::OnDeviceChange(UINT nEventType, DWORD dwData){
	switch(nEventType){
		case DBT_DEVICEREMOVECOMPLETE://�Ƴ��豸
		case DBT_DEVICEARRIVAL://����豸
			updateCommunityWay();
			break;
	}
	return TRUE;
}

//������λ����ť�ĵ���¼�
void Ctest_fingerDlg::OnBnClickedBtnconnect(){
	//���ݰ�ť�ϵ������жϵ�ǰ����״̬
	WCHAR str[64];
	btnConnect->GetWindowTextW(str,512);
	if(lstrcmp(str,_T("������λ��"))==0){
		updateControlDisable(actOpeningPort);

		int com,baud=GetDlgItemInt(IDC_CMBBaud);//��ȡ������
		cmbWay->GetWindowText(str,64);
		swscanf(str,_T("COM%d"),&com);//��ȡͨ�ŷ�ʽ
		
		bool ret=CCommunication::connect(com,baud);
		if(ret){
			btnConnect->SetWindowText(_T("�Ͽ�����"));
			updateControlDisable(actOpenedPort);
			MyLog.print(Log::LOGU,"����COM%d�ɹ�",com);
		}else{
			updateControlDisable(actClosedPort);
			MyLog.print(Log::LOGU,"����COM%dʧ��",com);
		}
	}else{
		CCommunication::disConnect();
		updateControlDisable(actClosedPort);
		MyLog.print(Log::LOGU,"�Ͽ����ӳɹ�");
		btnConnect->SetWindowText(_T("������λ��"));
	}
}

//��־���水ť����¼�
void Ctest_fingerDlg::OnBnClickedBtnsavelog(){
	//��ȡ�ļ�·����
	LPCTSTR filter=_T("�ı��ļ�(*.txt)|*.txt||");
	CFileDialog dlgFileOpen(0,0,0,0,filter,0);
	if(dlgFileOpen.DoModal()==IDOK){
		CString path=dlgFileOpen.GetPathName();
		//get text
		CString logText;
		editLog->GetWindowText(logText);
		//Add .txt ?
		if(path.Find(_T(".txt"),path.GetLength()-4)==-1){
			path=path+_T(".txt");
		}
		//CString->char*
        char* filePath=CString2char(path);
		//write into file
		FILE* fp=fopen(filePath,"w");
		fwprintf_s(fp,_T("%s"),logText);
		fclose(fp);
	}
}

//��ȡԭʼͼ����̺߳���
DWORD WINAPI threadGetRawImage(LPVOID params){
	CCommunication::sendCommand(CMD_GET_RAW_IMAGE);
	progress->SetPos(30);
	MyLog.print(Log::LOGD,"Serial Thread:3����λ����������:CMD_GET_RAW_IMAGE");
	MyLog.print(Log::LOGU,"�����ָ");
	CCommunication::waitForPacket(10*1000);
	progress->SetPos(50);
	MyLog.print(Log::LOGD,"Serial Thread:4���յ����ݰ�,��СΪ%d",packetCnt);
	MyLog.print(Log::LOGD,"Serial Thread:5�߳������̷߳�����ϢWM_GET_RAW_IMAGE");
	SendMessage((HWND)params,WM_GET_RAW_IMAGE,WM_GET_RAW_IMAGE,0);
	return 0;
}

//ԭʼͼ��ĵ���¼�
void Ctest_fingerDlg::OnBnClickedBtnrawimage(){
	updateControlDisable(actGetingImage);
	progress->SetPos(10);
	MyLog.print(Log::LOGD,"Main Thread:1��ʼ�ɼ�ԭʼͼ��");
	serialThread=CreateThread(0,0,threadGetRawImage,this->m_hWnd,0,0);
	progress->SetPos(20);
    MyLog.print(Log::LOGD,"Main Thread:2�ɼ�ͼ���̵߳�ַ:%d",serialThread);
}

//�����߳���Ϣ������
LRESULT Ctest_fingerDlg::serialResponse(WPARAM w,LPARAM l){
	static bool continueImage=false;
	switch(w){
		case WM_GET_RAW_IMAGE:{
			progress->SetPos(75);
			MyLog.print(Log::LOGD,"Main Thread:6��Ϣ�������յ���ϢWM_GET_RAW_IMAGE");
			CCommunication::getDataFromPacket();
			
			if(packetDataLen==0){
				MyLog.print(Log::LOGU,"�������ݳ�ʱ");
				CloseHandle(serialThread);
				serialThread=0;
			}else{
				saveImage(_T("collectedImage"));
				progress->SetPos(100);
				MyLog.print(Log::LOGD,"Main Thread:7����ͼƬ���");
				MyLog.print(Log::LOGU,"�������ݳɹ�");
				CloseHandle(serialThread);
				serialThread=0;
			}
			if(!continueImage){
				updateControlDisable(actGotImage);
				break;
			}
		}//if continueImage then can exec next
		//so no break
		case WM_GET_CON_IMAGE:{
			continueImage=true;
			assert(serialThread==0);
			serialThread=CreateThread(0,0,threadGetRawImage,this->m_hWnd,0,0);
		}break;
		case WM_STP_GET_IMAGE:{
			continueImage=false;
			if(serialThread){
				TerminateThread(serialThread,-1);
				CloseHandle(serialThread);
				serialThread=0;
			}
		}break;
		case WM_READ_REGISTER:{
			CCommunication::getDataFromPacket();
			if(packetDataLen==0){
				MyLog.print(Log::LOGU,"�������ݳ�ʱ");
				CloseHandle(serialThread);
				serialThread=0;
			}else{
				CString tmp;
				tmp.Format(_T("%X"),packetData[0]);
				editReadRegVal->SetWindowText(tmp);
				MyLog.print(Log::LOGU,"�������ݳɹ�");
				CloseHandle(serialThread);
				serialThread=0;
			}
			updateControlDisable(actReadedReg);
		}break;
		case WM_WRITE_REGISTER:{
			MyLog.print(Log::LOGU,"�޸ļĴ�������ͳɹ�");
			CloseHandle(serialThread);
			serialThread=0;
			updateControlDisable(actWritedReg);
		}break;
		case WM_GET_TEST_IMAGE:{
			progress->SetPos(75);
			MyLog.print(Log::LOGD,"Main Thread:4��Ϣ�������յ���ϢWM_GET_TEST_IMAGE");
			CCommunication::getDataFromPacket();
			
			if(packetDataLen==0){
				MyLog.print(Log::LOGU,"���ձ������ݳ�ʱ");
				CloseHandle(serialThread);
				serialThread=0;
			}else{
				saveImage(_T("collectedBGI"));
				progress->SetPos(100);
				MyLog.print(Log::LOGD,"Main Thread:5����ͼƬ���");
				MyLog.print(Log::LOGU,"���ձ������ݳɹ�");
				CloseHandle(serialThread);
				serialThread=0;
			}
			if(!continueImage){
				updateControlDisable(actGotImage);
				break;
			}
		}
		DWORD WINAPI threadGetTestImage(LPVOID params);
		case WM_GET_CON_BKI:{
			continueImage=true;
			assert(serialThread==0);
			serialThread=CreateThread(0,0,threadGetTestImage,this->m_hWnd,0,0);
		}break;
		case WM_STP_GET_BKI:{
			if(serialThread){
				continueImage=false;
				TerminateThread(serialThread,-1);
				CloseHandle(serialThread);
				serialThread=0;
			}
		}break;
	}
	progress->SetPos(0);
	return 1;
}

//������ȡͼ��ĵ���¼�
void Ctest_fingerDlg::OnBnClickedBtncontinueimage(){
	//���ݰ�ť�ϵ������жϵ�ǰ����״̬
	WCHAR str[512];
	btnContinueImage->GetWindowTextW(str,512);
	if(lstrcmp(str,_T("������ȡͼ��"))==0){
		MyLog.print(Log::LOGU,"��ʼ������ȡͼ��");
		updateControlDisable(actGetConImage);
		btnContinueImage->SetWindowText(_T("ֹͣ��ȡͼ��"));
		SendMessage(WM_GET_CON_IMAGE,WM_GET_CON_IMAGE,0);
	}else{
		MyLog.print(Log::LOGU,"ֹͣ������ȡͼ��");
		updateControlDisable(actStpGetImage);
		btnContinueImage->SetWindowText(_T("������ȡͼ��"));
		SendMessage(WM_STP_GET_IMAGE,WM_STP_GET_IMAGE,0);
	}
}


void Ctest_fingerDlg::OnBnClickedBtndevlog(){
	MyLog.print(Log::LOGU,"V0.9 <ʱ��δ֪>:����˴������Ӻ�ͼƬ��ʾ,�������־���ܵĽ���");
	MyLog.print(Log::LOGU,"V1.0 <2019��3��16��15:36:11>:���ԭʼͼ�������ȡͼ��ť����");
	MyLog.print(Log::LOGU,"V1.1 <2019��3��16��15:54:23>:��ɰ�ť����,��ֹ�̳߳�ͻ,��ӿ�����־");
	MyLog.print(Log::LOGU,"V1.2 <2019��3��18��00:57:44>:��Ӷ�д�Ĵ���,��ӽ�����,���ѡͼ���С");
	MyLog.print(Log::LOGU,"V1.3 <2019��3��24��13:59:42>:��������ù���ɾ��,�Ŵ���ָ��ͼ��,�޸��˰�ť����bug");
	MyLog.print(Log::LOGU,"V1.4 <2019��3��24��14:12:08>:�������releaseģʽ��ȡ��warning�Ĵ���,����˴��ļ��а�ť");
	MyLog.print(Log::LOGU,"V1.5 <2019��4��10��17:15:45>:�������ȡ��������");
	MyLog.print(Log::LOGU,"V1.6 <2019��4��22��22:42:59>:�����˺�о��ȡԭʼͼ����,�޸���ʱ��ͱ༭�����bug");
}

//���Ĵ������̺߳���
DWORD WINAPI threadReadReg(LPVOID params){
	CString hex;
	int integer;
	editReadRegAddr->GetWindowText(hex);
	sscanf(CString2char(hex),"%X",&integer);
	uint8_t address=integer;

	CCommunication::sendCommand(CMD_READ_NOTE_BOOK,&address,1);
	CCommunication::waitForPacket(1*1000);

	SendMessage((HWND)params,WM_READ_REGISTER,WM_READ_REGISTER,0);
	return 0;
}

//д�Ĵ������̺߳���
DWORD WINAPI threadWriteReg(LPVOID params){
	CString hex;
	int integer;
	uint8_t addrVal[2];
	editWriteRegAddr->GetWindowText(hex);
	sscanf(CString2char(hex),"%X",&integer);
	addrVal[0]=integer;
	editWriteRegVal->GetWindowText(hex);
	sscanf(CString2char(hex),"%X",&integer);
	addrVal[1]=integer;

    CCommunication::sendCommand(CMD_WRITE_NOTE_BOOK,addrVal,2);

	SendMessage((HWND)params,WM_WRITE_REGISTER,WM_WRITE_REGISTER,0);
	return 0;
}

void Ctest_fingerDlg::OnBnClickedBtnreadreg(){
	updateControlDisable(actReadingReg);
	progress->SetPos(10);
	MyLog.print(Log::LOGD,"Main Thread:1��ʼ���Ĵ���");
	serialThread=CreateThread(0,0,threadReadReg,this->m_hWnd,0,0);
	progress->SetPos(20);
    MyLog.print(Log::LOGD,"Main Thread:2���Ĵ����̵߳�ַ:%d",serialThread);
}


void Ctest_fingerDlg::OnBnClickedBtnwritereg(){
	updateControlDisable(actWritingReg);
	progress->SetPos(10);
	MyLog.print(Log::LOGD,"Main Thread:1��ʼд�Ĵ���");
	serialThread=CreateThread(0,0,threadWriteReg,this->m_hWnd,0,0);
	progress->SetPos(20);
    MyLog.print(Log::LOGD,"Main Thread:2д�Ĵ����̵߳�ַ:%d",serialThread);
}


void Ctest_fingerDlg::OnBnClickedBtnsetcmos(){
	WCHAR a[100],b[100];
	GetDlgItemText(IDC_EDITLightTime,a,100);
	GetDlgItemText(IDC_EDITSensitivity,b,100);
	if(a[0]==0&&b[0]==0)
		MyLog.print(Log::LOGU,"����ʧ��,������Ϊ��");
	else if(a[0]==0)
		MyLog.print(Log::LOGU,CString(_T("����������Ϊ"))+b);
	else if(b[0]==0)
		MyLog.print(Log::LOGU,CString(_T("�����ع�ʱ��Ϊ"))+a);
	else
		MyLog.print(Log::LOGU,CString(_T("�����ع�ʱ��Ϊ"))+a+_T(" , ")+_T("����������Ϊ")+b);
}


void Ctest_fingerDlg::OnBnClickedBtnsetbaud(){
	int baud=GetDlgItemInt(IDC_CMBBaudSet);
	MyLog.print(Log::LOGU,"���ô��ڲ�����Ϊ%d",baud);
}


void Ctest_fingerDlg::OnBnClickedBtnsetpassword(){
	WCHAR str[100];
	GetDlgItemText(IDC_EDITPasswordSet,str,100);
	MyLog.print(Log::LOGU,CString(_T("���ô���ͨ������Ϊ"))+str);
}


void Ctest_fingerDlg::OnBnClickedBtnsetaddress(){
	WCHAR str[100];
	GetDlgItemText(IDC_EDITAddressSet,str,100);
	MyLog.print(Log::LOGU,CString(_T("���ô���ͨ�ŵ�ַΪ"))+str);
}


void Ctest_fingerDlg::OnBnClickedBtnopenimage(){
    ShellExecuteA(NULL, "explore", "collectedImage", NULL, NULL, SW_HIDE);
}


void Ctest_fingerDlg::OnBnClickedBtncontinuebackgroundimage(){
	//���ݰ�ť�ϵ������жϵ�ǰ����״̬
	WCHAR str[512];
	btnContinueBackGroundImage->GetWindowTextW(str,512);
	if(lstrcmp(str,_T("������ȡ����"))==0){
		MyLog.print(Log::LOGU,"��ʼ������ȡ����");
		updateControlDisable(actGetConBKI);
		btnContinueBackGroundImage->SetWindowText(_T("ֹͣ��ȡ����"));
		SendMessage(WM_GET_CON_BKI,WM_GET_CON_BKI,0);
	}else{
		MyLog.print(Log::LOGU,"ֹͣ������ȡ����");
		updateControlDisable(actStpGetBKI);
		btnContinueBackGroundImage->SetWindowText(_T("������ȡ����"));
		SendMessage(WM_STP_GET_BKI,WM_STP_GET_BKI,0);
	}
}


void Ctest_fingerDlg::OnBnClickedBtnopenbackgroundimage(){
    ShellExecuteA(NULL, "explore", "collectedBGI", NULL, NULL, SW_HIDE);
}

//��ȡ�������̺߳���
DWORD WINAPI threadGetTestImage(LPVOID params){
	CCommunication::sendCommand(CMD_GET_TEST_IMAGE);
	progress->SetPos(30);
	MyLog.print(Log::LOGD,"Serial Thread:1����λ����������:CMD_GET_TEST_IMAGE");
	CCommunication::waitForPacket(10*1000);
	progress->SetPos(50);
	MyLog.print(Log::LOGD,"Serial Thread:2���յ����ݰ�,��СΪ%d",packetCnt);
	MyLog.print(Log::LOGD,"Serial Thread:3�߳������̷߳�����ϢCMD_GET_TEST_IMAGE");
	SendMessage((HWND)params,WM_GET_TEST_IMAGE,WM_GET_TEST_IMAGE,0);
	return 0;
}

void Ctest_fingerDlg::OnBnClickedBtnbackgroundimage(){
	updateControlDisable(actGetingImage);
	progress->SetPos(10);
	MyLog.print(Log::LOGD,"Main Thread:��ʼ�ɼ�����");
	serialThread=CreateThread(0,0,threadGetTestImage,this->m_hWnd,0,0);
	progress->SetPos(20);
    MyLog.print(Log::LOGD,"Main Thread:�ɼ������̵߳�ַ:%d",serialThread);
}
