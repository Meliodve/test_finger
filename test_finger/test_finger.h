
// test_finger.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ctest_fingerApp:
// �йش����ʵ�֣������ test_finger.cpp
//

class Ctest_fingerApp : public CWinApp
{
public:
	Ctest_fingerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ctest_fingerApp theApp;