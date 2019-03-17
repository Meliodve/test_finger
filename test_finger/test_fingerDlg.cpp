#include "stdafx.h"
#include "afxdialogex.h"

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
CComboBox* cmbSecurity;
CComboBox* cmbLogLevel;
CButton* btnConnect;
CButton* btnReset;
CButton* btnRawImage;
CButton* btnContinueImage;
CButton* btnSetSecurity;
CButton* btnSetCmos;
CButton* btnSetBaud;
CButton* btnSetPassword;
CButton* btnSetAddress;
CButton* btnSaveLog;
CButton* btnReadReg;
CButton* btnWriteReg;
CButton* radImgSize1;
CButton* radImgSize2;
CButton* radImgSize3;
CButton* radImgSize4;
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
	ON_WM_QUERYDRAGICON()
	ON_WM_DEVICECHANGE()
	ON_BN_CLICKED(IDC_BTNConnect, &Ctest_fingerDlg::OnBnClickedBtnconnect)
	ON_BN_CLICKED(IDC_BTNSaveLog, &Ctest_fingerDlg::OnBnClickedBtnsavelog)
	ON_BN_CLICKED(IDC_BTNRawImage, &Ctest_fingerDlg::OnBnClickedBtnrawimage)
	ON_BN_CLICKED(IDC_BTNContinueImage, &Ctest_fingerDlg::OnBnClickedBtncontinueimage)
	ON_BN_CLICKED(IDC_BTNdevLog, &Ctest_fingerDlg::OnBnClickedBtndevlog)
	ON_BN_CLICKED(IDC_BTNreadReg, &Ctest_fingerDlg::OnBnClickedBtnreadreg)
	ON_BN_CLICKED(IDC_BTNwriteReg, &Ctest_fingerDlg::OnBnClickedBtnwritereg)
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
	cmbSecurity		= (CComboBox*) GetDlgItem(IDC_CMBSecurity);
	cmbLogLevel		= (CComboBox*) GetDlgItem(IDC_CMBLogLevel);
	btnConnect		= (CButton*) GetDlgItem(IDC_BTNConnect);
	btnReset		= (CButton*) GetDlgItem(IDC_BTNReset);
	btnRawImage		= (CButton*) GetDlgItem(IDC_BTNRawImage);
	btnContinueImage= (CButton*) GetDlgItem(IDC_BTNContinueImage);
	btnSetSecurity	= (CButton*) GetDlgItem(IDC_BTNSetSecurity);
	btnSetCmos		= (CButton*) GetDlgItem(IDC_BTNSetCmos);
	btnSetBaud		= (CButton*) GetDlgItem(IDC_BTNSetBaud);
	btnSetPassword	= (CButton*) GetDlgItem(IDC_BTNSetPassword);
	btnSetAddress	= (CButton*) GetDlgItem(IDC_BTNSetAddress);
	btnSaveLog		= (CButton*) GetDlgItem(IDC_BTNSaveLog);
	btnReadReg		= (CButton*) GetDlgItem(IDC_BTNreadReg);
	btnWriteReg		= (CButton*) GetDlgItem(IDC_BTNwriteReg);
	radImgSize1		= (CButton*) GetDlgItem(IDC_RADimgSize1);
	radImgSize2		= (CButton*) GetDlgItem(IDC_RADimgSize2);
	radImgSize3		= (CButton*) GetDlgItem(IDC_RADimgSize3);
	radImgSize4		= (CButton*) GetDlgItem(IDC_RADimgSize4);
	textDevice		= (CStatic*) GetDlgItem(IDC_TEXTDevice);
	image			= (CStatic*) GetDlgItem(IDC_IMAGE);
	progress		= (CProgressCtrl*) GetDlgItem(IDC_PROGRESS);

	///2.����Ͽ�ĳ�ʼ��
	updateCommunityWay();
	//���ò�����
	const WCHAR* baud[]={_T("9600"),_T("115200"),_T("256000"),0};
	for(int i=0;baud[i];i++){
		cmbBaud->InsertString(i,baud[i]);
		cmbBaudSet->InsertString(i,baud[i]);
	}
	cmbBaud->SetCurSel(1);
	//ָ�ư�ȫ����
	const WCHAR* security[]={_T("1"),_T("2"),_T("3"),_T("4"),_T("5"),0};
	for(int i=0;security[i];i++){
		cmbSecurity->InsertString(i,security[i]);
	}
	cmbSecurity->SetCurSel(2);
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

	///6.Ĭ��ѡ��160x160
	((CButton*)GetDlgItem(IDC_RADimgSize1))->SetCheck(TRUE);

	///0.����
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Ctest_fingerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Ctest_fingerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//֧�ִ����Ȱβ���豸���ļ�������
#include<Dbt.h>
#include "test_fingerDlg.h"
afx_msg BOOL Ctest_fingerDlg::OnDeviceChange(UINT nEventType, DWORD dwData){
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
	WCHAR str[512];
	btnConnect->GetWindowTextW(str,512);
	if(lstrcmp(str,_T("������λ��"))==0){
		updateControlDisable(actOpeningPort);

		LONG baud=GetDlgItemInt(IDC_CMBBaud);//��ȡ������
		cmbWay->GetWindowText(str,512);
		CString way(str);int com;
		swscanf(way,_T("COM%d"),&com);//��ȡͨ�ŷ�ʽ
		
		way.Format(_T("\\\\.\\COM%d"),com);//�õ��˿ڵ�ַ
		LONG retCode=ERROR_SUCCESS;

		if(retCode==ERROR_SUCCESS)
			retCode=serial.Open(way,2048,2048,true);

		//����������������Ĭ�ϲ���
		if(retCode==ERROR_SUCCESS)
			retCode=serial.Setup((CSerial::EBaudrate)baud);

		if(retCode==ERROR_SUCCESS)
			retCode=serial.SetMask(CSerial::EEventRecv);
		if(retCode==ERROR_SUCCESS){
			log(LOGU,"����COM%d�ɹ�",com);
			updateControlDisable(actOpenedPort);
			btnConnect->SetWindowText(_T("�Ͽ�����"));
			serial.Purge();
		}else{
			log(LOGU,"����COM%dʧ��",com);
			updateControlDisable(actClosedPort);
		}
	}else{
		serial.Close();
		updateControlDisable(actClosedPort);
		log(LOGU,"�Ͽ����ӳɹ�");
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
		char filePath[256]={},* text=CString2char(logText);
		int len=WideCharToMultiByte(0,0,path,path.GetLength(),0,0,0,0);
		WideCharToMultiByte(0,0,path,path.GetLength(),filePath,len,0,0);
		//write into file
		FILE* fp=fopen(filePath,"w");
		fprintf(fp,"%s",text);
		fclose(fp);
	}
}

