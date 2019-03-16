#pragma once
#include"stdafx.h"
#include"algo.h"
CSerial serial;//���ڶ���

void enumerateSerialPorts(CUIntArray& exist,CUIntArray& useful,CUIntArray& used){
    //���������������
    exist.RemoveAll();
    useful.RemoveAll();
    used.RemoveAll();
    int portState=0;
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
                used.Add(i);//��ռ�õĴ���
            }
        } else{
            //�򿪴��ڳɹ�
            bSuccess=TRUE;
            useful.Add(i);//���õĴ���
            if(!CloseHandle(hPort)){
                DWORD dwError=GetLastError();//�رղ��ɹ���ԭ��
            }
        }
        if(bSuccess){
            exist.Add(i);//���д��ڵĴ���
        }
    }
}

void updateCommunityWay(){
	CUIntArray exist,useful,used;
	CString name;
	cmbWay->ResetContent();
	enumerateSerialPorts(exist,useful,used);
	if(exist.GetSize()>0){
		for(int i=0;i<exist.GetSize();i++){
			name.Format(_T("COM%d"),exist.ElementAt(i));
			cmbWay->InsertString(i,name);
		}
		cmbWay->SetCurSel(0);
		log(LOGU,"����%d������",exist.GetSize());
	}else{
		log(LOGU,"δ���ִ��ڵĴ���");
	}
}

char* timeStr(){
	static char tstr[64];
	time_t tt=time(NULL);//����һ��ʱ���
	tm* t=localtime(&tt);
	sprintf(tstr,"%d-%02d-%02d %02d:%02d:%02d ",
		t->tm_year+1900,
		t->tm_mon+1,
		t->tm_mday,
		t->tm_hour,
		t->tm_min,
		t->tm_sec);
	return tstr;
}

void log(int level,CString info){
	if(level>cmbLogLevel->GetCurSel())return;
	CString time(timeStr()),old;
	editLog->GetWindowText(old);
	editLog->SetWindowText(old+time+info+"\r\n");
	editLog->SendMessage(WM_VSCROLL,SB_BOTTOM,0);//������ʼ���ڵײ�
}

void log(int level,const char* format,...){
	static char tmp[512];
	va_list ap;
	va_start(ap,format);
	vsprintf(tmp,format,ap);
	va_end(ap);
	
	CString info(tmp);
	log(level,info);
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
		disable(cmbSecurity);
		disable(btnReset);
		disable(btnRawImage);
		disable(btnContinueImage);
		disable(btnSetSecurity);
		disable(btnSetCmos);
		disable(btnSetBaud);
		disable(btnSetPassword);
		disable(btnSetAddress);
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
		enable(cmbSecurity);
		enable(btnReset);
		enable(btnRawImage);
		enable(btnContinueImage);
		enable(btnSetSecurity);
		enable(btnSetCmos);
		enable(btnSetBaud);
		enable(btnSetPassword);
		enable(btnSetAddress);

		disable(cmbBaud);
		disable(cmbWay);
		break;
	case actClosedPort:
		enable(btnConnect);
		goto actInit;
		break;
	case actGetConImage:
		enable(btnContinueImage);
		
		disable(btnConnect);
		disable(editAddress);
		disable(editPassword);
		disable(editAddressSet);
		disable(editPasswordSet);
		disable(editLightTime);
		disable(editSensitivity);
		disable(cmbBaudSet);
		disable(cmbSecurity);
		disable(btnReset);
		disable(btnRawImage);
		disable(btnSetSecurity);
		disable(btnSetCmos);
		disable(btnSetBaud);
		disable(btnSetPassword);
		disable(btnSetAddress);
		break;
	case actStpGetImage:
		enable(btnConnect);
		enable(editAddress);
		enable(editPassword);
		enable(editAddressSet);
		enable(editPasswordSet);
		enable(editLightTime);
		enable(editSensitivity);
		enable(cmbBaudSet);
		enable(cmbSecurity);
		enable(btnReset);
		enable(btnRawImage);
		enable(btnContinueImage);
		enable(btnSetSecurity);
		enable(btnSetCmos);
		enable(btnSetBaud);
		enable(btnSetPassword);
		enable(btnSetAddress);
		break;
	}
}

void loadImage(WCHAR* filePath){
    HBITMAP hBmp=(HBITMAP)LoadImage(0,filePath,0,0,0,LR_LOADFROMFILE);
	image->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE);
    image->SetBitmap(hBmp);
}

void saveBmp(int h,int w,BYTE*pData,CString path){
    HANDLE hFile;

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

	CreateDirectory(_T("collectedImage"),0);
    hFile=CreateFile(path,GENERIC_READ|GENERIC_WRITE,0,
		NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    if(hFile==INVALID_HANDLE_VALUE){
        return;
    }
    WriteFile(hFile,&bmpFileInfo,sizeof bmpFileInfo,0,0);
    WriteFile(hFile,&bmpInfo,sizeof bmpInfo,0,0);
    WriteFile(hFile,&bmfColorQuad,sizeof bmfColorQuad,0,0);
	WriteFile(hFile,pData,w*h,0,0);
    CloseHandle(hFile);
}