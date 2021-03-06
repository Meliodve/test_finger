﻿#pragma once

class SettingUpdatePage: public CDialogEx{
    DECLARE_DYNAMIC(SettingUpdatePage)

public:
    SettingUpdatePage(CWnd* pParent=nullptr);
    virtual ~SettingUpdatePage();

#ifdef AFX_DESIGN_TIME
    enum{
        IDD=IDD_SettingUpdatePage
    };
#endif

protected:
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

public:
    virtual void OnOK();
    afx_msg void OnBnClickedBtnCheckUpdate();
    afx_msg void OnBnClickedBtnDownload();
};
