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

class CommandControl{
public:
    CommandControl(int height,struct Command c,CWnd* parent){
        CmdCode=c.CmdCode;
        btn=new CButton();
        btn->Create(c.Name,0,CRect(10,height,50,height+20),parent,nID);
        for(int i=0;i<c.Type.size();i++){
            txt.push_back(new CStatic());
            edt.push_back(new CEdit());
            txt[i]->Create(c.Type[i].first,0,CRect(60+60*i,height,80+60*i,height+20),parent);
            edt[i]->Create(0,CRect(80+60*i,height,120+60*i,height+20),parent,nID*10+i);
        }
        nID++;
    }
    DataPacket Click(){

    }
private:
    static int nID;
    int CmdCode;
    CButton* btn;
    std::vector<CStatic*> txt;
    std::vector<CEdit*> edt;
};
int CommandControl::nID=2001;
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
