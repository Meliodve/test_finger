#pragma once
#include "MyString.h"
#include <afxwin.h>

// ���ؿؼ�������,������MyString
MyString getText(CWnd* pWnd);

// ���ÿؼ�������
void setText(CWnd* pWnd,MyString str);

// �ѿؼ��е����ݵ�ʮ���ƽ�������һ������
int getInt(CWnd* pWnd);

// �ѿؼ��е����ݵ�ʮ�����ƽ�������һ������
int getHex(CWnd* pWnd);

// ��filePath��ͼ����ص�ͼƬ�ؼ���
void loadImage(CStatic* image,MyString filePath);

// �����ѡЭ��
MyString getProtocol();
