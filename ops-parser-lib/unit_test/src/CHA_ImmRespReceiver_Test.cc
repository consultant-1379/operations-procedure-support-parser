#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "../../src/main/cpp/cmd/CHA_ImmRespReceiver.H"
#include "../../src/main/cpp/cmd/CHA_PromptString.H"

using namespace std;
using namespace testing;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;

class MockCHA_ImmRespReceiver : public CHA_ImmRespReceiver {
public:
    MockCHA_ImmRespReceiver(): CHA_ImmRespReceiver() {}
    MOCK_METHOD2(readBuffers, void (RWBoolean, RWBoolean));
};

class MockWinfiolClient : public WinFIOLClient {
public:
   MOCK_METHOD0(getResponsedata,std::string());
};

TEST(CHA_ImmRespReceiver_Test, updateFrom)
{
    MockCHA_ImmRespReceiver objImmResp;

    objImmResp.updateFrom(0,0);
}

TEST(CHA_ImmRespReceiver_Test, detachFrom)
{
    MockCHA_ImmRespReceiver objImmResp;

    objImmResp.detachFrom(0);
}

TEST(CHA_ImmRespReceiver_Test, newCommand)
{
    MockCHA_ImmRespReceiver objImmResp;
    MockWinfiolClient mWinF;

    EXPECT_EQ( 0, objImmResp.newCommand(&mWinF));
}

TEST(CHA_ImmRespReceiver_Test, receiveResponse_success)
{
    MockCHA_ImmRespReceiver objImmResp;
    MockWinfiolClient mWinF;
    EXPECT_CALL(mWinF, getResponsedata()).WillRepeatedly(Return(""));


    CHA_ImmRespReceiver::ReturnCode result = objImmResp.receiveResponse(&mWinF);
    EXPECT_EQ(result,CHA_ImmRespReceiver::ReturnCode::FAILED);
}

TEST(CHA_ImmRespReceiver_Test, cancelResponse)
{
    MockCHA_ImmRespReceiver objImmResp;

    objImmResp.cancelResponse();
}
