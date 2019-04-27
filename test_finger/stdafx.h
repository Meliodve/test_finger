
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#define STRICT

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include<afxpriv.h>
#include<Dbt.h>
#include<assert.h>
#include<iterator>
#include<algorithm>
#include<vector>
#include<map>

extern CEdit* editLog;
extern CEdit* editAddress;
extern CEdit* editPassword;
extern CEdit* editAddressSet;
extern CEdit* editPasswordSet;
extern CEdit* editLightTime;
extern CEdit* editSensitivity;
extern CEdit* editReadRegAddr;
extern CEdit* editReadRegVal;
extern CEdit* editWriteRegAddr;
extern CEdit* editWriteRegVal;
extern CComboBox* cmbWay;
extern CComboBox* cmbBaud;
extern CComboBox* cmbBaudSet;
extern CComboBox* cmbChipType;
extern CComboBox* cmbLogLevel;
extern CButton* btnConnect;
extern CButton* btnRawImage;
extern CButton* btnTestImage;
extern CButton* btnContinueImage;
extern CButton* btnContinueBackGroundImage;
extern CButton* btnSetCmos;
extern CButton* btnSetBaud;
extern CButton* btnSetPassword;
extern CButton* btnSetAddress;
extern CButton* btnSaveLog;
extern CButton* btnReadReg;
extern CButton* btnWriteReg;
extern CButton* chkTimeoutContinue;
extern CStatic* textDevice;
extern CStatic* image;
extern CProgressCtrl* progress;

#define WM_GET_RAW_IMAGE	WM_USER+5
#define WM_GET_CON_IMAGE	WM_USER+6
#define WM_STP_GET_IMAGE	WM_USER+7
#define WM_READ_REGISTER	WM_USER+8
#define WM_WRITE_REGISTER	WM_USER+9
#define WM_GET_CON_BKI		WM_USER+10
#define WM_STP_GET_BKI		WM_USER+11
#define WM_GET_TEST_IMAGE	WM_USER+12

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

#include"str4err_warn.h"
#include"MyLog.h"

#include"comm.h"
#include"enumcd.h"
#include"UsbPort.h"
#include"CCommunication.h"
#include"CommListener.h"
#include"CommProtocolConverter.h"

#include"test_finger.h"
#include"test_fingerDlg.h"
#include"algo.h"//�����Ŀ�õ��㷨ͷ�ļ�
extern BYTE packet[65536];
extern DWORD packetCnt;
extern BYTE packetData[65536];
extern DWORD packetDataLen;