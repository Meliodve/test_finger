#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest{

    TEST_CLASS(DataPacketUnitTest){
public:
    struct Mock{
        //���ݰ�
        uint8_t* data;
        //���ݰ�����
        int   len;
        //�Ѷ��ֽ���
        int   read;
    };
    Mock getMock(DataPacket packet){
        Mock ret;
        Assert::AreEqual(sizeof packet,12u);
        memcpy(&ret,&packet,sizeof packet);
        return ret;
    }
    DataPacket getPacket(Mock mock){
        DataPacket packet;
        Assert::AreEqual(sizeof packet,12u);
        memcpy(&packet,&mock,sizeof packet);
        return packet;
    }

    //�����޲ι��캯��
    TEST_METHOD(DataPacket1){
        DataPacket packet;
        Mock mock=getMock(packet);
        Assert::AreEqual(-1,mock.len);
        Assert::AreEqual(0,(int)mock.data);
        Assert::AreEqual(0,mock.read);
        packet.Destruction();
    }

    //�����вι��캯��
    TEST_METHOD(DataPacket2){
        char* str=new char[4];
        strcpy(str,"str");
        DataPacket packet(str,4);
        Mock mock=getMock(packet);
        Assert::AreEqual(4,mock.len);
        Assert::AreNotEqual((char*)mock.data,str);
        Assert::AreEqual(0,mock.read);
        Assert::AreEqual(0,strcmp((char*)mock.data,str));
        packet.Destruction();
        delete[] str;
    }

    };
}