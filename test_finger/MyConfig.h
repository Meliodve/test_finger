#pragma once
#include <map>

// ������
class MyConfig{
private:
    // �������õĵط�
    std::map<std::string,std::string>m;
    // Ĭ������
    void defaultConfig();
public:
    void InitConfig();
    ~MyConfig();
    // ����[]������
    std::string& operator[](std::string s);
    // �ṩ�ַ�����ʾ
    static std::string Bool(bool b);
};

// ȫ��Ψһ����
extern MyConfig conf;