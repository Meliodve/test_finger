#pragma once
#include"stdafx.h"

Log MyLog;
bool Log::isExistLog(){
    FILE* fp=fopen(LOG_FILE,"r");
    if(fp){
        fclose(fp);
    }
    return fp!=NULL;
}

void Log::clearLog(){
    if(isExistLog()){
        remove(LOG_FILE);
    }
}

void Log::createLog(){
    fclose(fopen(LOG_FILE,"a+"));
}

void Log::appendLog(wchar_t* text){
    FILE* fp=fopen(LOG_FILE,"a+");
    fwprintf_s(fp,_T("%s"),text);
    fclose(fp);
}

void Log::print(LogLevel level,MyString info){
    if(level>=LOG_HIGHEST){
        print(Log::LOGW,"%s at %s(%d)FuncName:<%s>",ASF_WARNING1,__FILE__,__LINE__,__FUNCTION__);
    }
    if(level>cmbLogLevel->GetCurSel())return;

    time_t curtime;
    time(&curtime);
    MyString time(ctime(&curtime));
    MyString content=time+" "+info+"\r\n";
    int len=editLog->GetWindowTextLength();
    //ѡ����ǰ�ı���ĩ��
    editLog->SetSel(len,len);
    //�ڱ༭����׷���ı�
    editLog->ReplaceSel(content);
    //���ļ���׷���ı�
    appendLog(content);
}

void Log::print(LogLevel level,const char* format,...){
    static char tmp[512];
    va_list ap;
    va_start(ap,format);
    vsprintf(tmp,format,ap);
    va_end(ap);

    CString info(tmp);
    print(level,info);
}