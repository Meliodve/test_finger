#include "stdafx.h"

//������λ����ť�ĵ���¼�
void MainDialog::OnBnClickedBtnconnect(){
    //���ݰ�ť�ϵ������жϵ�ǰ����״̬
    if(getText(btnConnect)=="������λ��"){
        MainDialogCtrlValidity::Connecting();

        bool ret;
        if(getText(cmbWay)=="USB"){
            ret=comm.connectUSB();
        } else{
            int com,baud=getInt(cmbBaud);//��ȡ������
            sscanf(getText(cmbWay),"COM%d",&com);//��ȡͨ�ŷ�ʽ
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
