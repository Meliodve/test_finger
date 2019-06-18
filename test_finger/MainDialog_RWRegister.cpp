#include "stdafx.h"

// ���Ĵ�������¼�
void MainDialog::OnBnClickedBtnReadReg(){
    if(getProtocol()==GD32){
        // ��������
        flow.clear();
        // ���� 0:����<���Ĵ���>ָ��
        flow.add(0,
            [](int& result){
                MainDialogCtrlValidity::Working();
                MyLog::debug("��ʼ���Ĵ���");
                uint8_t address=getHex(editReadRegAddr);
                comm.request(SII(ReadRegister),DataPacket(&address,1));
                setProgress(100*flow.percent());
                flow.next();
                return false;
            }
        );
        // ���� 1:���Ĵ�������,�ƺ���
        flow.add(1,
            [](int& result){
                MainDialogCtrlValidity::Work();
                setProgress(100*flow.percent());
                flow.clear();
                return false;
            }
        );
        // ��ʼִ������
        flow.start();
    }
}

// д�Ĵ�������¼�
void MainDialog::OnBnClickedBtnWriteReg(){
    if(getProtocol()==GD32){
        MainDialogCtrlValidity::Working();
        setProgress(50);
        MyLog::debug("��ʼд�Ĵ���");

        uint8_t addrVal[2];
        addrVal[0]=getHex(editWriteRegAddr);
        addrVal[1]=getHex(editWriteRegVal);
        // ����<д�Ĵ���>ָ��
        comm.request(SII(WriteRegister),DataPacket(addrVal,2));

        setProgress(100);
        MainDialogCtrlValidity::Work();
    }
}
