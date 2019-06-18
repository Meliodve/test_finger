// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
#pragma once

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT _WIN32_WINNT_MAXVER

#define STRICT

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

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

//C
#include <afxpriv.h>
#include <Dbt.h>
#include <assert.h>
#include <io.h>
//C++
#include <functional>
#include <iterator>
#include <algorithm>
#include <exception>
#include <vector>
#include <queue>
#include <map>

#include "MyDefine.h"

#include "resource.h"

#include "Test.h"

#include "MyLocker.h"
#include "MyControl.h"
#include "MyConfig.h"
#include "strings.h"
#include "MyThread.h"
#include "MyFlow.h"
#include "MyString.h"
#include "MyLog.h"
#include "MyNet.h"

#include "Serial.h"
#include "enumcd.h"
#include "UsbPort.h"

#include "App.h"
#include "MainDialog.h"
#include "AdvancedDebugDialog.h"
#include "SettingDialog.h"

#include "MainControl.h"
#include "MainDialogCtrlValidity.h"

#include "DataPacket.h"
#include "ConverterBoardcast.h"
#include "MyConverterHeadFile.h"
#include "ListenerBoardcast.h"
#include "MyListenerHeadFile.h"
#include "Comm.h"

#include "MyImage.h"
