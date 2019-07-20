#pragma once
#include <stdio.h>
#include <functional>
#include "MyString.h"
#include "CommandDialog.h"

class MyFile{
public:
    typedef std::function<bool(FILE* fp)> ReturnFileFunction_t;
    typedef std::function<void(FILE* fp)> FileFunction_t;
private:
    static MyString CONF_PATH;
    static MyString DATA_DIR;
    static MyString LOG_DIR;
    // ����ʼ����ʱ��
    static MyString RUN_TIME;
    static MyString init();
    static bool OperateFile(MyString path,const char* mode,FileFunction_t f);
    static bool OperateFile(MyString path,const char * mode,ReturnFileFunction_t f);
public:
    static MyString IMAGE_DIR;
    static MyString BACKGROUND_DIR;
    static MyString HISTOGRAM_DIR;
    static MyString TEMP_IMAGE_PATH;
    static bool ReadConfig(FileFunction_t f);
    static bool WriteConfig(FileFunction_t f);
    static bool DownloadUpdate(int version,FileFunction_t f);
    static bool AppendLog(FileFunction_t f);
    static bool LogSaveAs(FileFunction_t f);
    static bool SaveImage(MyString fileName,FileFunction_t f);
    static bool SaveBGImg(MyString fileName,FileFunction_t f);
    static bool SaveTempImage(FileFunction_t f,int id=0);
    static bool HaveCommands(MyString path);
    static bool ReadCommands(MyString path,MyString& TabName,std::vector<struct Command>& v);
    static bool SaveDefaultPlugin1(MyString path);
    static bool SaveDefaultPlugin2(MyString path);
};
