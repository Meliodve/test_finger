#pragma once
#include "MyString.h"
#include "MyMsgQueue.h"

#define FastDeclearLogName(FuncName) \
static void FuncName(MyString info);\
static void FuncName(const char* format,...);

class MyLog{
public:
    enum LogLevel{
        LOGU,// �û�����Ϣ,���û���ʾ����Ϣ
        LOGE,// ������Ϣ
        LOGW,// ���漶��Ϣ
        LOGD,// ���Լ���Ϣ
        LOGT,// ��ʱ����Ϣ
        LOG_HIGHEST// ������,��Ҫɾ
    };
    // ���level��info
    static void print(LogLevel level,MyString info);
    // ���level��info(printf������)
    static void print(LogLevel level,const char* format,...);
    FastDeclearLogName(trace)
    FastDeclearLogName(debug)
    FastDeclearLogName(error)
    FastDeclearLogName(warn)
    FastDeclearLogName(user)
    // ���������־
    static void DevelopLog();
    // ׷����־����
    static void appendLog(const char * text);
    // ��Ϣ����
    static MyMsgQueue<MyString> MsgQueue;
};

// �汾��270=2.7,271=2.7.1
extern int Version;