//��ȡԭʼͼ����̺߳���
DWORD WINAPI threadGetRawImage(LPVOID params){
	serial.Purge();
	SendCommand(CMD_GET_RAW_IMAGE,0,0);
	progress->SetPos(30);
	log(LOGD,"Serial Thread:3����λ����������:CMD_GET_RAW_IMAGE");
	log(LOGU,"�����ָ");
	serial.Read(packet,sizeof packet,&packetCnt,0,10*1000);
	progress->SetPos(50);
	log(LOGD,"Serial Thread:4���յ����ݰ�,��СΪ%d",packetCnt);
	log(LOGD,"Serial Thread:5�߳������̷߳�����ϢWM_GET_RAW_IMAGE");
	SendMessage((HWND)params,WM_GET_RAW_IMAGE,WM_GET_RAW_IMAGE,0);
	return 0;
}

//ԭʼͼ��ĵ���¼�
void Ctest_fingerDlg::OnBnClickedBtnrawimage(){
	updateControlDisable(actGetingImage);
	progress->SetPos(10);
	log(LOGD,"Main Thread:1��ʼ�ɼ�ԭʼͼ��");
	serialThread=CreateThread(0,0,threadGetRawImage,this->m_hWnd,0,0);
	progress->SetPos(20);
    log(LOGD,"Main Thread:2�ɼ�ͼ���̵߳�ַ:%d",serialThread);
}

