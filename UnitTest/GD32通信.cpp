#include "stdafx.h"

namespace IntegrationTest{

    TEST_CLASS(GD32CommTest){
public:
    TEST_CLASS_INITIALIZE(init){
        conf.InitConfig();
        comm.setBlock(false);
    }

    //≤‚ ‘ReadRegister
    TEST_METHOD(ReadRegister){
        test.testBegin(test.Comm|test.UI|test.My,GD32);
        TestDataLoader loader(__FUNCTION__);
        comm.connect(0,0);
        auto TEST_Send=loader.ReadByteSection("TEST Send");
        auto CHECK_Send=loader.ReadByteSection("CHECK Send");
        auto TEST_Receive=loader.ReadByteSection("TEST Receive");
        auto CHECK_Receive=loader.ReadStrSection("CHECK Receive");
        // TEST Send
        comm.request(SII(ReadRegister),DataPacket(TEST_Send));
        while(!test.commTest.Comm_sendSize);
        CHECK_SEND;
        TEST_RECEIVE;
        CHECK_RECEIVE;
        Assert::AreEqual(75,test.uiTest.UI_progress);
        Assert::AreEqual("2",test.myTest.My_CtrlSet[0].second);
        test.testEnd();
    }

    //≤‚ ‘WriteRegister
    TEST_METHOD(WriteRegister){
        test.testBegin(test.Comm|test.UI,GD32);
        TestDataLoader loader(__FUNCTION__);
        comm.connect(0,0);
        auto TEST_Send=loader.ReadByteSection("TEST Send");
        auto CHECK_Send=loader.ReadByteSection("CHECK Send");
        // TEST Send
        comm.request(SII(WriteRegister),DataPacket(TEST_Send));
        while(!test.commTest.Comm_sendSize);
        CHECK_SEND;
        test.testEnd();
    }

    TEST_METHOD(GetRawImage){
        test.testBegin(test.Comm|test.UI|test.My,GD32);
        TestDataLoader loader(__FUNCTION__);
        comm.connect(0,0);
        auto CHECK_Send=loader.ReadByteSection("CHECK Send");
        auto TEST_Receive=loader.ReadByteSection("TEST Receive");
        auto CHECK_Receive=loader.ReadStrSection("CHECK Receive");
        // TEST Send
        comm.request(SII(GetRawImage));
        while(!test.commTest.Comm_sendSize);
        CHECK_SEND;
        TEST_RECEIVE;
        CHECK_RECEIVE;
        Assert::AreEqual(100,test.uiTest.UI_progress);
        test.testEnd();
    }

    TEST_METHOD(GetTestImage){
        test.testBegin(test.Comm|test.UI|test.My,GD32);
        TestDataLoader loader(__FUNCTION__);
        comm.connect(0,0);
        auto CHECK_Send=loader.ReadByteSection("CHECK Send");
        auto TEST_Receive=loader.ReadByteSection("TEST Receive");
        auto CHECK_Receive=loader.ReadStrSection("CHECK Receive");
        // TEST Send
        comm.request(SII(GetTestImage));
        while(!test.commTest.Comm_sendSize);
        CHECK_SEND;
        TEST_RECEIVE;
        CHECK_RECEIVE;
        Assert::AreEqual(100,test.uiTest.UI_progress);
        test.testEnd();
    }

    };
}