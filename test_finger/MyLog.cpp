#pragma once
#include"stdafx.h"
#include "MyLog.h"

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

void Log::appendLog(const char* text){
    FILE* fp=fopen(LOG_FILE,"a+");
    fprintf_s(fp,"%s",text);
    fclose(fp);
}

void Log::print(LogLevel level,MyString info){
    static MyString last="",lastEdit="";
    if(level>=LOG_HIGHEST){
        ASF_WARNING(1);
        level=LOGD;
    }

    time_t curtime;
    time(&curtime);
    MyString time(ctime(&curtime));
    MyString content=MyString::Time("%Y-%m-%d %H:%M:%S ")+info+"\r\n";
    int len=editLog->GetWindowTextLength();
    if(last==info){
        setText(editLog,lastEdit+content);
        editLog->SetSel(len,len);
        appendLog(content);
    } else{
        editLog->SetSel(len,len);
        editLog->ReplaceSel(content);
        appendLog(content);
        lastEdit=getText(editLog);
    }
    last=info;
}

void Log::print(LogLevel level,const char* format,...){
    static char tmp[512];
    va_list ap;
    va_start(ap,format);
    vsprintf(tmp,format,ap);
    va_end(ap);

    print(level,MyString(tmp));
}

void Log::debug(MyString info){
    print(LOGD,info);
}

void Log::debug(const char * format,...){
    static char tmp[512];
    va_list ap;
    va_start(ap,format);
    vsprintf(tmp,format,ap);
    va_end(ap);

    print(LOGD,tmp);
}

void Log::error(MyString info){
    print(LOGE,info);
}

void Log::error(const char * format,...){
    static char tmp[512];
    va_list ap;
    va_start(ap,format);
    vsprintf(tmp,format,ap);
    va_end(ap);

    print(LOGE,tmp);
}

void Log::warn(MyString info){
    print(LOGW,info);
}

void Log::warn(const char * format,...){
    static char tmp[512];
    va_list ap;
    va_start(ap,format);
    vsprintf(tmp,format,ap);
    va_end(ap);

    print(LOGW,tmp);
}

void Log::user(MyString info){
    print(LOGU,info);
}

void Log::user(const char * format,...){
    static char tmp[512];
    va_list ap;
    va_start(ap,format);
    vsprintf(tmp,format,ap);
    va_end(ap);

    print(LOGU,tmp);
}

void Log::DevelopLog(){
    print(Log::LOGU,"V0.9 <ʱ��δ֪>:����˴������Ӻ�ͼƬ��ʾ,�������־���ܵĽ���");
    print(Log::LOGU,"V1.0 <2019��3��16��15:36:11>:���ԭʼͼ�������ȡͼ��ť����");
    print(Log::LOGU,"V1.1 <2019��3��16��15:54:23>:��ɰ�ť����,��ֹ�̳߳�ͻ,��ӿ�����־");
    print(Log::LOGU,"V1.2 <2019��3��18��00:57:44>:��Ӷ�д�Ĵ���,��ӽ�����,���ѡͼ���С");
    print(Log::LOGU,"V1.3 <2019��3��24��13:59:42>:��������ù���ɾ��,�Ŵ���ָ��ͼ��,�޸��˰�ť����bug");
    print(Log::LOGU,"V1.4 <2019��3��24��14:12:08>:�������releaseģʽ��ȡ��warning�Ĵ���,����˴��ļ��а�ť");
    print(Log::LOGU,"V1.5 <2019��4��10��17:15:45>:�������ȡ��������");
    print(Log::LOGU,"V1.6 <2019��4��22��22:42:59>:�����˺�о��ȡԭʼͼ����,�޸���ʱ��ͱ༭�����bug");
    print(Log::LOGU,"V2.0 <2019��4��28��17:17:46>:�����˴��ڼܹ�,֧�������ͱ���ģʽ����");
    print(Log::LOGU,"V2.01<2019��4��29��12:15:13>:�������ھ����������,�޸���һЩ��֪bug");
    print(Log::LOGU,"V2.1 <2019��4��29��16:55:54>:�����˰���ȷ�Ϸ���,����DataPacket��ʶ��Э��");
    print(Log::LOGU,"V2.2 <2019��4��30��14:44:30>:�����˸߼����Թ���");
    print(Log::LOGU,"V2.3 <2019��5��01��20:56:32>:�����µ�Э��ASFComm");
    print(Log::LOGU,"V2.31<2019��5��01��23:12:42>:������AdjustingImage�����ӿ�");
}
