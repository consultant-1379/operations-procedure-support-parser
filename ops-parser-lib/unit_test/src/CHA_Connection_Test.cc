#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <grpcpp/client_context.h>
#include <limits.h>
#include <fstream>
#include <string> 
#include <iostream>
#include <list>
#include <memory>
#include <rw/cstring.h>

#include "../../src/main/cpp/cmd/CHA_Connection.H"
#include "../../src/main/cpp/cmd/CHA_CommandSender.H"
#include "../../src/main/cpp/common/CHA_Model.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OPSLogger.H"
#include "../../src/main/cpp/cmd/WinFIOLClient.H"
#include "../../../ops-parser-lib/src/main/cpp/common/CHA_Pipe.H"
#include "../../..//src/main/cpp/common/CHA_Pipe.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_Pipe.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_CmdRspBuf.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_ErrHandling.H"
#include "../../../ops-enm-parser/src/main/cpp/parse/OZT_EventHandler.H"

using namespace std;
using namespace testing;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;
using grpc::ClientContext;

class MockCHA_Pipe:public CHA_Pipe
{
public:
    MockCHA_Pipe(const RWCString& a,RWBoolean doDetach = FALSE):CHA_Pipe(a,FALSE){}
    MOCK_METHOD0(status,PipeStatus());
    MOCK_METHOD0(getReceiveDescriptor,int());
};

class MockOZT_EventHandler:public OZT_EventHandler
{
public:
    MockOZT_EventHandler():OZT_EventHandler(){}
};

TEST(CHA_Connection_Test,Connection_NOT_EXIST_Trying_TODisconnect)
{
    WinFIOLClient *wfc = new WinFIOLClient();
    CHA_CommandSender *cs = new  CHA_CommandSender();
    CHA_Connection  cc(wfc,cs);

    EXPECT_EQ(0,cc.disconnect(TRUE));
}

TEST(CHA_Pipe_Test,EXECUTE_SUCC_CASE)
{
    RWCString const a ="ls",b="Successful";
    OZT_Result ozr;
    MockCHA_Pipe  *mcp = new MockCHA_Pipe("/bin/sh",FALSE);
    MockOZT_EventHandler evnt; 
    OZT_CmdRspBuf cmpbuf;
    OZT_Pipe ozp(mcp,cmpbuf,&evnt);
    OZT_Result result(OZT_Result::NO_PROBLEM);
    OZT_Result result1(OZT_Result::STOP);

    ozr = ozp.execute(a);
    EXPECT_EQ(b,ozr.toMsg()) ;
}

TEST(CHA_Pipe_Test,EXECUTE_FAILED_CASE)
{
    RWCString const a ="abcd" , b = "Cannot Execute External Program";
    OZT_Result ozr;
    MockCHA_Pipe  *mcp = new MockCHA_Pipe("/bin/sh",FALSE);
    MockOZT_EventHandler evnt; 
    OZT_CmdRspBuf cmpbuf;
    OZT_Pipe ozp(mcp,cmpbuf,&evnt);
    OZT_Result result(OZT_Result::EXECUTE_ERR);
    OZT_Result result1(OZT_Result::STOP);

    ozr = ozp.execute(a);
    EXPECT_EQ(b,ozr.toMsg());
}
