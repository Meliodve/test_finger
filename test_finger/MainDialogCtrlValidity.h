#pragma once
#include "stdafx.h"

// MainDialog�Ŀؼ�������
class MainDialogCtrlValidity{
public:
    // ����
    typedef std::vector<CWnd*> vec;
    // ��ʼ���ؼ�
    static void InitCtrl();
    // ��ʼ״̬
    static void Init(vec except=vec());
    // ������״̬
    static void Connecting(vec except=vec());
    // ������֮ǰ��״̬
    static void BeforeConnect(vec except=vec());
    // ����֮���״̬
    static void AfterConnect(vec except=vec());
    // ׼��̬
    static void Work(vec except=vec());
    // ����̬
    static void Working(vec except=vec());
private:
    // ���¿ؼ�������
    static void update(vec& dis,vec& en);
    // ���ÿؼ�
    static void disable(CWnd* pWnd);
    // ���ÿؼ�
    static void enable(CWnd* pWnd);
};
