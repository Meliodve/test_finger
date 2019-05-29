#pragma once
#include"stdafx.h"

const char* MyLog::LOG_FILE="backup_log.txt";

bool MyLog::isExistLog(){
    FILE* fp=fopen(LOG_FILE,"r");
    if(fp){
        fclose(fp);
    }
    return fp!=NULL;
}

void MyLog::clearLog(){
    if(isExistLog()){
        remove(LOG_FILE);
    }
}

void MyLog::createLog(){
    fclose(fopen(LOG_FILE,"a+"));
}

void MyLog::appendLog(const char* text){
    FILE* fp=fopen(LOG_FILE,"a+");
    fprintf_s(fp,"%s",text);
    fclose(fp);
}

void MyLog::print(LogLevel level,MyString info){
    //��־�ȼ��쳣
    if(level>=LOG_HIGHEST){
        ASF_WARNING(1);
        level=LOGD;
    }
    //���ӵȼ���ʾ
    const char* pLevel;
    switch(level){
        case LOGU:pLevel=" U ";break;
        case LOGE:pLevel=" E ";break;
        case LOGW:pLevel=" W ";break;
        case LOGD:pLevel=" D ";break;
        case LOGT:pLevel=" T ";break;
        default:pLevel=" Unknown ";break;
    }
    //�����װ�������Ϣ
    MyString content=MyString::Time("%Y-%m-%d %H:%M:%S")+pLevel+info+"\r\n";
    //�����߼�
    static MyString last_info="";
    if(info!=last_info){
        int len=editLog->GetWindowTextLength();
        MyString old_content=getText(editNow);
        editLog->SetSel(len,len,0);
        editLog->ReplaceSel(old_content);
        appendLog(old_content);
    }
    if(getText(editNow)!=content){
        setText(editNow,content);
    }
    last_info=info;
}

void MyLog::print(LogLevel level,const char* format,...){
    static char tmp[512];
    va_list ap;
    va_start(ap,format);
    vsprintf(tmp,format,ap);
    va_end(ap);

    print(level,MyString(tmp));
}

void MyLog::debug(MyString info){
    print(LOGD,info);
}

void MyLog::debug(const char * format,...){
    static char tmp[512];
    va_list ap;
    va_start(ap,format);
    vsprintf(tmp,format,ap);
    va_end(ap);

    print(LOGD,tmp);
}

void MyLog::error(MyString info){
    print(LOGE,info);
}

void MyLog::error(const char * format,...){
    static char tmp[512];
    va_list ap;
    va_start(ap,format);
    vsprintf(tmp,format,ap);
    va_end(ap);

    print(LOGE,tmp);
}

void MyLog::warn(MyString info){
    print(LOGW,info);
}

void MyLog::warn(const char * format,...){
    static char tmp[512];
    va_list ap;
    va_start(ap,format);
    vsprintf(tmp,format,ap);
    va_end(ap);

    print(LOGW,tmp);
}

void MyLog::user(MyString info){
    print(LOGU,info);
}

void MyLog::user(const char * format,...){
    static char tmp[512];
    va_list ap;
    va_start(ap,format);
    vsprintf(tmp,format,ap);
    va_end(ap);

    print(LOGU,tmp);
}

int Version=260;
void MyLog::DevelopLog(){
    //print(MyLog::LOGU,"V0.9 <ʱ��δ֪>:����˴������Ӻ�ͼƬ��ʾ,�������־���ܵĽ���");
    print(MyLog::LOGU,"V1.0 <2019��3��16��15:36:11>:���ԭʼͼ�������ȡͼ��ť����");
    //print(MyLog::LOGU,"V1.1 <2019��3��16��15:54:23>:��ɰ�ť����,��ֹ�̳߳�ͻ,��ӿ�����־");
    //print(MyLog::LOGU,"V1.2 <2019��3��18��00:57:44>:��Ӷ�д�Ĵ���,��ӽ�����,���ѡͼ���С");
    //print(MyLog::LOGU,"V1.3 <2019��3��24��13:59:42>:��������ù���ɾ��,�Ŵ���ָ��ͼ��,�޸��˰�ť����bug");
    //print(MyLog::LOGU,"V1.4 <2019��3��24��14:12:08>:�������releaseģʽ��ȡ��warning�Ĵ���,����˴��ļ��а�ť");
    //print(MyLog::LOGU,"V1.5 <2019��4��10��17:15:45>:�������ȡ��������");
    //print(MyLog::LOGU,"V1.6 <2019��4��22��22:42:59>:�����˺�о��ȡԭʼͼ����,�޸���ʱ��ͱ༭�����bug");
    print(MyLog::LOGU,"V2.0 <2019��4��28��17:17:46>:�����˴��ڼܹ�,֧�������ͱ���ģʽ����");
    //print(MyLog::LOGU,"V2.01<2019��4��29��12:15:13>:�������ھ����������,�޸���һЩ��֪bug");
    print(MyLog::LOGU,"V2.1 <2019��4��29��16:55:54>:�����˰���ȷ�Ϸ���,����DataPacket��ʶ��Э��");
    print(MyLog::LOGU,"V2.2 <2019��4��30��14:44:30>:�����˸߼����Թ���");
    print(MyLog::LOGU,"V2.3 <2019��5��01��20:56:32>:�����µ�Э��ASFComm");
    //print(MyLog::LOGU,"V2.31<2019��5��01��23:12:42>:������AdjustingImage�����ӿ�");
    print(MyLog::LOGU,"V2.4 <2019��5��20��01:19:35>:������Syno��Э��,��ע��/�ȶԹ���");
    print(MyLog::LOGU,"V2.5 <2019��5��20��22:37:36>:������Syno��ɾ��/(����)ȡͼ����,���Ӹ��¹���");
    //print(MyLog::LOGU,"V2.51<2019��5��24��12:49:24>:�޸�GD32Э����Ĵ���bug,���䲨���ʺ�Э��");
    //print(MyLog::LOGU,"V2.52<2019��5��26��21:36:00>:����GD32Э���µ�DeviceInfo����,��һ���豸��Ϣ�İ�ť,��ǿ���¹���");
    print(MyLog::LOGU,"V2.6 <2019��5��27��22:49:28>:�Ż���־������,�����豸��Ϣ����");
    print(MyLog::LOGU,"V2.61<2019��5��29��16:29:31>:�޸��豸��Ϣ����ChipVersion bug");
}

void MyLog::ClearLog(){
    clearLog();
    createLog();
    setText(editLog,"");
}
