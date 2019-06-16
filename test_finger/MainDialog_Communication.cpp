#include "stdafx.h"

// ������λ����ť�ĵ���¼�
void MainDialog::OnBnClickedBtnConnect(){
    // ���ݰ�ť�ϵ������жϵ�ǰ����״̬
    if(getText(btnConnect)=="������λ��"){
        if(getText(cmbWay)==""){
            return;
        }
        MainDialogCtrlValidity::Connecting();

        // ��ȡ���ںźͲ�����
        int com=getComID();
        int baud=getInt(cmbBaud);
        bool ret=comm.connect(com,baud);
        
        if(ret){
            setText(btnConnect,"�Ͽ�����");
            MainDialogCtrlValidity::AfterConnect();
        } else{
            MainDialogCtrlValidity::BeforeConnect();
        }
    } else{
        comm.disconnect();
        MainDialogCtrlValidity::BeforeConnect();
        setText(btnConnect,"������λ��");
    }
}

// ��������ʱ仯,���浽������
void MainDialog::OnCbnSelChangeCmbBaud(){
    conf["Baud"]=MyString::Format("%d",cmbBaud->GetCurSel());
}

// ���ͨ�ŷ�ʽѡ����USB�ͰѲ�����ѡ�����
void MainDialog::OnCbnSelChangeCmbWay(){
    if(getText(cmbWay)=="USB"){
        cmbBaud->EnableWindow(FALSE);
    } else{
        cmbBaud->EnableWindow(TRUE);
    }
}
