#pragma once
#include"stdafx.h"
#include"MyListenerHeadFile.h"

CommBoardcast boardcastListener;

CommBoardcast::CommBoardcast(){
    attach(CMD_GET_RAW_IMAGE,(ICommListener*)(new GET_RAW_IMAGE_Listener()));
    attach(CMD_GET_TEST_IMAGE,(ICommListener*)(new GET_TEST_IMAGE_Listener()));
    attach(CMD_READ_NOTE_BOOK,(ICommListener*)(new READ_REGISTER_Listener()));
    attach(CMD_WRITE_NOTE_BOOK,(ICommListener*)(new WRITE_REGISTER_Listener()));
    attach(CmdCodeLOG_Info,(ICommListener*)(new CmdCodeLOG_Info_Listener()));
    attach(CmdCodeLOG_MeasureTimeStart,(ICommListener*)(new CmdCodeLOG_MeasureTimeStart_Listener()));
    attach(CmdCodeLOG_MeasureTimeEnd,(ICommListener*)(new CmdCodeLOG_MeasureTimeEnd_Listener()));
}

void CommBoardcast::attach(int event,ICommListener* listener){
    if(!m.count(event)){
        m[event]=std::vector<ICommListener*>();
    }
    m[event].push_back(listener);
}

void CommBoardcast::boardcast(int event,DataPacket response){
    std::vector<ICommListener*>::iterator it;
    for(it=m[event].begin();it!=m[event].end();it++){
        (*it)->listen(response);
    }
}
