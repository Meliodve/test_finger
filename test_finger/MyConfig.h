#pragma once
#include <map>

// ������
class MyConfig{
private:
    // �������õĵط�
    std::map<std::string,MyString>m;
    // Ĭ������
    void defaultConfig();
public:
    void InitConfig();
    ~MyConfig();
    // ����[]������
    MyString& operator[](MyString s);
    // �ṩ�ַ�����ʾ
    static MyString Bool(bool b);
};

// ȫ��Ψһ����
extern MyConfig conf;