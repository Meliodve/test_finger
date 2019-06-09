#include "stdafx.h"

//���ؿؼ�������,������MyString
MyString getText(CWnd * pWnd){
    static CString ret;
    pWnd->GetWindowText(ret);
    return ret;
}

//���ÿؼ�������
void setText(CWnd * pWnd,MyString str){
    pWnd->SetWindowText(str);
}

//�ѿؼ��е����ݵ�ʮ���ƽ�������һ������
int getInt(CWnd * pWnd){
    int ret;
    getText(pWnd).Parse("%d",&ret);
    return ret;
}

//�ѿؼ��е����ݵ�ʮ�����ƽ�������һ������
int getHex(CWnd * pWnd){
    int ret;
    getText(pWnd).Parse("%x",&ret);
    return ret;
}

//��filePath��ͼ����ص�ͼƬ�ؼ���
void loadImage(CStatic* image,MyString filePath){
    HBITMAP hBmp=(HBITMAP)LoadImage(0,filePath,0,0,0,LR_LOADFROMFILE);
    if(hBmp){
        image->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE);
        image->SetBitmap(hBmp);
    } else{
        ASF_WARNING(4);
    }
}
