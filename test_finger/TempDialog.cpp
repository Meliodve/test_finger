#include "stdafx.h"

IMPLEMENT_DYNAMIC(TempDialog,CDialogEx)

// ���캯��
TempDialog::TempDialog(CWnd* pParent)
    : CDialogEx(IDD_TempDialog,pParent){}

// ��������
TempDialog::~TempDialog(){
    //TODO ����
}

LRESULT TempDialog::response(WPARAM w,LPARAM l){
    return TRUE;
}

// ��ʼ���¼�
BOOL TempDialog::OnInitDialog(){
    CDialogEx::OnInitDialog();
    setText(GetDlgItem(IDC_EDITBufferID),"1");
    return 0;
}

// ��ֹEnter�رմ���
void TempDialog::OnOK(){}

// ��Ϣӳ��
BEGIN_MESSAGE_MAP(TempDialog,CDialogEx)
    RESPONSE_USER_MESSAGE(response)
    ON_BN_CLICKED(IDC_BTNDownImage,&TempDialog::OnBnClickedBtnDownImage)
    ON_BN_CLICKED(IDC_BTNWriteNotepad,&TempDialog::OnBnClickedBtnWriteNotepad)
    ON_BN_CLICKED(IDC_BTNDownChar,&TempDialog::OnBnClickedBtnDownChar)
END_MESSAGE_MAP()

void TempDialog::OnBnClickedBtnDownImage(){
    MyString SelectedImagePath;
    if(!MyFile::OpenFileDialog("bmp",this,SelectedImagePath)){
        MyLog::error("δѡ��ͼƬ");
        return;
    }

    if(MyFile::ReadImage(SelectedImagePath,tempCommDataPacket)){
        isFreeRequest=2;
        comm.request(0x0b);
        MyLog::user("����ͼ��ɹ�!");
    } else{
        MyLog::error("��ѡͼ�������ڷ���");
    }
}


void TempDialog::OnBnClickedBtnWriteNotepad(){
    MyString SelectedNotepadPath;
    if(!MyFile::OpenFileDialog("txt",this,SelectedNotepadPath)){
        MyLog::error("δѡ����±�");
        return;
    }

    int NotepadID=MyString::AutoParseInt(getText(GetDlgItem(IDC_EDITNotepadID)));
    if(0>NotepadID||NotepadID>15){
        MyLog::error("NotepadIDֻ����[0,15]�ķ�Χ��");
        return;
    }

    DataPacket data;
    MyString msg="";
    auto f=[&](FILE* fp)->bool{
        uint8_t pData[33];
        int ret,t;
        for(int i=0;i<32;i++){
            ret=fscanf(fp,"%x",&t);
            pData[i+1]=t;
            if(t<0||t>255){
                msg=MyString::Format("��%d��ʮ��������δ��[0x00,0xFF]��Χ��",i);
                return false;
            }
            if(ret==EOF){
                msg="ʮ����������������";
                return false;
            }
        }
        ret=fscanf(fp,"%*x");
        if(ret!=EOF){
            msg="ʮ����������������32��";
            return false;
        } else{
            pData[0]=NotepadID;
            data=DataPacket(pData,33);
            return true;
        }
    };

    if(MyFile::Read(SelectedNotepadPath,f)){
        isFreeRequest=2;
        comm.request(0x18,data);
        MyLog::user("����Notepad�ɹ�!");
    } else{
        MyLog::error("�ü��±���ʽ����ȷ:%s",(const char*)msg);
    }
}

void TempDialog::OnBnClickedBtnDownChar(){
    MyString SelectedCharPath;
    if(!MyFile::OpenFileDialog("char",this,SelectedCharPath)){
        MyLog::error("δѡ�������ļ�");
        return;
    }

    uint8_t BufferID=MyString::AutoParseInt(getText(GetDlgItem(IDC_EDITBufferID)));
    DataPacket data(&BufferID,1);

    if(MyFile::LoadCharFile(SelectedCharPath,tempCommDataPacket)){
        isFreeRequest=2;
        comm.request(0x09,data);
        MyLog::user("���������ļ��ɹ�!");
    } else{
        MyLog::error("��ѡ�����ļ��������ڷ���");
    }
}
