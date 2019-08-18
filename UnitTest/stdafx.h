// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once
#include "targetver.h"

// ���� CppUnitTest ��ͷ�ļ�
#include "CppUnitTest.h"

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#define private public
#include "../test_finger/stdafx.h"
#undef private

#include "TestDataLoader.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define CHECK_SEND \
for(uint32_t i=0;i<CHECK_Send.size();i++){\
    Assert::AreEqual(CHECK_Send[i],test.commTest.Comm_send[i]);\
}

#define TEST_RECEIVE \
for(uint32_t i=0;i<TEST_Receive.size();i++){\
    test.commTest.Comm_receive[i]=TEST_Receive[i];\
}\
bool process=false;\
flow.clear();\
flow.add(0,\
    [&](int& result)->bool{\
        process=true;\
        flow.clear();\
        return false;\
    }\
);\
flow.jump(0);\
test.commTest.Comm_receiveSize=TEST_Receive.size();\
while(!process);

#define CHECK_RECEIVE \
Assert::AreEqual(CHECK_Receive.size(),test.myTest.My_logs.size());\
for(uint32_t i=0;i<CHECK_Receive.size();i++){\
    Assert::AreEqual((std::string)CHECK_Receive[i],(std::string)test.myTest.My_logs[i]);\
}
