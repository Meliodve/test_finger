#pragma once
#include"stdafx.h"

// ��ʼ��MainDialog�Ŀؼ�ָ��,�Լ���ʼ��һЩ�ؼ�����
void initMainControl(MainDialog* Dlg);

// ��MainDialog����Ϣ������������Ϣ
void sendMainDialogMessage(int Message);

// ����ͨ�ŷ�ʽ��Ͽ�
void updateCommunityWay();
// �����Զ�����
void autoConnect();
// �Զ��Ͽ�����
void autoDisconnect();

// ���ͨ�ŷ�ʽ��ѡ���Com��,USB����=0,���ڷ���>0
int getComID();

// ���ý���������[0,100]
void setProgress(int percent);
// ���ý���������[0.0,100.0]
void setProgress(double percent);

// ���⹫���Ŀؼ�
extern CEdit* editLog;
extern CEdit* editNow;
extern CEdit* editAddress;
extern CEdit* editPassword;
extern CEdit* editReadRegAddr;
extern CEdit* editReadRegVal;
extern CEdit* editWriteRegAddr;
extern CEdit* editWriteRegVal;
extern CEdit* editFingerId;
extern CComboBox* cmbWay;
extern CComboBox* cmbBaud;
extern CComboBox* cmbProtocolType;
extern CComboBox* cmbLogLevel;
extern CButton* btnConnect;
extern CButton* btnAdvDbg;
extern CButton* btnRawImage;
extern CButton* btnTestImage;
extern CButton* btnContinueImage;
extern CButton* btnContinueBGImg;
extern CButton* btnSaveLog;
extern CButton* btnReadReg;
extern CButton* btnWriteReg;
extern CButton* btnEnroll;
extern CButton* btnMatch;
extern CButton* btnDeviceInfo;
extern CButton* btnViewEnrollIds;
extern CButton* btnCancel;
extern CButton* btnClearLog;
extern CButton* btnDeleteTemplate;
extern CStatic* image;
extern CProgressCtrl* progress;
extern AdvancedDebugDialog* advancedDebugDialog;

// font
extern CFont* defaultFont;
