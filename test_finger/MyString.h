#pragma once
#include"stdafx.h"
#include<string>

//�������渴�ӵ��ַ���ת��

class MyString{
public:
    MyString(const char* pcc){
        str=pcc;
    }
    MyString(char* pc){
        str=pc;
    }
    MyString(wchar_t* pw){

    }
private:
    std::string str;
};