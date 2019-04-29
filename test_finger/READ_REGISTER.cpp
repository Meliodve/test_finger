#include "stdafx.h"
#include "READ_REGISTER.h"

void READ_REGISTER_Listener::listen(DataPacket response){
    if(response.size()==0){
        MyLog.print(Log::LOGU,"�������ݳ�ʱ");
    } else{
        CString tmp;
        tmp.Format(_T("%X"),response.getPointer()[0]);
        editReadRegVal->SetWindowText(tmp);
        MyLog.print(Log::LOGU,"�������ݳɹ�");
    }
    SendMessage(hwnd,WM_READ_REGISTER,WM_READ_REGISTER,0);
    updateControlDisable(actReadedReg);
}
