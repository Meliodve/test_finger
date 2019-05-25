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
    void print(LogLevel level,MyString info);
    void print(LogLevel level,const char* format,...);
    void debug(MyString info);
    void debug(const char* format,...);
    void error(MyString info);
    void error(const char* format,...);
    void warn(MyString info);
    void warn(const char* format,...);
    void user(MyString info);
    void user(const char* format,...);
    void DevelopLog();
private:
    const char* LOG_FILE="backup.txt";
    bool isExistLog();
    void clearLog();
    void createLog();
    void appendLog(const char * text);
};

extern Log MyLog;
