#include "stdafx.h"

// ��p���������,����Ϊlen��תһ��
void reverse(uint8_t* p,int len){
    for(int i=0;i<len-1-i;i++){
        uint8_t t=p[len-1-i];
        p[len-1-i]=p[i];
        p[i]=t;
    }
}

// �ѳ�Ϊw,��Ϊh��ͼƬpData,�浽��ǰĿ¼��dirnameĿ¼��,�ļ�����filename
bool saveBmp(int w,int h,uint8_t* pData,MyString dirname,MyString filename){
    if(test.isTest(test.UI)){
        return true;
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
    bmpFileInfo.bfOffBits=0x400+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

    CreateDirectory(dirname,0);

    FILE* fp=fopen(dirname+"/"+filename+".bmp","wb");
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

// ��dataPacket������ݵ���ͼƬ�浽dir·����
void saveImage(MyString dir,DataPacket dataPacket){
    MyString fileName=MyString::Time();
    MyString dirFileName=dir+"/"+fileName+".bmp";

    int w,h,dataSize=dataPacket.readSize();
    switch(dataSize){
        case 160*160/2:
        {
            MyLog::user("���յ�160x160��ͼ��");
            w=h=160;
            //��ͼ���4bitת��Ϊ8bit
            uint8_t* pData=dataPacket.getPointer();
            uint8_t* x2=new uint8_t[160*160+5];
            for(int i=0;i<160;i++){
                for(int j=0;j<80;j++){
                    x2[i*160+j*2]=pData[i*80+j]&0xF0;
                    x2[i*160+j*2+1]=(pData[i*80+j]&0x0F)<<4;
                }
            }
            pData=x2;
            //�������ھ����������
            for(int i=0;i<h;i++){
                for(int j=0;j<w;j++){
                    if(j==47||j==99||j==151){
                        pData[i*w+j]=(pData[i*w+j+1]+pData[i*w+j-1])/2;
                    }
                }
            }
            reverse(pData,w*h);
            for(int i=0;i<h;i++){
                reverse(pData+i*w,w);
            }

            saveBmp(w,h,pData,dir,fileName);
            loadImage(image,dirFileName);
            delete[] pData;
        }break;
        case 160*160:
        {
            MyLog::user("���յ�160x160��ͼ��");
            w=h=160;

            uint8_t* pData=dataPacket.getPointer();
            //�������ھ����������
            for(int i=0;i<h;i++){
                for(int j=0;j<w;j++){
                    if(j==47||j==99||j==151){
                        pData[i*w+j]=(pData[i*w+j+1]+pData[i*w+j-1])/2;
                    }
                }
            }
            reverse(pData,w*h);
            for(int i=0;i<h;i++){
                reverse(pData+i*w,w);
            }

            saveBmp(w,h,pData,dir,fileName);
            loadImage(image,dirFileName);
        }break;
        case 192*192:
        {
            MyLog::user("���յ�192x192��ͼ��");
            w=h=192;
            saveBmp(w,h,dataPacket.getPointer(),dir,fileName);
            loadImage(image,dirFileName);
        }break;
        default:
        {
            MyLog::user("�Ȳ���160x160Ҳ����192x192,û����Ⱦͼ��");
        }break;
    }
    dataPacket.readData(dataPacket.size());
}

// ��������ֱ��ͼ,����Ϊw*h��pData,���Ϊhw*hh��Histogram
void generateHistogram(uint8_t* Histogram,int hw,int hh,uint8_t* pData,int w,int h){
    auto func=[&](int position,int height)->void{
        for(int i=0;i<hh;i++){
            if(i==height){
                if(position>0){
                    Histogram[i*hw+position-1]=127;
                }
                if(position<hw){
                    Histogram[i*hw+position+1]=127;
                }
                Histogram[i*hw+position]=0;
            } else if(i==height+1||i==height-1){
                Histogram[i*hw+position]=127;
            } else{
                Histogram[i*hw+position]=255;
            }
        }
    };
    int* count=new int[hw];
    memset(count,0,hw*4);
    for(int i=0;i<w*h;i++){
        count[pData[i]*hw/256]++;
    }
    int max=0;
    for(int i=0;i<hw;i++){
        if(max<count[i]){
            max=count[i];
        }
    }
    for(int i=0;i<hw;i++){
        func(i,count[i]*hh/max);
    }
    delete[] count;
}

// ��w*h��src��ͼƬ�Ŵ�һ��,�浽dest��
void imgSizeX2(uint8_t * src,int w,int h,uint8_t * dest){
    int dw=w+w,dh=h+h;
    for(int i=0;i<dh;i++){
        for(int j=0;j<dw;j++){
            dest[i*dw+j]=src[i/2*w+j/2];
        }
    }
}
