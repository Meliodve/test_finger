#pragma once
#include "MyDefine.h"

// ������߰汾
int NetGetVersion();
// ���ذ汾�ĺ���,����Ϊ��Ӧ�汾��ÿ�λ�����ݵĻص�����
void NetDownload(int NetVersion,_Function_t(void,uint8_t* data,int size,int total) func);
// ��ð汾��ϸ˵��
MyString NetVersionInfo(int NetVersion);
// �����Ƿ���������
bool isConnectedNet();