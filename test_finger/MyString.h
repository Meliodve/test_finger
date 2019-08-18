#pragma once
#include<string>

// �������渴�ӵ��ַ���ת��

// �ַ���ģ��
class MyString{
public:
    // ��������
    ~MyString();
    // ���캯��Ⱥ
    MyString();
    MyString(char* pc);
    MyString(char* pc,int len);
    MyString(wchar_t* pw);
    MyString(CString pCS);
    MyString(const MyString& other);
    MyString(MyString&& other);
    MyString(const char* pcc);
    MyString(std::string str);

    // ����sprintf
    static MyString Format(const char* format,...);
    // ����ַ���������%s,������Format������
    template<class T>
    MyString Format(T arg);

    // ����sscanf
    void Parse(const char* format,...);

    // ת��������
    operator wchar_t*();
    operator const char*()const;
    operator const wchar_t*();
    operator CString();

    // ���ع�ϵ������
    bool operator==(const MyString other)const;
    bool operator==(MyString other);
    bool operator==(const char* other);
    bool operator!=(MyString other);
    bool operator!=(const char* other);

    // �������Ӳ�����
    MyString operator+(MyString other);

    // ���ظ�ֵ������
    MyString& operator=(MyString other);

    // ���ؼӵȲ�����
    MyString& operator+=(MyString other);

    const char operator[](int index);

    // ���س���
    int length();

    // ���Һ���
    int find(MyString beFound,int startPosition);

    // �滻����
    void replace(char oldChar,char newChar);

    // split����
    void split(char ch,std::vector<MyString>& out);

    const char* c_str();
    
    // intתMyString
    static MyString IntToMyString(int i);

    // MyStringתint
    static int ParseInt(MyString s);
    static int AutoParseInt(MyString s);

    // ����ʱ���ַ���
    static MyString Time(const char* format="%Y_%m_%d_%H_%M_%S");

private:
    // ʵ�ʴ洢���ݵ�std::string
    std::string str;
    // ���𷵻ؿ��ַ�
    wchar_t* wstr=0;
    // ����str����wstr
    void updateWstr();
};

template<class T>
inline MyString MyString::Format(T arg){
    static char tmp[1<<16];
    sprintf_s(tmp,*this,arg);
    return tmp;
}
