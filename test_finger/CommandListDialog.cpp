#include "stdafx.h"

IMPLEMENT_DYNAMIC(CommandListDialog,CDialogEx)

// ���캯��
CommandListDialog::CommandListDialog(CWnd* pParent): CDialogEx(IDD_CommandListDialog,pParent){}

// ��������
CommandListDialog::~CommandListDialog(){}

LRESULT CommandListDialog::response(WPARAM w,LPARAM l){

    return TRUE;
}

CListCtrl* listCtrl;
CButton* btnAddPlugin;
CButton* btnRemovePlugin;
CButton* btnOpenPluginFolder;
CButton* btnEditPlugin;

// ��ʼ���¼�
BOOL CommandListDialog::OnInitDialog(){
    CDialogEx::OnInitDialog();

    btnAddPlugin=(CButton*)GetDlgItem(IDC_BTNAddPlugin);
    btnRemovePlugin=(CButton*)GetDlgItem(IDC_BTNRemovePlugin);
    btnOpenPluginFolder=(CButton*)GetDlgItem(IDC_BTNOpenPluginFolder);
    btnEditPlugin=(CButton*)GetDlgItem(IDC_BTNEditPlugin);

    listCtrl=(CListCtrl*)GetDlgItem(IDC_LSTPlugin);
    listCtrl->ModifyStyle(LVS_LIST,LVS_REPORT);
    listCtrl->SetExtendedStyle(LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);
    listCtrl->InsertColumn(0,L"����",LVCFMT_LEFT,50);
    listCtrl->InsertColumn(1,L"��Ч��",LVCFMT_LEFT,50);
    listCtrl->InsertColumn(2,L"·��",LVCFMT_LEFT,250-50-50);

    OnBnClickedBtnFlush();

    return 0;
}

// ��ֹEnter�رմ���
void CommandListDialog::OnOK(){}

// ��Ϣӳ��
BEGIN_MESSAGE_MAP(CommandListDialog,CDialogEx)
    RESPONSE_USER_MESSAGE(response)
    ON_BN_CLICKED(IDC_BTNAddPlugin,&CommandListDialog::OnBnClickedBtnAddPlugin)
    ON_BN_CLICKED(IDC_BTNRemovePlugin,&CommandListDialog::OnBnClickedBtnRemovePlugin)
    ON_BN_CLICKED(IDC_BTNSaveDefaultPlugin,&CommandListDialog::OnBnClickedBtnSaveDefaultPlugin)
    ON_BN_CLICKED(IDC_BTNOpenPluginFolder,&CommandListDialog::OnBnClickedBtnOpenPluginFolder)
    ON_BN_CLICKED(IDC_BTNEditPlugin,&CommandListDialog::OnBnClickedBtnEditPlugin)
    ON_BN_CLICKED(IDC_BTNFlush,&CommandListDialog::OnBnClickedBtnFlush)
END_MESSAGE_MAP()

void CommandListDialog::OnBnClickedBtnAddPlugin(){
    TCHAR szBuffer[MAX_PATH]={0};
    OPENFILENAME openFilename={0};
    openFilename.lStructSize=sizeof(openFilename);
    openFilename.hwndOwner=m_hWnd;
    openFilename.lpstrFilter=_T("����ļ�(*.ini)*.ini�����ļ�(*.*)*.*");
    openFilename.lpstrFile=szBuffer;
    openFilename.nMaxFile=sizeof(szBuffer)/sizeof(*szBuffer);
    openFilename.nFilterIndex=0;
    openFilename.Flags=OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER;
    BOOL bSel=GetOpenFileName(&openFilename);
    if(bSel){
        int CustomCnt=MyString::ParseInt(conf["CustomCnt"]);
        conf[(std::string)MyString::Format("Custom%d",CustomCnt)]=MyString(openFilename.lpstrFile);
        conf["CustomCnt"]=MyString::IntToMyString(CustomCnt+1);
        OnBnClickedBtnFlush();
    }
}


void CommandListDialog::OnBnClickedBtnRemovePlugin(){
    int position=listCtrl->GetSelectionMark();
    listCtrl->DeleteItem(position);
    int CustomCnt=MyString::ParseInt(conf["CustomCnt"]);
    for(int i=position;i<CustomCnt-1;i++){
        conf[(std::string)MyString::Format("Custom%d",i)]=conf[(std::string)MyString::Format("Custom%d",i+1)];
    }
    conf[(std::string)MyString::Format("Custom%d",CustomCnt-1)]="";
    conf["CustomCnt"]=MyString::IntToMyString(CustomCnt-1);
}


void CommandListDialog::OnBnClickedBtnSaveDefaultPlugin(){
    CFileDialog fileDlg1(FALSE,MyString("ini"),MyString("��һ��Ĭ�ϲ��"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,MyString("�����ļ�(*.ini)|*.ini|�����ļ�(*.*)|*.*||"),this);
    if(IDOK==fileDlg1.DoModal()){
        MyString filepath=fileDlg1.GetPathName();
        MyFile::SaveDefaultPlugin1(filepath);
    }
    CFileDialog fileDlg2(FALSE,MyString("ini"),MyString("�ڶ���Ĭ�ϲ��"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,MyString("�����ļ�(*.ini)|*.ini|�����ļ�(*.*)|*.*||"),this);
    if(IDOK==fileDlg2.DoModal()){
        MyString filepath=fileDlg2.GetPathName();
        MyFile::SaveDefaultPlugin2(filepath);
    }
}


void CommandListDialog::OnBnClickedBtnOpenPluginFolder(){
    int position=listCtrl->GetSelectionMark();
    std::string path=conf[(std::string)MyString::Format("Custom%d",position)];
    int end=path.rfind('\\');
    MyString PATH=path.substr(0,end);
    ShellExecuteA(NULL,"explore",PATH,NULL,NULL,SW_NORMAL);
}


void CommandListDialog::OnBnClickedBtnEditPlugin(){

}


void CommandListDialog::OnBnClickedBtnFlush(){
    btnAddPlugin->EnableWindow(conf["SaveConf"]==Stringify(true));
    btnRemovePlugin->EnableWindow(conf["SaveConf"]==Stringify(true));
    btnOpenPluginFolder->EnableWindow(conf["SaveConf"]==Stringify(true));
    btnEditPlugin->EnableWindow(conf["SaveConf"]==Stringify(true));
    listCtrl->DeleteAllItems();
    if(conf["SaveConf"]==Stringify(true)){
        int CustomCnt=MyString::ParseInt(conf["CustomCnt"]);
        for(int i=0;i<CustomCnt;i++){
            std::string key=MyString::Format("Custom%d",i);
            MyString TabName;
            std::vector<struct Command> v;
            bool have=MyFile::ReadCommands(conf[key],TabName,v);
            int pos=listCtrl->InsertItem(i,TabName);
            listCtrl->SetItemText(pos,1,have?L"��Ч":L"��Ч");
            listCtrl->SetItemText(pos,2,MyString(conf[key]));
        }
    }
}
