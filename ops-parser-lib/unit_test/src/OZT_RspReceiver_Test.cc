#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_RspReceiver.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_CmdRspBuf.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_CmdSender.H"
#include "../../../ops-parser-lib/src/main/cpp/common/CHA_ResponseReceiver.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_EventHandler.H"

#include <rw/cstring.h>

using namespace testing;

TEST(OZT_RspRecieverTest,LogOn_True)
{
   OZT_CmdRspBuf cmdBuf;
   OZT_RspReceiver oz_Rsp(&cmdBuf,NULL,NULL,NULL);
   OZT_Result result = oz_Rsp.logOn();
   EXPECT_EQ(OZT_Result::Code::NO_PROBLEM, result.code);
}
TEST(OZT_RspRecieverTest,LogOn_FALSE)
{
   OZT_CmdRspBuf cmdBuf;
   OZT_RspReceiver oz_Rsp(&cmdBuf,NULL,NULL,NULL,FALSE);
   OZT_Result result = oz_Rsp.logOn();
   EXPECT_EQ(OZT_Result::Code::NO_PROBLEM, result.code);
}
TEST(OZT_RspRecieverTest,LogOFF)
{
    
   OZT_CmdRspBuf cmdBuf;
   OZT_RspReceiver oz_Rsp(&cmdBuf,NULL,NULL,NULL,FALSE);
   RWBoolean result = oz_Rsp.logOff();
   RWBoolean Expect_Result = FALSE;
   EXPECT_EQ(Expect_Result, result);

}
TEST(OZT_RspRecieverTest,LogOFF_WhenLogOnTrue_NEgative)
{
   OZT_CmdRspBuf cmdBuf;
   OZT_RspReceiver oz_Rsp(&cmdBuf,NULL,NULL,NULL); 
   RWBoolean result = oz_Rsp.logOff();
   RWBoolean Expect_Result = FALSE;
   EXPECT_EQ(Expect_Result, result);

}



TEST(OZT_RspRecieverTest,LogOFF_WhenLogOnTrue_Positive)
{
   OZT_CmdRspBuf cmdBuf;
   OZT_RspReceiver oz_Rsp(&cmdBuf,NULL,NULL,NULL,TRUE);
   RWBoolean result = oz_Rsp.logOff();
   RWBoolean Expect_Result = TRUE;
   EXPECT_EQ(Expect_Result, result);

}







