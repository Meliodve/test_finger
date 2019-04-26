#pragma once
#include"stdafx.h"

char* CString2char(CString&c){
	static char text[65536+10];
	int len=WideCharToMultiByte(0,0,c,c.GetLength(),0,0,0,0);
	WideCharToMultiByte(0,0,c,c.GetLength(),text,len,0,0);
	text[len]=0;
	return text;
}

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
	time_t curtime;
	time(&curtime);
	sprintf(tstr,"%s ",ctime(&curtime));
	return tstr;
}

void log(int level,CString info){
	if(level>LOGT){
		ASF_WARNING(1);
	}
	if(level>cmbLogLevel->GetCurSel())return;
	CString time(timeStr()),old;
	int len=editLog->GetWindowTextLength();
	//ѡ����ǰ�ı���ĩ��
	editLog->SetSel(len,len);
	//׷���ı�
	editLog->ReplaceSel(time+info+"\r\n");

	//�Զ�����
	editLog->GetWindowText(old);
	char* text=CString2char(old);
	//write into file
	FILE* fp=fopen("backup.txt","w");
	fprintf(fp,"%s",text);
	fclose(fp);
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
		}else{
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
	}else{
		ASF_WARNING(4);
	}
}

bool saveBmp(int h,int w,BYTE*pData,CString dir,CString path){
    for(int i=0;i<w*h-1-i;i++){
        BYTE t = pData[w*h-1-i];
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
	//if(packetDataLen!=160*160)
	//	ASF_WARNING(3);


	int w,h;
	if(packetDataLen==160*160){
		log(LOGU,"���յ�160x160��ͼ��");
		w=h=160;
		saveBmp(w,h,packetData,x,path);
		loadImage((LPTSTR)(LPCTSTR)path);
	}else if(packetDataLen==192*192){
		log(LOGU,"���յ�192x192��ͼ��");
		w=h=192;
		saveBmp(w,h,packetData,x,path);
		loadImage((LPTSTR)(LPCTSTR)path);
	}else{
		log(LOGU,"�Ȳ���160x160Ҳ����192x192,û����Ⱦͼ��");
	}
}