#include "stdafx.h"

// ȫ��Ψһ����
MyConfig conf;

void setDefault(std::map<std::string,std::string>& m,const char* key,const char* val,bool give,bool cond=true){
    if(give||!m.count(key)){
        if(cond){
            m[key]=val;
        }
    }
}

// Ĭ������
void MyConfig::defaultConfig(){
    if(!m.count("SaveConf")){
        m["SaveConf"]=Stringify(false);
    }
    // ��SaveConfΪfalse,����Ĭ������
    bool give=m["SaveConf"]==Stringify(false);

    setDefault(m,"CustomCnt","0",give);
    setDefault(m,"AdvDbg",Stringify(false),give);
    setDefault(m,"AutoCheck",Stringify(true),give);
    setDefault(m,"AutoLog",Stringify(true),give);
    setDefault(m,"RemBaud",Stringify(true),give);
    setDefault(m,"RemProtocol",Stringify(true),give);
    setDefault(m,"Baud","2",give,m["RemBaud"]==Stringify(true));
    setDefault(m,"ProtocolType","0",give,m["RemProtocol"]==Stringify(true));
    setDefault(m,"ImgSize","160",give);
    return;
}

// ��ʼ�������Ǵ��ļ��ж�ȡ����
void MyConfig::InitConfig(){
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
                sscanf_s(buffer+c,"%[^`]`%[^`]`%n",key,sizeof key,val,sizeof val,&n);
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
                    if(it->second==""){
                        continue;
                    }
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
