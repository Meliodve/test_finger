#include "stdafx.h"

// ���ؿؼ�������,������MyString
MyString getText(CWnd * pWnd){
    if(test.isTest(test.My)){
        throw 0;
    }
    static CString ret;
    pWnd->GetWindowText(ret);
    return ret;
}

// ���ÿؼ�������
void setText(CWnd * pWnd,MyString str){
    if(test.isTest(test.My)){
        test.myTest.My_CtrlSet.push_back(std::make_pair(pWnd,str));
        return;
    }
    pWnd->SetWindowText(str);
}

// ����ѡ���Ĺ�ѡ״̬
void setCheck(CButton * pCheck,bool select){
    pCheck->SetCheck(select?TRUE:FALSE);
}

// ���ѡ���Ĺ�ѡ״̬
bool isChecked(CButton * pCheck){
    return pCheck->GetCheck()==BST_CHECKED;
}

// �ѿؼ��е����ݵ�ʮ���ƽ�������һ������
int getInt(CWnd * pWnd){
    int ret;
    getText(pWnd).Parse("%d",&ret);
    return ret;
}

// �ѿؼ��е����ݵ�ʮ�����ƽ�������һ������
int getHex(CWnd * pWnd){
    int ret;
    getText(pWnd).Parse("%x",&ret);
    return ret;
}

// ��filePath��ͼ����ص�ͼƬ�ؼ���
void loadImage(CStatic* image,MyString filePath){
    if(test.isTest(test.UI)){
        return;
    }
    HBITMAP hBmp=(HBITMAP)LoadImage(0,filePath,0,0,0,LR_LOADFROMFILE);
    if(hBmp){
        image->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE);
        image->SetBitmap(hBmp);
    } else{
        ASF_WARNING(4);
    }
}

// �����ѡЭ��
MyString getProtocol(){
    if(test.isTest(test.UI)){
        return MyString(test.uiTest.UI_protocol);
    }
    return getText(cmbProtocolType);
}
