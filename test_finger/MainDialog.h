#pragma once
#include"stdafx.h"

// ��������
class MainDialog: public CDialogEx{
public:
    // �����ڵĹ��캯��
    MainDialog(CWnd* pParent=NULL);
    enum{
        IDD=IDD_TEST_FINGER_DIALOG
    };
protected:
    HICON m_hIcon;
    // ��ʼ�������¼�
    virtual BOOL OnInitDialog();
    // �ػ��¼�
    afx_msg void OnPaint();
    // ��ѯͼ���¼�
    afx_msg HCURSOR OnQueryDragIcon();
    //֧�ִ����Ȱβ���豸���ļ�������
    afx_msg BOOL OnDeviceChange(UINT nEventType,DWORD dwData);
    //�����߳���Ϣ������
    afx_msg LRESULT serialResponse(WPARAM w,LPARAM l);
    DECLARE_MESSAGE_MAP()
public:
    virtual void OnOK();
    afx_msg void OnBnClickedBtnConnect();
    afx_msg void OnBnClickedBtnSaveLog();
    afx_msg void OnBnClickedBtnRawImage();
    afx_msg void OnBnClickedBtnContinueImage();
    afx_msg void OnBnClickedBtnDevLog();
    afx_msg void OnBnClickedBtnReadReg();
    afx_msg void OnBnClickedBtnWriteReg();
    afx_msg void OnBnClickedBtnOpenImage();
    afx_msg void OnBnClickedBtnContinueBackgroundImage();
    afx_msg void OnBnClickedBtnOpenBackgroundImage();
    afx_msg void OnBnClickedBtnBackgroundImage();
    afx_msg void OnCbnCloseupCmbLogLevel();
    afx_msg void OnBnClickedBtnAdvDbg();
    afx_msg void OnBnClickedBtn();
    afx_msg void OnBnClickedBtnEnroll();
    afx_msg void OnBnClickedBtnMatch();
    afx_msg void OnBnClickedBtnDeviceInfo();
    afx_msg void OnBnClickedBtnViewEnrollIDs();
    afx_msg void OnBnClickedBtnDeleteTemplate();
    afx_msg void OnBnClickedBtnCancel();
    afx_msg void OnBnClickedBtnClearLog();
    afx_msg void OnBnClickedBtnSetting();
    afx_msg void OnCbnSelChangeCmbBaud();
    afx_msg void OnCbnSelChangeCmbProtocolType();
    afx_msg void OnCbnSelChangeCmbWay();
    afx_msg void OnCbnSelchangeCmbloglevel();
    afx_msg void OnBnClickedBtnTest();
    afx_msg void OnEnChangeEditAddress();
    afx_msg void OnBnClickedBtnSearch();
    afx_msg void OnBnClickedChkLED();
};
