#pragma once
#include "MyString.h"

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
    // LOGT��print
    static void trace(MyString info);
    // LOGT��print
    static void trace(const char* format,...);
    // LOGD��print
    static void debug(MyString info);
    // LOGD��print
    static void debug(const char* format,...);
    // LOGE��print
    static void error(MyString info);
    // LOGE��print
    static void error(const char* format,...);
    // LOGW��print
    static void warn(MyString info);
    // LOGW��print
    static void warn(const char* format,...);
    // LOGU��print
    static void user(MyString info);
    // LOGU��print
    static void user(const char* format,...);
    // ���������־
    static void DevelopLog();
    // �����־��
    static void ClearLog();
private:
    // ��־����λ��
    static const char* LOG_FILE;
    // �Ƿ��Ѿ�������־�ļ�
    static bool isExistLog();
    // ɾ����־�ļ�
    static void clearLog();
    // ������־�ļ�
    static void createLog();
    // ׷����־����
    static void appendLog(const char * text);
};

// �汾��270=2.7,271=2.7.1
extern int Version;
