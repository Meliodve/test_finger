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
	ON_WM_QUERYDRAGICON()
	ON_WM_DEVICECHANGE()
	ON_BN_CLICKED(IDC_BTNConnect, &Ctest_fingerDlg::OnBnClickedBtnconnect)
	ON_BN_CLICKED(IDC_BTNSaveLog, &Ctest_fingerDlg::OnBnClickedBtnsavelog)
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
	const WCHAR* baud[]={_T("9600"),_T("115200"),0};//���ò�����
	for(int i=0;baud[i];i++){
		cmbBaud->InsertString(i,baud[i]);
		cmbBaudSet->InsertString(i,baud[i]);
	}
	cmbBaud->SetCurSel(1);
	const WCHAR* security[]={_T("1"),_T("2"),_T("3"),_T("4"),_T("5"),0};//ָ�ư�ȫ����
	for(int i=0;security[i];i++){
		cmbSecurity->InsertString(i,security[i]);
	}
	cmbSecurity->SetCurSel(2);

	///3.���� ���ؼ�����Ȩ��
	updateControlDisable(actInit);


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
	
	loadImage(_T("res/preview.bmp"));

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
			log("����COM%d�ɹ�",com);
			updateControlDisable(actOpenedPort);
			btnConnect->SetWindowText(_T("�Ͽ�����"));
			serial.Purge();
		}else{
			log("����COM%dʧ��",com);
			updateControlDisable(actClosedPort);
		}
	}else{
		serial.Close();
		updateControlDisable(actClosedPort);
		log("�Ͽ����ӳɹ�");
		btnConnect->SetWindowText(_T("������λ��"));
	}
}


void Ctest_fingerDlg::OnBnClickedBtnsavelog(){
	
}
