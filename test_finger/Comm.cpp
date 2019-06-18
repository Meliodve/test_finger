#include "stdafx.h"

std::vector<MyThread*> blockQueue;
int CommType;
Comm comm;

Comm::Comm(){
    this->block=false;
    this->id=CommType=-1;

    // ��������������ϻ�һֱ��,�����ǵ��߳�ʹ��,������static��
    static uint8_t buffer[1<<16];

    // ����dataQueue(Packet������)����
    static MyLocker dataQueueMutex;

    // Packet������
    static std::queue<DataPacket> dataQueue;

    // ���������λ��������,��Packet��������
    this->listenThread=new MyThread(
        [&](){
            while(this->isOpen()){
                ULONG cnt;
                if(this->readBytes(buffer,sizeof buffer,cnt)){
                    cnt=max(cnt,sizeof buffer);
                    dataQueue.push(DataPacket(buffer,cnt));
                    dataQueueMutex.unlock();
                }
            }
            return 0;
        }
    );

    // ����ַ�Packet����Ӧ��Listener,��Packet��������
    this->responseThread=new MyThread(
        [&](){
            DataPacket dataPacket;
            while(1){
                // ���ڷ��ʻ�����������
                dataQueueMutex.lock();

                // ��ͨ�����������Ѿ���������
                if(dataQueue.size()){
                    dataPacket=dataQueue.front();
                    dataQueue.pop();
                }
                while(dataPacket.isValid()){
                    // ���������ݰ�������ָ��
                    int cmdCode=converterBoardcast.ResponseGetCmdCode(dataPacket);

                    // cmdCode==-1����û��Э�����ת��ʣ�µ�������,���ݷ���
                    if(cmdCode==-1){
                        break;
                    }

                    // ���������ݰ�����������
                    DataPacket data=converterBoardcast.ResponseConvert(dataPacket);

                    // ����ָ������ݽ��й㲥
                    listenerBoardcast.boardcast(cmdCode,data);
                    data.Destruction();
                }
                dataPacket.Destruction();
                if(this->block){
                    this->blockLocker.unlock();
                }
            }
        }
    );
}

// ���ID
int Comm::getConnectId(){
    return this->id;
}

// ����request��������ʽ,�����Ļ�,�յ���Ӧ֮���ټ�����
void Comm::setBlock(bool block){
    this->block=block;
}

// ����λ����������(����)
void Comm::request(int cmdCode,DataPacket packet){
    blockQueue.push_back(new MyThread(
        [=](){
            // ��cmdCode��packet������ѡЭ����ת��Ϊ��Ӧ��ʽ
            auto converter=converterBoardcast.RequestConvert();
            if(converter){
                // ת��Ϊ����õ�Packet
                auto dataPacket=converter->convert(cmdCode,packet.getPointer(),packet.size());
                for(auto it=dataPacket.begin();it!=dataPacket.end();it++){
                    this->sendBytes(it->getPointer(),it->size());
                    it->Destruction();
                }
            } else{
                // �Ҳ���Converter?
                ASF_ERROR(3);
            }
        },true
    ));
    (new MyThread(
        [=](){
            if(this->block){
                this->blockLocker.lock();
            }
            blockQueue.back()->start();
            blockQueue.pop_back();
        },true
    ))->start();
}

// �����豸�Ƿ��
bool Comm::isOpen(){
    if(test.isTest(test.Comm)){
        return true;
    }
    if(this->id>0){
        return this->serial.IsOpen();
    } else{
        return this->id==0;
    }
}

// ���豸�����ֽ���
void Comm::sendBytes(uint8_t * data,int len){
    if(!this->isOpen()){
        return;
    }
    if(test.isTest(test.Comm)){
        memcpy(test.commTest.Comm_send,data,len);
        test.commTest.Comm_sendSize=len;
        return;
    }
    if(this->id==0){
        BYTE cdb_w[16]={0xef,0x01};
        this->usb.USBSCSIWrite(cdb_w,IOCTRL_CDB_LEN,data,len,SCSI_TIMEOUT);
    } else{
        this->serial.Write(data,len);
    }
}

// ���豸�ж�ȡ�ֽ���,�����Ƿ��������
bool Comm::readBytes(uint8_t* buffer,int blen,ULONG& cnt){
    if(!this->isOpen()){
        return false;
    }
    if(test.isTest(test.Comm)){
        if(test.commTest.Comm_receiveSize>0){
            cnt=test.commTest.Comm_receiveSize;
            memcpy(buffer,test.commTest.Comm_receive,cnt);
            test.commTest.Comm_receiveSize=0;
            return true;
        }
        return false;
    }
    if(this->id==0){
        BYTE cdb_r[16]={0xef,0x02};
        return this->usb.USBSCSIRead(cdb_r,IOCTRL_CDB_LEN,buffer,blen,cnt,SCSI_TIMEOUT);
    } else{
        return this->serial.Read(buffer,blen,&cnt)==ERROR_SUCCESS;
    }
}

// ������λ��
bool Comm::connect(int id,int baud){
    if(test.isTest(test.Comm)){
        this->responseThread->start();
        this->listenThread->start();
        return true;
    }
    // USB��ʽ����
    if(id==0){
        int ret=this->usb.InitUsbPort(COMM_USB_MASS,"UD");
        if(ret!=-1){
            MyLog::user("����USB�ɹ�");
            this->id=CommType=COMM_USB_MASS;
            this->responseThread->start();
            this->listenThread->start();
        } else{
            MyLog::user("����USBʧ��(ע��,����USB��Ҫ����ԱȨ��)");
            this->id=CommType=-1;
        }
        return ret!=-1;
    }
    // ���ڷ�ʽ����

    // ����˿ڵ�ַ
    MyString way=MyString::Format("\\\\.\\COM%d",id);
    LONG retCode=ERROR_SUCCESS;
    if(retCode==ERROR_SUCCESS){ retCode=this->serial.Open(way,2048,2048,true); }
    if(retCode==ERROR_SUCCESS){ retCode=this->serial.Setup((CSerial::EBaudrate)baud); }
    if(retCode==ERROR_SUCCESS){ retCode=this->serial.SetMask(CSerial::EEventRecv); }
    if(retCode==ERROR_SUCCESS){ retCode=this->serial.SetupReadTimeouts(CSerial::EReadTimeoutNonblocking); }
    if(retCode==ERROR_SUCCESS){ this->serial.Purge(); }
    if(retCode==ERROR_SUCCESS){
        this->responseThread->start();
        this->listenThread->start();
        this->id=id;
        MyLog::user("����COM%d�ɹ�",id);
    } else{
        MyLog::user("����COM%dʧ��",id);
    }
    return retCode==ERROR_SUCCESS;
}

// �Ͽ�����λ��������
bool Comm::disconnect(){
    if(test.isTest(test.Comm)){
        this->responseThread->terminate();
        this->listenThread->terminate();
        return true;
    }
    if(this->id<0){
        return true;
    }
    this->responseThread->terminate();
    this->listenThread->terminate();
    // ����id���ж��Ǵ��ڻ���USB
    int ret=ERROR_SUCCESS;
    if(this->id==0){
        ret=this->usb.CloseUsbPort();
    } else{
        ret=this->serial.Close();
    }
    MyLog::user("�Ͽ����ӳɹ�");
    if(ret==ERROR_SUCCESS){
        this->id=CommType=-1;
        return true;
    } else{
        ASF_WARNING(5);
        return false;
    }
}
