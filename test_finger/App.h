#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include"stdafx.h"

class App: public CWinApp{
public:
    App();
public:
    virtual BOOL InitInstance();
    DECLARE_MESSAGE_MAP()
};

extern App theApp;