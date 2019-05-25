#pragma once
#include"stdafx.h"

class MyLog{
public:
    enum LogLevel{
        LOGU,//�û�����Ϣ,���û���ʾ����Ϣ
        LOGE,//������Ϣ
        LOGW,//���漶��Ϣ
        LOGD,//���Լ���Ϣ
        LOGT,//��ʱ����Ϣ
        LOG_HIGHEST//������,��Ҫɾ
    };
    static void print(LogLevel level,MyString info);
    static void print(LogLevel level,const char* format,...);
    static void debug(MyString info);
    static void debug(const char* format,...);
    static void error(MyString info);
    static void error(const char* format,...);
    static void warn(MyString info);
    static void warn(const char* format,...);
    static void user(MyString info);
    static void user(const char* format,...);
    static void DevelopLog();
    static void ClearLog();
private:
    static const char* LOG_FILE;
    static bool isExistLog();
    static void clearLog();
    static void createLog();
    static void appendLog(const char * text);
};

extern int Version;
