#include "stdafx.h"
#include "test_finger.h"
#include "test_fingerDlg.h"
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
CStatic* textDevice;
CStatic* image;
BYTE packet[65536];
DWORD packetCnt;


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
	ON_WM_QUERYDRAGICON()
	ON_WM_DEVICECHANGE()
	ON_BN_CLICKED(IDC_BTNConnect, &Ctest_fingerDlg::OnBnClickedBtnconnect)
	ON_BN_CLICKED(IDC_BTNSaveLog, &Ctest_fingerDlg::OnBnClickedBtnsavelog)
	ON_BN_CLICKED(IDC_BTNRawImage, &Ctest_fingerDlg::OnBnClickedBtnrawimage)
	ON_BN_CLICKED(IDC_BTNContinueImage, &Ctest_fingerDlg::OnBnClickedBtncontinueimage)
	ON_BN_CLICKED(IDC_BTNdevLog, &Ctest_fingerDlg::OnBnClickedBtndevlog)
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
	textDevice		= (CStatic*) GetDlgItem(IDC_TEXTDevice);
	image			= (CStatic*) GetDlgItem(IDC_IMAGE);

	///2.����Ͽ�ĳ�ʼ��
	updateCommunityWay();
	//���ò�����
	const WCHAR* baud[]={_T("9600"),_T("115200"),0};
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
	const WCHAR* logLevel[]={_T("�û�"),_T("����"),_T("����"),_T("����"),0};
	for(int i=0;logLevel[i];i++){
		cmbLogLevel->InsertString(i,logLevel[i]);
	}
	cmbLogLevel->SetCurSel(3);

	///3.���� ���ؼ�����Ȩ��
	updateControlDisable(actInit);

	///4.�߳̾������
	serialThread=0;

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
		char filePath[256]={},* text;
		int len=WideCharToMultiByte(0,0,path,path.GetLength(),0,0,0,0);
		WideCharToMultiByte(0,0,path,path.GetLength(),filePath,len,0,0);
		len=WideCharToMultiByte(0,0,logText,logText.GetLength(),0,0,0,0);
		text=new char[len+1];
		WideCharToMultiByte(0,0,logText,logText.GetLength(),text,len,0,0);
		text[len+1]=0;
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
	log(LOGD,"Serial Thread:3����λ����������:CMD_GET_RAW_IMAGE");
	log(LOGU,"�����ָ");
	serial.Read(packet,sizeof packet,&packetCnt,0,10*1000);
	log(LOGD,"Serial Thread:4���յ����ݰ�,��СΪ%d",packetCnt);
	log(LOGD,"Serial Thread:5�߳������̷߳�����ϢWM_GET_RAW_IMAGE");
	SendMessage((HWND)params,WM_GET_RAW_IMAGE,WM_GET_RAW_IMAGE,0);
	return 0;
}

//ԭʼͼ��ĵ���¼�
void Ctest_fingerDlg::OnBnClickedBtnrawimage(){
	log(LOGD,"Main Thread:1��ʼ�ɼ�ԭʼͼ��");
	serialThread=CreateThread(0,0,threadGetRawImage,this->m_hWnd,0,0);
    log(LOGD,"Main Thread:2�ɼ�ͼ���̵߳�ַ:%d",serialThread);
}

//�����߳���Ϣ������
LRESULT Ctest_fingerDlg::serialResponse(WPARAM w,LPARAM l){
	static bool continueImage=false;
	switch(w){
		case WM_GET_RAW_IMAGE:{
			log(LOGD,"Main Thread:6��Ϣ�������յ���ϢWM_GET_RAW_IMAGE");
			static uint8_t imageBuf[160*160];
			//����ͼƬ�İ���26627�ֽڵ�
			//�ɺܶ�С�����,���а�ͷռ19�ֽ�,CRCУ��ռ2�ֽڴ��ڰ�β
			for(int i=0,j=0;i<packetCnt;){
				int k=packet[i+15]+packet[i+16]*256;//�����ݲ��ֳ���
				i+=19;//������ͷ
				while(k--){
					imageBuf[j++]=packet[i++];
				}
				i+=2;//����CRC
			}
			
			if(packetCnt==0){
				log(LOGU,"�������ݳ�ʱ");
				CloseHandle(serialThread);
				serialThread=0;
			}else{
				CString path=CTime::GetCurrentTime().Format("%Y_%m_%d_%H_%M_%S");
				path=_T("collectedImage/")+path+_T(".bmp");
				saveBmp(160,160,imageBuf,path);
				loadImage((LPTSTR)(LPCTSTR)path);
				log(LOGD,"Main Thread:7����ͼƬ���");
				log(LOGU,"�������ݳɹ�");
				CloseHandle(serialThread);
				serialThread=0;
			}
			if(!continueImage){
				break;
			}
		}//if continueImage then can exec next
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
	}
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
}
