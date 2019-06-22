#include "stdafx.h"

// ȫ��Ψһ����
MyConfig conf;

// Ĭ������
void MyConfig::defaultConfig(){
    if(!m.count("SaveConf")){
        m["SaveConf"]=Stringify(false);
    }
    // ��SaveConfΪfalse,����Ĭ������
    bool give=m["SaveConf"]==Stringify(false);

    if(give||!m.count("AdvDbg")){
        m["AdvDbg"]=Stringify(false);
    }
    if(give||!m.count("AutoCheck")){
        m["AutoCheck"]=Stringify(true);
    }
    if(give||!m.count("AutoLog")){
        m["AutoLog"]=Stringify(true);
    }
    if(give||!m.count("RemBaud")){
        m["RemBaud"]=Stringify(true);
    }
    if(give||!m.count("RemProtocol")){
        m["RemProtocol"]=Stringify(true);
    }
    if(give||!m.count("Baud")){
        if(m["RemBaud"]==Stringify(true)){
            m["Baud"]="2";
        }
    }
    if(give||!m.count("ProtocolType")){
        if(m["RemProtocol"]==Stringify(true)){
            m["ProtocolType"]="0";
        }
    }
    return;
}

// ���캯���Ǵ��ļ��ж�ȡ����
MyConfig::MyConfig(){
    MyFile::ReadConfig(
        [&](FILE* fp){
            char buffer[1<<16],key[1<<6],val[1<<6];
            char* p=buffer;
            // һ����ȫ��ȡ������
            while((*p++=-fgetc(fp))!=-EOF);
            // �������,������Ϊ�˽����ַ���
            *--p=0;
            int n,c=0;
            while(buffer[c]){
                sscanf(buffer+c,"%[^`]`%[^`]`%n",key,val,&n);
                c+=n;
                m[key]=val;
            }
        }
    );
    defaultConfig();
}

// ���������ǰ�����д���ļ���
MyConfig::~MyConfig(){
    if(m["SaveConf"]==Stringify(true)){
        MyFile::WriteConfig(
            [&](FILE* fp){
                for(auto it=m.begin();it!=m.end();it++){
                    for(auto jt=it->first.c_str();*jt;jt++){
                        fputc(-*jt,fp);
                    }
                    fputc(-'`',fp);
                    for(auto jt=it->second.c_str();*jt;jt++){
                        fputc(-*jt,fp);
                    }
                    fputc(-'`',fp);
                }
            }
        );
    }
}

// ��map<string,string>һ��,���������ַ���,ֵ����Ҳ���ַ���
std::string& MyConfig::operator[](std::string s){
    return m[s];
}

std::string MyConfig::Bool(bool b){
    return b?Stringify(true):Stringify(false);
}
