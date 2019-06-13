#include "stdafx.h"

void CmdCodeLOG_AdvDbg_AdjImg_Listener::listen(DataPacket response){
    conf["id"]=MyString((char*)response.getPointer(),response.size()-32*32);
    response.readData(response.size()-32*32);
    uint8_t bigImg[64*64];
    imgSizeX2(response.getPointer(),32,32,bigImg);
    saveBmp(64,64,bigImg,"collectedTempImage",conf["AdvDbg_ImgId"]);
    uint8_t Histogram[256*64];
    generateHistogram(Histogram,256,64,response.getPointer(),32,32);
    saveBmp(256,64,Histogram,"collectedTempImage",MyString("Histogram")+conf["AdvDbg_ImgId"]);
    sendMainDialogMessage(WM_APPEND_CONTROLS);
    response.readData(32*32);
}

void CmdCodeLOG_Info_Listener::listen(DataPacket response){
    MyLog::debug((char*)response.getPointer());
}

clock_t clockTime;

void CmdCodeLOG_MeasureTimeStart_Listener::listen(DataPacket response){
    clockTime=clock();
}

void CmdCodeLOG_MeasureTimeEnd_Listener::listen(DataPacket response){
    MyLog::debug("MeasureTime:%d",clock()-clockTime);
}