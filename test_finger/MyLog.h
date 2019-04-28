#pragma once
#include"stdafx.h"

class Log{
public:
    enum LogLevel{
        LOGU,//�û�����Ϣ,���û���ʾ����Ϣ
        LOGE,//������Ϣ
        LOGW,//���漶��Ϣ
        LOGD,//���Լ���Ϣ
        LOGT,//��ʱ����Ϣ
        LOG_HIGHEST//������,��Ҫɾ
    };
    const char* LOG_FILE="backup.txt";
    bool isExistLog();
    void clearLog();
    void createLog();
    void appendLog(wchar_t* text);
    void print(LogLevel level,MyString info);
    void print(LogLevel level,const char* format,...);
};

extern Log MyLog;
