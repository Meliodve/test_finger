#include "stdafx.h"

// Э��䶯�¼�
void MainDialog::OnCbnSelChangeCmbProtocolType(){
    // ��������
    conf["ProtocolType"]=MyString::Format("%d",cmbProtocolType->GetCurSel());
    // �������ÿؼ�������
    MainDialogCtrlValidity::Work();
    // ���ô�������̬
    if(getText(cmbProtocolType)==SYNO){
        comm.setBlock(true);
    } else{
        comm.setBlock(false);
    }
}

// �߼�����ģʽ����¼�
void MainDialog::OnBnClickedBtnAdvDbg(){
    if(advancedDebugDialog){
        delete advancedDebugDialog;
        advancedDebugDialog=0;
    } else{
        advancedDebugDialog=new AdvancedDebugDialog();
        advancedDebugDialog->Create(IDD_ADVANCED_DEBUG_DIALOG,this);
        advancedDebugDialog->ShowWindow(SW_SHOW);
    }
}