//�����߳���Ϣ������
LRESULT Ctest_fingerDlg::serialResponse(WPARAM w,LPARAM l){
	static bool continueImage=false;
	switch(w){
		case WM_GET_RAW_IMAGE:{
			progress->SetPos(75);
			log(LOGD,"Main Thread:6��Ϣ�������յ���ϢWM_GET_RAW_IMAGE");
			getDataFromPacket();
			
			if(packetDataLen==0){
				log(LOGU,"�������ݳ�ʱ");
				CloseHandle(serialThread);
				serialThread=0;
			}else{
				CString path=CTime::GetCurrentTime().Format("%Y_%m_%d_%H_%M_%S");
				path=_T("collectedImage/")+path+_T(".bmp");
				if(packetDataLen!=160*160)
					ASF_WARNING(03);
				saveBmp(160,160,packetData,path);
				loadImage((LPTSTR)(LPCTSTR)path);
				progress->SetPos(100);
				log(LOGD,"Main Thread:7����ͼƬ���");
				log(LOGU,"�������ݳɹ�");
				CloseHandle(serialThread);
				serialThread=0;
			}
			updateControlDisable(actGotImage);
			if(!continueImage){
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
			getDataFromPacket();
			if(packetDataLen==0){
				log(LOGU,"�������ݳ�ʱ");
				CloseHandle(serialThread);
				serialThread=0;
			}else{
				CString tmp;
				tmp.Format(_T("%X"),packetData[0]);
				editReadRegVal->SetWindowText(tmp);
				log(LOGU,"�������ݳɹ�");
				CloseHandle(serialThread);
				serialThread=0;
			}
			updateControlDisable(actReadedReg);
		}break;
		case WM_WRITE_REGISTER:{
			log(LOGU,"�޸ļĴ�������ͳɹ�");
			CloseHandle(serialThread);
			serialThread=0;
			updateControlDisable(actWritedReg);
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
		log(LOGU,"��ʼ������ȡͼ��");
		updateControlDisable(actGetConImage);
		btnContinueImage->SetWindowText(_T("ֹͣ��ȡͼ��"));
		SendMessage(WM_GET_CON_IMAGE,WM_GET_CON_IMAGE,0);
	}else{
		log(LOGU,"ֹͣ������ȡͼ��");
		updateControlDisable(actStpGetImage);
		btnContinueImage->SetWindowText(_T("������ȡͼ��"));
		SendMessage(WM_STP_GET_IMAGE,WM_STP_GET_IMAGE,0);
	}
}


void Ctest_fingerDlg::OnBnClickedBtndevlog(){
	log(LOGU,"V0.9 <ʱ��δ֪>:����˴������Ӻ�ͼƬ��ʾ,�������־���ܵĽ���");
	log(LOGU,"V1.0 <2019��3��16��15:36:11>:���ԭʼͼ�������ȡͼ��ť����");
	log(LOGU,"V1.1 <2019��3��16��15:54:23>:��ɰ�ť����,��ֹ�̳߳�ͻ,��ӿ�����־");
	log(LOGU,"V1.2 <2019��3��18��00:57:44>:��Ӷ�д�Ĵ���,��ӽ�����,���ѡͼ���С");
}

//���Ĵ������̺߳���
DWORD WINAPI threadReadReg(LPVOID params){
	CString hex;
	int integer;
	editReadRegAddr->GetWindowText(hex);
	sscanf(CString2char(hex),"%X",&integer);
	U8 address=integer;

    serial.Purge();
    SendCommand(CMD_READ_NOTE_BOOK,&address,1);

	serial.Read(packet,sizeof packet,&packetCnt,NULL,1000);

	SendMessage((HWND)params,WM_READ_REGISTER,WM_READ_REGISTER,0);
	return 0;
}

//д�Ĵ������̺߳���
DWORD WINAPI threadWriteReg(LPVOID params){
	CString hex;
	int integer;
	U8 addrVal[2];
	editWriteRegAddr->GetWindowText(hex);
	sscanf(CString2char(hex),"%X",&integer);
	addrVal[0]=integer;
	editWriteRegVal->GetWindowText(hex);
	sscanf(CString2char(hex),"%X",&integer);
	addrVal[1]=integer;

    serial.Purge();
    SendCommand(CMD_WRITE_NOTE_BOOK,addrVal,2);

	SendMessage((HWND)params,WM_WRITE_REGISTER,WM_WRITE_REGISTER,0);
	return 0;
}

void Ctest_fingerDlg::OnBnClickedBtnreadreg(){
	updateControlDisable(actReadingReg);
	progress->SetPos(10);
	log(LOGD,"Main Thread:1��ʼ���Ĵ���");
	serialThread=CreateThread(0,0,threadReadReg,this->m_hWnd,0,0);
	progress->SetPos(20);
    log(LOGD,"Main Thread:2���Ĵ����̵߳�ַ:%d",serialThread);
}


void Ctest_fingerDlg::OnBnClickedBtnwritereg(){
	updateControlDisable(actWritingReg);
	progress->SetPos(10);
	log(LOGD,"Main Thread:1��ʼд�Ĵ���");
	serialThread=CreateThread(0,0,threadWriteReg,this->m_hWnd,0,0);
	progress->SetPos(20);
    log(LOGD,"Main Thread:2д�Ĵ����̵߳�ַ:%d",serialThread);
}
