#pragma once


// Ctest_fingerDlg �Ի���
class Ctest_fingerDlg : public CDialogEx
{
// ����
public:
	Ctest_fingerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_FINGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);
	afx_msg LRESULT serialResponse(WPARAM w,LPARAM l);
	DECLARE_MESSAGE_MAP()
public:
	HANDLE serialThread;
	afx_msg void OnBnClickedBtnconnect();
	afx_msg void OnBnClickedBtnsavelog();
	afx_msg void OnBnClickedBtnrawimage();
	afx_msg void OnBnClickedBtncontinueimage();
	afx_msg void OnBnClickedBtndevlog();
};