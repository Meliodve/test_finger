#include "stdafx.h"

IMPLEMENT_DYNAMIC(CommandDialog,CDialogEx)

// ���캯��
CommandDialog::CommandDialog(std::vector<struct Command>& v,CWnd* pParent)
    : CDialogEx(IDD_CommandDialog,pParent){
    commands=v;
    Create(IDD_CommandDialog,this);
    ShowWindow(SW_SHOW);
}

// ��������
CommandDialog::~CommandDialog(){
    //TODO ����
}

LRESULT CommandDialog::response(WPARAM w,LPARAM l){

    return TRUE;
}

// ��ʼ���¼�
BOOL CommandDialog::OnInitDialog(){
    CDialogEx::OnInitDialog();

    // TODO ��̬���ӿؼ�
    return 0;
}

// ��ֹEnter�رմ���
void CommandDialog::OnOK(){}

// ��Ϣӳ��
BEGIN_MESSAGE_MAP(CommandDialog,CDialogEx)
    RESPONSE_USER_MESSAGE(response)
END_MESSAGE_MAP()
