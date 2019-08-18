#pragma once
#include "DataPacket.h"
#include "MainDialog.h"
#include "MainControl.h"
#include "CommandControl.h"

class CommandDialog: public CDialogEx{
    DECLARE_DYNAMIC(CommandDialog)

public:
    CommandDialog(std::vector<struct Command>& v,CWnd* pParent=nullptr);
    virtual ~CommandDialog();
    //��Ϣ������
    afx_msg LRESULT response(WPARAM w,LPARAM l);

#ifdef AFX_DESIGN_TIME
    enum{
        IDD=IDD_TabsDialog
    };
#endif

protected:
    std::vector<struct Command> commands;
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
    CommandControl* cc[10];

public:
    virtual void OnOK();
    afx_msg void OnClick();
};
extern int isFreeRequest;
