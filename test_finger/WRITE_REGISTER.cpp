#include "stdafx.h"
#include "WRITE_REGISTER.h"

void WRITE_REGISTER_Listener::listen(DataPacket response){
    MyLog.print(Log::LOGU,"�޸ļĴ�������ͳɹ�");
    updateControlDisable(actWritedReg);
}
