#pragma once
#include"stdafx.h"

char* CString2char(CString&c){
    static char text[65536+10];
    int len=WideCharToMultiByte(0,0,c,c.GetLength(),0,0,0,0);
    WideCharToMultiByte(0,0,c,c.GetLength(),text,len,0,0);
    text[len]=0;
    return text;
}

void enumerateSerialPorts(CUIntArray* idle,CUIntArray* buzy){
    //���������������
    idle->RemoveAll();
    buzy->RemoveAll();
    //��Ϊ������255�����ڣ��������μ��������Ƿ����
    //����ܴ�ĳһ���ڣ���򿪴��ڲ��ɹ��������ص��� ERROR_ACCESS_DENIED������Ϣ��
    //����Ϊ���ڴ��ڣ�ֻ�������߱��������Ѿ���ռ��,���򴮿ڲ�����
    //���255��̫��ʱ��,����ǰ30���ļ��ʽϴ�
    for(int i=1; i<30; i++){
        //����ԭʼ�豸��
        CString sPort;
        sPort.Format(_T("\\\\.\\COM%d"),i);

        //��ͼ�򿪴˴���
        BOOL bSuccess;
        HANDLE hPort=::CreateFile(sPort,GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,0,0);
        if(hPort==INVALID_HANDLE_VALUE){
            //�򿪴���ʧ��
            bSuccess=FALSE;
            DWORD dwError=GetLastError();
            if(dwError==ERROR_ACCESS_DENIED){
                bSuccess=TRUE;
                buzy->Add(i);//��ռ�õĴ���
            }
        } else{
            //�򿪴��ڳɹ�
            bSuccess=TRUE;
            idle->Add(i);//���õĴ���
            if(!CloseHandle(hPort)){
                DWORD dwError=GetLastError();//�رղ��ɹ���ԭ��
            }
        }
    }
}

void updateCommunityWay(){
    CUIntArray*idle,*buzy;
    CUIntArray*lastIdle=0,*lastBuzy=0;
    cmbWay->ResetContent();
    enumerateSerialPorts(idle,buzy);
    if(lastIdle)
    if(idle->GetSize()>0){
        for(int i=0;i<idle->GetSize();i++){
            CString name;
            name.Format(_T("COM%d"),idle->ElementAt(i));
            cmbWay->InsertString(i,name);
        }
        cmbWay->SetCurSel(0);
        MyLog.print(Log::LOGU,"����%d������",idle->GetSize());
    } else{
        MyLog.print(Log::LOGU,"δ���ִ��ڵĴ���");
    }
}

//���غ���,���ÿؼ�
void disable(CWnd* pWnd){
    pWnd->EnableWindow(FALSE);
}
//���غ���,���ÿؼ�
void enable(CWnd* pWnd){
    pWnd->EnableWindow(TRUE);
}

void updateControlDisable(action a){
    switch(a){
        case actInit:
            actInit://һ����ǩ
            enable(cmbBaud);
            enable(cmbWay);

            disable(editAddress);
            disable(editPassword);
            disable(editAddressSet);
            disable(editPasswordSet);
            disable(editLightTime);
            disable(editSensitivity);
            disable(cmbBaudSet);
            disable(cmbChipType);
            disable(btnRawImage);
            disable(btnTestImage);
            disable(btnContinueImage);
            disable(btnContinueBackGroundImage);
            disable(btnSetCmos);
            disable(btnSetBaud);
            disable(btnSetPassword);
            disable(btnSetAddress);
            disable(btnReadReg);
            disable(btnWriteReg);
            break;
        case actOpeningPort:
        case actClosingPort:
            disable(cmbBaud);
            disable(cmbWay);
            disable(btnConnect);
            break;
        case actOpenedPort:
            enable(btnConnect);
            enable(editAddress);
            enable(editPassword);
            enable(editAddressSet);
            enable(editPasswordSet);
            enable(editLightTime);
            enable(editSensitivity);
            enable(cmbBaudSet);
            enable(cmbChipType);
            enable(btnRawImage);
            enable(btnTestImage);
            enable(btnContinueImage);
            enable(btnContinueBackGroundImage);
            enable(btnSetCmos);
            enable(btnSetBaud);
            enable(btnSetPassword);
            enable(btnSetAddress);
            enable(btnReadReg);
            enable(btnWriteReg);

            disable(cmbBaud);
            disable(cmbWay);
            break;
        case actClosedPort:
            enable(btnConnect);
            goto actInit;
            break;
        case actReadingReg:
        case actWritingReg:
        case actGetingImage:
            disable(btnConnect);
            disable(editAddress);
            disable(editPassword);
            disable(editAddressSet);
            disable(editPasswordSet);
            disable(editLightTime);
            disable(editSensitivity);
            disable(cmbBaudSet);
            disable(cmbChipType);
            disable(btnRawImage);
            disable(btnTestImage);
            disable(btnSetCmos);
            disable(btnSetBaud);
            disable(btnSetPassword);
            disable(btnSetAddress);
            disable(btnContinueImage);
            disable(btnContinueBackGroundImage);
            disable(btnReadReg);
            disable(btnWriteReg);
            break;
        case actReadedReg:
        case actWritedReg:
        case actGotImage:
            enable(btnConnect);
            enable(editAddress);
            enable(editPassword);
            enable(editAddressSet);
            enable(editPasswordSet);
            enable(editLightTime);
            enable(editSensitivity);
            enable(cmbBaudSet);
            enable(cmbChipType);
            enable(btnRawImage);
            enable(btnTestImage);
            enable(btnContinueImage);
            enable(btnContinueBackGroundImage);
            enable(btnSetCmos);
            enable(btnSetBaud);
            enable(btnSetPassword);
            enable(btnSetAddress);
            enable(btnReadReg);
            enable(btnWriteReg);
            break;
        case actGetConBKI:
        case actGetConImage:
            if(a==actGetConBKI){
                disable(btnContinueImage);
                enable(btnContinueBackGroundImage);
            } else{
                enable(btnContinueImage);
                disable(btnContinueBackGroundImage);
            }

            disable(editAddress);
            disable(editPassword);
            disable(editAddressSet);
            disable(editPasswordSet);
            disable(editLightTime);
            disable(editSensitivity);
            disable(cmbBaudSet);
            disable(cmbChipType);
            disable(btnRawImage);
            disable(btnTestImage);
            disable(btnSetCmos);
            disable(btnSetBaud);
            disable(btnSetPassword);
            disable(btnSetAddress);
            disable(btnReadReg);
            disable(btnWriteReg);
            disable(btnConnect);
            break;
        case actStpGetBKI:
        case actStpGetImage:
            enable(btnConnect);
            enable(editAddress);
            enable(editPassword);
            enable(editAddressSet);
            enable(editPasswordSet);
            enable(editLightTime);
            enable(editSensitivity);
            enable(cmbBaudSet);
            enable(cmbChipType);
            enable(btnRawImage);
            enable(btnTestImage);
            enable(btnContinueImage);
            enable(btnContinueBackGroundImage);
            enable(btnSetCmos);
            enable(btnSetBaud);
            enable(btnSetPassword);
            enable(btnSetAddress);
            enable(btnReadReg);
            enable(btnWriteReg);
            break;
    }
}

