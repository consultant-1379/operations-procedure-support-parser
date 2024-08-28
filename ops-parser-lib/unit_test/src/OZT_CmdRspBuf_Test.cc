#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <rw/cstring.h>

#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_CmdRspBuf.H"
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

class MockOZT_CmdRspBuf:public OZT_CmdRspBuf {
public:
    MockOZT_CmdRspBuf() {}
};

class MockOZT_EventHandler:public OZT_EventHandler
{
public:
    MOCK_METHOD1(setResult,void(OZT_Result));
};


TEST(OZT_CmdRspBufTest,checkReply_WITH_FUNBUSY)
{
    const RWCString testString = "NOT ACCEPTED";
    MockOZT_CmdRspBuf cmdBuf;
    std::vector<std::string>  test = {"This","is","NOT ACCEPTED","FUNCTION BUSY","Purpose"};
    cmdBuf.MarksetterTest(test);
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();


    // unit under test
    size_t pos = 0;
    size_t retVal = cmdBuf.scan(testString,pos,pos);
    // assertion
    EXPECT_EQ(-1, retVal);
    Mock::AllowLeak(Mock_EVT);
}
TEST(OZT_CmdRspBufTest,checkReply_WITHOUT_FUNBUSY)
{
    const RWCString testString = "NOT ACCEPTED";
    MockOZT_CmdRspBuf cmdBuf;
    std::vector<std::string>  test = {"This","is","NOT ACCEPTED","COMMAND UNKNOWN","Purpose"};
    cmdBuf.MarksetterTest(test);
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();


    // unit under test
    size_t pos = 0;
    size_t retVal = cmdBuf.scan(testString,pos,pos);
    // assertion
    EXPECT_EQ(3, retVal);
    Mock::AllowLeak(Mock_EVT);
}
