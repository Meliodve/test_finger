#include "stdafx.h"

// ��������
MyString::~MyString(){
    if(wstr)
        delete[] wstr;
}

// ���캯��Ⱥ
MyString::MyString(){
    str="";
    updateWstr();
}

MyString::MyString(const char* pcc){
    str=pcc;
    updateWstr();
}

MyString::MyString(std::string str){
    this->str=str;
    updateWstr();
}

MyString::MyString(char* pc){
    str=pc;
    updateWstr();
}

MyString::MyString(char * pc,int len){
    uint8_t b=pc[len];
    pc[len]=0;
    str=pc;
    updateWstr();
    pc[len]=b;
}

MyString::MyString(wchar_t* pw){
    int size=WideCharToMultiByte(CP_ACP,0,pw,-1,NULL,0,NULL,NULL);
    char* pc=new char[size];
    WideCharToMultiByte(CP_ACP,0,pw,-1,pc,size,NULL,NULL);
    str=pc;
    delete[] pc;
    updateWstr();
}

MyString::MyString(CString pCS){
    *this=MyString(pCS.GetBuffer(pCS.GetLength()));
}

MyString::MyString(MyString & other){
    str=other.str;
    updateWstr();
}

// ���캯��Ⱥ
MyString::MyString(MyString && other){
    str=other.str;
    updateWstr();
}

// ����sprintf
MyString MyString::Format(const char * format,...){
    static char tmp[1<<16];
    va_list ap;
    va_start(ap,format);
    vsprintf(tmp,format,ap);
    va_end(ap);
    return MyString(tmp);
}

// ����sscanf
void MyString::Parse(const char * format,...){
    va_list ap;
    va_start(ap,format);
    vsscanf(str.c_str(),format,ap);
    va_end(ap);
}

// ת��������
MyString::operator wchar_t*(){
    return wstr;
}

MyString::operator const char*(){
    return str.c_str();
}

MyString::operator const wchar_t*(){
    return wstr;
}

MyString::operator CString(){
    return CString(str.c_str());
}

// ���ع�ϵ������
bool MyString::operator==(MyString other){
    return str==other.str;
}

bool MyString::operator==(const char * other){
    return *this==MyString(other);
}

bool MyString::operator!=(MyString other){
    return !operator==(other);
}

bool MyString::operator!=(const char * other){
    return !operator==(other);
}

// �������Ӳ�����
MyString MyString::operator+(MyString other){
    MyString ret(*this);
    ret.str+=other.str;
    ret.updateWstr();
    return ret;
}

// ���ظ�ֵ������
MyString & MyString::operator=(MyString other){
    str=other.str;
    updateWstr();
    return *this;
}

// ���ؼӵȲ�����
MyString & MyString::operator+=(MyString other){
    return *this=*this+other;
}

// ���س���
int MyString::length(){
    return str.length();
}

// ���Һ���
int MyString::find(MyString beFound,int startPosition){
    return str.find(beFound.str,startPosition);
}

// intתMyString
MyString MyString::IntToMyString(int i){
    CString x;
    x.Format(_T("%d"),i);
    return x;
}

// MyStringתint
int MyString::ParseInt(MyString s){
    int ret;
    sscanf(s,"%d",&ret);
    return ret;
}

// ����ʱ���ַ���
MyString MyString::Time(const char * format){
    return CTime::GetCurrentTime().Format(format);
}

// ����str����wstr
void MyString::updateWstr(){
    if(wstr){
        delete[] wstr;
    }
    int size=MultiByteToWideChar(CP_ACP,0,str.c_str(),-1,NULL,0);
    wstr=new wchar_t[size];
    MultiByteToWideChar(CP_ACP,0,str.c_str(),-1,wstr,size);
}