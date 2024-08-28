#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_CmdSender.H"
#include "../../src/main/cpp/cmd/CHA_CommandSender.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_CmdRspBuf.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_EventHandler.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_Clock.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_Value.H"

using namespace std;
using namespace testing;

class MockCHA_CommandSender:public CHA_CommandSender { 
public:
    MOCK_METHOD2(sendCommand,ReturnCode(RWCString cmd, const RWCString& pmt));
};

class MockOZT_EventHandler:public OZT_EventHandler
{
public:
    MOCK_METHOD3(setIOTrigger,void(void *,int (*func)(void *),int));
    MOCK_METHOD1(setResult,void(OZT_Result));   
    MOCK_METHOD1(waitResult,OZT_Result(RWBoolean));
    MOCK_METHOD3(setSigChdTrigger,void(void *,pid_t, int (*func)(void *,pid_t,int *)) );
};

TEST(OZT_CommandSender_Test,sendCommandNULL)
{
    MockCHA_CommandSender *Mock_CS = new MockCHA_CommandSender();
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();
    OZT_CmdRspBuf cmpbuf;
    OZT_CmdSender ocms(Mock_CS,cmpbuf,NULL);

    OZT_Result result =   ocms.sendCmd("File_ABCD","",TRUE);
    EXPECT_EQ(OZT_Result::Code::NO_PROBLEM, result.code);
}

TEST(OZT_CommandSender_Test,FileNameNULL)
{
    MockCHA_CommandSender *Mock_CS = new MockCHA_CommandSender();
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();
    OZT_CmdRspBuf cmpbuf;
    OZT_CmdSender ocms(Mock_CS,cmpbuf,NULL);

    OZT_Result result =   ocms.sendCmd("","caclp;",TRUE);
    EXPECT_EQ(40, result.code);
}

TEST(OZT_CommmandSender_Test,delayFail)
{
    MockCHA_CommandSender *Mock_CS = new MockCHA_CommandSender();
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();
    OZT_CmdRspBuf cmpbuf;
    RWCString const  timeMin = "123A568";
    OZT_CmdSender ocms(Mock_CS,cmpbuf,NULL);
    OZT_Value val(timeMin);
    OZT_Clock clk(NULL,ocms);

    OZT_Result result = clk.delay(val);
    EXPECT_EQ(3, result.code);
    
}
TEST(OZT_CommmandSender_Test,delayPass)
{
    MockCHA_CommandSender *Mock_CS = new MockCHA_CommandSender();
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();
    OZT_CmdRspBuf cmpbuf;
    RWCString const  timeMin = "1";
    OZT_CmdSender ocms(Mock_CS,cmpbuf,NULL);
    OZT_Value val(timeMin);   
    OZT_Clock clk(NULL,ocms);
    clk.setDelayInterrupt(FALSE);

    OZT_Result result = clk.delay(val);
    EXPECT_EQ(1, result.code);
    
}
TEST(OZT_CommmandSender_Test,delaySecFail)
{
    MockCHA_CommandSender *Mock_CS = new MockCHA_CommandSender();
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();
    OZT_CmdRspBuf cmpbuf;
    RWCString const  timeSec = "123A568";
    OZT_CmdSender ocms(Mock_CS,cmpbuf,NULL);
    OZT_Value val(timeSec);
    OZT_Clock clk(NULL,ocms);

    OZT_Result result = clk.delaySec(val);
    EXPECT_EQ(3, result.code);
    
}
TEST(OZT_CommmandSender_Test,delaysecPass)
{
    MockCHA_CommandSender *Mock_CS = new MockCHA_CommandSender();
    MockOZT_EventHandler *Mock_EVT = new MockOZT_EventHandler();
    OZT_CmdRspBuf cmpbuf;
    RWCString const  timeSec = "1";
    OZT_CmdSender ocms(Mock_CS,cmpbuf,NULL);
    OZT_Value val(timeSec);
    OZT_Clock clk(NULL,ocms);
    clk.setDelayInterrupt(FALSE);

    OZT_Result result = clk.delaySec(val);
    EXPECT_EQ(1, result.code);
    
}
TEST(OZT_CmdRspBuf_Test,reply_Pass)
{
    std::vector<std::string>  rspBuf;
    rspBuf = {"This","is","For","Testing","Purpose"};
    OZT_CmdRspBuf cmpbuf(rspBuf);
    size_t const val = 3;

    RWCString response = cmpbuf.reply(val);
    RWCString my_response = "Purpose";
    EXPECT_EQ(my_response,response);
}
TEST(OZT_CmdRspBuf_Test,reply_CornerTest)
{
    std::vector<std::string>  rspBuf;
    rspBuf = {"This","is","For","Testing","Purpose"};
    OZT_CmdRspBuf cmpbuf(rspBuf);
    size_t const val = 1;

    RWCString response = cmpbuf.reply(val);
    RWCString my_response = "For";
    EXPECT_EQ(my_response,response);
}
TEST(OZT_CmdRspBuf_Test,reply_SingleStore)
{
    std::vector<std::string>  rspBuf;
    rspBuf = {"Testing"};
    OZT_CmdRspBuf cmpbuf(rspBuf);
    size_t const val = 1;

    RWCString response = cmpbuf.reply(val);
    RWCString my_response = "";
    EXPECT_EQ(my_response,response);
}
TEST(OZT_CmdRspBuf_Test,reply_NegativeValue)
{
    std::vector<std::string>  rspBuf;
    rspBuf = {"This","is","For","Testing","Purpose"};
    OZT_CmdRspBuf cmpbuf(rspBuf);
    size_t const val = -2;

    RWCString response = cmpbuf.reply(val);
    RWCString my_response = "";
    EXPECT_EQ(my_response,response);
}
TEST(OZT_CmdRspBuf_Test,reply_InvalidValue)
{
    std::vector<std::string>  rspBuf;
    rspBuf = {"This","is","For","Testing","Purpose"};
    OZT_CmdRspBuf cmpbuf(rspBuf);
    size_t const val = 10;

    RWCString response = cmpbuf.reply(val);
    RWCString my_response = "";
    EXPECT_EQ(my_response,response);
}
TEST(OZT_CmdRspBuf_Test,reply_EmptyStore)
{
    std::vector<std::string>  rspBuf;
    OZT_CmdRspBuf cmpbuf(rspBuf);
    size_t const val = 2;

    RWCString response = cmpbuf.reply(val);
    RWCString my_response = "";
    EXPECT_EQ(my_response,response);
}
TEST(OZT_CmdRspBuf_Test,replyLen_Pass)
{
    std::vector<std::string>  rspBuf;
    size_t mark = 2;
    rspBuf = {"This","is","For","Testing","Purpose"};
    OZT_CmdRspBuf cmpbuf(rspBuf);

    size_t response = cmpbuf.replyLen();
    size_t my_response = rspBuf.size()-mark;
    EXPECT_EQ(my_response,response);
}
TEST(OZT_CmdRspBuf_Test,replyLen_EmptyStore)
{
    std::vector<std::string>  rspBuf;
    size_t mark = 2;
    OZT_CmdRspBuf cmpbuf(rspBuf);

    size_t response = cmpbuf.replyLen();
    size_t my_response = rspBuf.size()-mark;
    EXPECT_EQ(my_response,response);
}
