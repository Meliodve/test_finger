#pragma once
#include"stdafx.h"

int CString2int(CString c){
    int ret;
    swscanf(c,_T("%d"),&ret);
    return ret;
}

char* CString2char(CString&c){
    static char text[65536+10];
    int len=WideCharToMultiByte(0,0,c,c.GetLength(),0,0,0,0);
    WideCharToMultiByte(0,0,c,c.GetLength(),text,len,0,0);
    text[len]=0;
    return text;
}

std::vector<int>* idle=new std::vector<int>();
std::vector<int>* lastIdle=NULL;

void enumerateSerialPorts(){
    //���������������
    idle->clear();
    //��Ϊ������255�����ڣ��������μ��������Ƿ����
    //����ܴ�ĳһ���ڣ���򿪴��ڲ��ɹ��������ص��� ERROR_ACCESS_DENIED������Ϣ��
    //����Ϊ���ڴ��ڣ�ֻ�������߱��������Ѿ���ռ��,���򴮿ڲ�����
    //���255��̫��ʱ��,����ǰ30���ļ��ʽϴ�
    for(int i=1; i<30; i++){
        //����ԭʼ�豸��
        CString sPort;
        sPort.Format(_T("\\\\.\\COM%d"),i);

        HANDLE hPort=::CreateFile(sPort,GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,0,0);
        if(hPort!=INVALID_HANDLE_VALUE){
            idle->push_back(i);
            CloseHandle(hPort);
        }
    }
}

void updateCommunityWay(){
    if(lastIdle){
        delete lastIdle;
    }
    lastIdle=idle;
    idle=new std::vector<int>();

    enumerateSerialPorts();
    //UI:��Ͽ� ����
    cmbWay->ResetContent();
    if(idle->size()==0){
        MyLog.print(Log::LOGU,"δ���ֿ��еĴ���");
        return;
    } else{
        MyLog.print(Log::LOGU,"����%d������",idle->size());
        for(int i=0;i<idle->size();i++){
            CString name;
            name.Format(_T("COM%d"),(*idle)[i]);
            cmbWay->InsertString(i,name);
        }
    }
}


void autoConnect(){
    int id=CCommunication::getConnectId();
    //�Զ�����ֻ��δ����״̬��Ч
    if(id==0){
        if(idle->size()==lastIdle->size()+1){ //Ӧ�û�����һ�������豸
            std::vector<int> diff;
            std::set_difference(
                idle->begin(),idle->end(),
                lastIdle->begin(),lastIdle->end(),
                std::inserter(diff,diff.begin())
            );//��idle-lastIdle
            if(diff.size()==1){ //�Ӧ��ֻ��һ��Ԫ��
                int needConnectId=diff[0];
                for(int i=0;i<idle->size();i++){
                    if((*idle)[i]==needConnectId){
                        cmbWay->SetCurSel(i);
                        CString baud;
                        cmbBaud->GetWindowTextW(baud);
                        CCommunication::connect(needConnectId,CString2int(baud));
                    }
                }
            } else{
                MyLog.print(Log::LOGE,"����Bug,��ǰ���ڴ���δ����״̬,����һ�δ���ö��,����idle��lastIdle�ĲԪ�ظ�������һ��,��ϸ��Ϣ:");
                {
                    CString error=_T("diff:");
                    for(std::vector<int>::iterator it=diff.begin();it!=diff.end();it++){
                        char number[20];
                        sprintf(number," %d",*it);
                        error+=number;
                    }
                    MyLog.print(Log::LOGE,error);
                }
            }
        } else{
            //�����쳣���
            MyLog.print(Log::LOGE,"����Bug,��ǰ���ڴ���δ����״̬,����һ�δ���ö��,����idle������lastIdle��,��ϸ��Ϣ:");
            {
                CString error=_T("idle:");
                for(std::vector<int>::iterator it=idle->begin();it!=idle->end();it++){
                    char number[20];
                    sprintf(number," %d",*it);
                    error+=number;
                }
                MyLog.print(Log::LOGE,error);
            }
            {
                CString error=_T("lastIdle:");
                for(std::vector<int>::iterator it=lastIdle->begin();it!=lastIdle->end();it++){
                    char number[20];
                    sprintf(number," %d",*it);
                    error+=number;
                }
                MyLog.print(Log::LOGE,error);
            }
        }
    }
}

void autoDisconnect(){
    int id=CCommunication::getConnectId();
    //�Զ��Ͽ���������״̬��
    if(id!=0){
        bool needDisconnect=true;
        for(int i=0;i<idle->size();i++){
            if((*idle)[i]==id){
                needDisconnect=false;
            }
        }
        if(needDisconnect){
            CCommunication::disConnect();
        }
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