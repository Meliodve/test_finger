#include "stdafx.h"

//������λ����ť�ĵ���¼�
void MainDialog::OnBnClickedBtnconnect(){
    //���ݰ�ť�ϵ������жϵ�ǰ����״̬
    if(getText(btnConnect)=="������λ��"){
        if(getText(cmbWay)==""){
            return;
        }
        MainDialogCtrlValidity::Connecting();

        bool ret;
        if(getText(cmbWay)=="USB"){
            ret=comm.connect();
        } else{
            int baud=getInt(cmbBaud);//��ȡ������
            int com=(*idle)[idle->size()-cmbWay->GetCurSel()];
            ret=comm.connect(com,baud);
        }
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

void MainDialog::OnCbnSelchangeCmbbaud(){
    conf["Baud"]=MyString::Format("%d",cmbBaud->GetCurSel());
}

void MainDialog::OnCbnSelchangeCmbway(){
    if(getText(cmbWay)=="USB"){
        cmbBaud->EnableWindow(FALSE);
    } else{
        cmbBaud->EnableWindow(TRUE);
    }
}
