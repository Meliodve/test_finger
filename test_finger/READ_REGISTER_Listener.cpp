#include "stdafx.h"
#include "READ_REGISTER_Listener.h"

void READ_REGISTER_Listener::listen(DataPacket response){
    if(response.len==0){
        MyLog.print(Log::LOGU,"�������ݳ�ʱ");
    } else{
        CString tmp;
        tmp.Format(_T("%X"),response.data[0]);
        editReadRegVal->SetWindowText(tmp);
        MyLog.print(Log::LOGU,"�������ݳɹ�");
    }
    updateControlDisable(actReadedReg);
}