void loadImage(WCHAR* filePath){
    HBITMAP hBmp=(HBITMAP)LoadImage(0,filePath,0,0,0,LR_LOADFROMFILE);
    if(hBmp){
        image->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE);
        image->SetBitmap(hBmp);
    } else{
        ASF_WARNING(4);
    }
}

bool saveBmp(int h,int w,BYTE*pData,CString dir,CString path){
    for(int i=0;i<w*h-1-i;i++){
        BYTE t=pData[w*h-1-i];
        pData[w*h-1-i]=pData[i];
        pData[i]=t;
    }
    BITMAPINFOHEADER bmpInfo;
    bmpInfo.biSize=sizeof bmpInfo;
    bmpInfo.biWidth=w;
    bmpInfo.biHeight=h;
    bmpInfo.biPlanes=1;
    bmpInfo.biBitCount=8;
    bmpInfo.biCompression=BI_RGB;
    bmpInfo.biSizeImage=0;
    bmpInfo.biXPelsPerMeter=0;
    bmpInfo.biYPelsPerMeter=0;
    bmpInfo.biClrUsed=256;
    bmpInfo.biClrImportant=256;
    RGBQUAD bmfColorQuad[256];
    for(int i=0;i<256;i++){
        bmfColorQuad[i].rgbBlue=i;
        bmfColorQuad[i].rgbGreen=i;
        bmfColorQuad[i].rgbRed=i;
        bmfColorQuad[i].rgbReserved=0;
    }
    BITMAPFILEHEADER bmpFileInfo;
    bmpFileInfo.bfType=0x4d42;//"BM"
    bmpFileInfo.bfSize=0x400+w*h+(sizeof bmpInfo)+sizeof(bmpFileInfo);
    bmpFileInfo.bfReserved1=0;
    bmpFileInfo.bfReserved2=0;
    bmpFileInfo.bfOffBits=0x400+sizeof(BITMAPFILEHEADER)+
        sizeof(BITMAPINFOHEADER);

    CreateDirectory(dir,0);

    char* filePath=CString2char(path);
    FILE* fp=fopen(filePath,"wb");
    if(fp==NULL){
        ASF_ERROR(1);
        return false;
    }
    fwrite(&bmpFileInfo,sizeof bmpFileInfo,1,fp);
    fwrite(&bmpInfo,sizeof bmpInfo,1,fp);
    fwrite(&bmfColorQuad,sizeof bmfColorQuad,1,fp);
    fwrite(pData,w*h,1,fp);
    fclose(fp);
    return true;
}

void saveImage(CString x){
    CString path=CTime::GetCurrentTime().Format("%Y_%m_%d_%H_%M_%S");
    path=x+_T("/")+path+_T(".bmp");

    int w,h;
    if(packetDataLen==160*160){
        MyLog.print(Log::LOGU,"���յ�160x160��ͼ��");
        w=h=160;
        saveBmp(w,h,packetData,x,path);
        loadImage((LPTSTR)(LPCTSTR)path);
    } else if(packetDataLen==192*192){
        MyLog.print(Log::LOGU,"���յ�192x192��ͼ��");
        w=h=192;
        saveBmp(w,h,packetData,x,path);
        loadImage((LPTSTR)(LPCTSTR)path);
    } else{
        MyLog.print(Log::LOGU,"�Ȳ���160x160Ҳ����192x192,û����Ⱦͼ��");
    }
}