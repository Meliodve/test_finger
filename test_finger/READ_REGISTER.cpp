#include "stdafx.h"
#include "READ_REGISTER.h"

void READ_REGISTER_Listener::listen(DataPacket response){
    if(response.size()==0){
        MyLog.print(Log::LOGU,"�������ݳ�ʱ");
    } else{
        setText(editReadRegVal,MyString::Format("%X",response.getPointer()[0]));
        MyLog.print(Log::LOGU,"�������ݳɹ�");
    }
    sendMessage(WM_READ_REGISTER);
    updateControlDisable(actReadedReg);
}
