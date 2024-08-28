#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <rw/cstring.h>

#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_RspCatcher.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_CmdRspBuf.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_Indicator.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_CmdSender.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_EventHandler.H"
#include "../../../ops-enm-parser/target/ops_server/src/OPSS.H"
#include "../../../ops-enm-parser/target/ops_server/src/OPSC.H"

using namespace std;
using namespace testing;
using ::testing::AtLeast;
using ::testing::Mock;

class MockOPS: public POA_OPS::ServerRouterListener {
public:
    MOCK_METHOD1(showTimeInfo,void(::CORBA::Long _time));
};

class MockCHA_CommandSender:public CHA_CommandSender {
public:
    MOCK_METHOD2(sendCommand,ReturnCode(RWCString cmd, const RWCString& pmt));
};

class MockOZT_CmdSender: public OZT_CmdSender {
public:
    MockOZT_CmdSender(CHA_CommandSender *cms,OZT_CmdRspBuf &theCmdRspBuf,OZT_EventHandler *ozt_evt)
                       : OZT_CmdSender(cms,theCmdRspBuf,ozt_evt) {}
    MOCK_METHOD1(sendLogoff,OZT_Result(RWBoolean markBuf));
};

class MockOZT_EventHandler:public OZT_EventHandler
{
public:
    MOCK_METHOD1(setResult,void(OZT_Result));
};


TEST(OZT_RspCatcherTest,waitReply_INVALID_VALUE)
{
    OZT_CmdRspBuf cmdBuf;
    OZT_Indicator indictor;
    MockCHA_CommandSender *Mock_CHACS = new MockCHA_CommandSender();
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();
    MockOZT_CmdSender *Mock_CS = new MockOZT_CmdSender(Mock_CHACS,cmdBuf,Mock_EVT);

    RWCString const  timeSec = "-5";
    OZT_Value val(timeSec);
    OZT_RspCatcher objRC(NULL,cmdBuf,indictor,*Mock_CS);

    // unit under test
    OZT_Result result = objRC.waitReply(false,val);

    // assertion
    EXPECT_EQ(3, result.code);
    Mock::AllowLeak(Mock_EVT);
}

TEST(OZT_RspCatcherTest,waitReply_success)
{
    std::vector<std::string>rspBuf;
    rspBuf = {"This","is","For","Testing","Purpose"};
    OZT_CmdRspBuf cmdBuf(rspBuf);
    OZT_Indicator indictor;
    MockCHA_CommandSender *Mock_CHACS = new MockCHA_CommandSender();
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();
    MockOZT_CmdSender *Mock_CS = new MockOZT_CmdSender(Mock_CHACS,cmdBuf,Mock_EVT);

    RWCString const  timeSec = "5";
    OZT_Value val(timeSec);
    OZT_RspCatcher objRC(NULL,cmdBuf,indictor,*Mock_CS);
    objRC.setFailReply("");

    // unit under test
    OZT_Result result = objRC.waitReply(false,val);

    // assertion
    EXPECT_EQ(1, result.code);
    Mock::AllowLeak(Mock_EVT);
}


TEST(OZT_RspCatcherTest,waitFor_INVALID_VALUE)
{
    OZT_CmdRspBuf cmdBuf;
    OZT_Indicator indictor;
    MockCHA_CommandSender *Mock_CHACS = new MockCHA_CommandSender();
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();
    MockOZT_CmdSender *Mock_CS = new MockOZT_CmdSender(Mock_CHACS,cmdBuf,Mock_EVT);

    RWCString const  timeSec = "-5";
    OZT_Value val(timeSec);
    OZT_RspCatcher objRC(NULL,cmdBuf,indictor,*Mock_CS);
    OZT_Result result = objRC.waitFor("END","RESPONSE",false,val);

    // assertion
    EXPECT_EQ(OZT_Result::Code::INVALID_VALUE, result.code);
    Mock::AllowLeak(Mock_EVT);
}

TEST(OZT_RspCatcherTest,waitFor_success)
{
    std::vector<std::string>rspBuf;
    rspBuf = {"This","is","For","Testing","Purpose"};
    OZT_CmdRspBuf cmdBuf(rspBuf);
    OZT_Indicator indictor;
    MockCHA_CommandSender *Mock_CHACS = new MockCHA_CommandSender();
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();
    MockOZT_CmdSender *Mock_CS = new MockOZT_CmdSender(Mock_CHACS,cmdBuf,Mock_EVT);

    RWCString const  timeSec = "5";
    OZT_Value val(timeSec);
    OZT_RspCatcher objRC(NULL,cmdBuf,indictor,*Mock_CS);

    // unit under test
    OZT_Result result = objRC.waitFor("This","For",false,val);

    EXPECT_EQ(1, result.code);
    Mock::AllowLeak(Mock_EVT);
}

TEST(OZT_RspCatcherTest,waitFor_NULL_INPUT)
{
    std::vector<std::string>rspBuf;
    rspBuf = {"This","is","For","Testing","Purpose"};
    OZT_CmdRspBuf cmdBuf(rspBuf);
    OZT_Indicator indictor;
    MockCHA_CommandSender *Mock_CHACS = new MockCHA_CommandSender();
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();
    MockOZT_CmdSender *Mock_CS = new MockOZT_CmdSender(Mock_CHACS,cmdBuf,Mock_EVT);

    RWCString const  timeSec = "5";
    OZT_Value val(timeSec);
    OZT_RspCatcher objRC(NULL,cmdBuf,indictor,*Mock_CS);

    // unit under test
    OZT_Result result = objRC.waitFor("","",false,val);

    EXPECT_EQ(OZT_Result::Code::INVALID_VALUE, result.code);
    Mock::AllowLeak(Mock_EVT);
}
