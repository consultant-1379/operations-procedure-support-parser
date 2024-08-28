#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>
#include <sstream>

#include "../../src/main/cpp/cmd/WinFIOLDriver.H"
#include "../../src/main/cpp/cmd/WinFIOLClient.H"

using namespace std;
using namespace testing;
using ::testing::AtLeast;
using grpc::Status;
using grpc::StatusCode;
using winfiolAxeMed::ConnectRequest;

enum connection_Errors
{           
        Okay = 0,
        Invalid_NEID  = 2,	
        Syntax_Error = 5,
        Invalid_SessionID = 3,
        Invalid_EnumId = 4,
        Connect_Side_NOT_DEFINED = 6,
        Illigal_CP_NAME = 7,
        Connect_To_Side_NOT_Allowed = 8
};
class MockWinFiolDriver: public WinFIOLDriver
{
public:
    MockWinFiolDriver(std::string a) :WinFIOLDriver(a){}
    MOCK_METHOD3(connect,Status(std::string,ConnectRequest::ApNodeSide,ConnectRequest::ApNode));
    MOCK_METHOD1(sendData,void(std::string));
    MOCK_METHOD1(readData,bool(std::string &));
    MOCK_METHOD0(terminateSession,int());
    MOCK_METHOD2(sendControlChar,Status(int,int));
};

TEST(WinFIOLClient_connect,ValidConnection_tokname__ALLBC)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillRepeatedly(Return(Status::OK));
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("\3>"), Return(true)));
    WinFIOLClient wfc(mfd,"");

    EXPECT_EQ(Okay,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT__ALLBC"));
}


TEST(WinFIOLClient_connect,ConnectionFailed_INCORRECT_SIDE)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillRepeatedly(Return(Status::OK));
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("not defined cp "), Return(true)))
        .WillOnce(DoAll(SetArgReferee<0>("not defined cp "), Return(false)));
    EXPECT_CALL(*mfd,terminateSession()).Times(AtLeast(1));
    WinFIOLClient wfc(mfd,"");

    EXPECT_EQ(Connect_Side_NOT_DEFINED,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT__ALLBC"));
}

TEST(WinFIOLClient_connect,ConnectionFailed_INVALID_NEID)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::INVALID_ARGUMENT, "Invalid NeID");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillRepeatedly(Return(obj));
    WinFIOLClient wfc(mfd,"");

    EXPECT_EQ(Invalid_NEID,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT__ALLBC"));
}

TEST(WinFIOLClient_connect,ConnectionFailed_INCORRECT_CP)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillRepeatedly(Return(Status::OK));
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("Illegal (config)"), Return(true)))
        .WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(false)));
    EXPECT_CALL(*mfd,terminateSession()).Times(AtLeast(1));
    WinFIOLClient wfc(mfd,"");

    EXPECT_EQ(Illigal_CP_NAME,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT__OPGROUP"));
}

TEST(WinFIOLClient_connect,ConnectionFailed_INVALID_ENMUID)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::INVALID_ARGUMENT, "Invalid EnmUID");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillRepeatedly(Return(obj));
    WinFIOLClient wfc(mfd,"");

    EXPECT_EQ(Invalid_EnumId,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT__ALLBCD"));
}

TEST(WinFIOLClient_connect,ConnectionFailed_INVALID_SESSIONID)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::INVALID_ARGUMENT, "Invalid SessionID");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillRepeatedly(Return(obj));
    WinFIOLClient wfc(mfd,"");

    EXPECT_EQ(Invalid_SessionID,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT-ALLBCD"));
}

TEST(WinFIOLClient_connect,ConnectionFailed_INVALID_ARGUMENT)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::INVALID_ARGUMENT, "Syntax problem");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillRepeatedly(Return(obj));

    WinFIOLClient wfc(mfd,"");
    int status = wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT__CP1AB");
    EXPECT_EQ(Syntax_Error,status);
}

TEST(WinFIOLClient_connect,ValidConnection_Tokname_SIDE_STANDBY){
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillRepeatedly(Return(Status::OK));
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(true)))
        .WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(false)));

    WinFIOLClient wfc(mfd,"");
    EXPECT_EQ(Okay,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT__CP1,SIDE=STANDBY"));
}

TEST(WinFIOLClient_connect,ConnectionFailed_SIDE_NOT_ALLOWED)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillRepeatedly(Return(Status::OK));
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("not allowed (config)"), Return(true)))
        .WillOnce(DoAll(SetArgReferee<0>("not allowed (config)"), Return(false)));
    EXPECT_CALL(*mfd,terminateSession()).Times(AtLeast(1));

    WinFIOLClient wfc(mfd,"");
    EXPECT_EQ(Connect_To_Side_NOT_Allowed,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT__CP1,SIDE=STANDBY"));
}

TEST(WinFIOLClient_connect,ValidConnection_Tokname_NODE_A)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillOnce(Return(Status::OK));
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(true)))
        .WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(false)));

    WinFIOLClient wfc(mfd,"");
    EXPECT_EQ(Okay,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT,NODE=A"));
}

TEST(WinFIOLClient_connect,ConnectionFailed_ConnectionClosed)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillRepeatedly(Return(Status::OK));
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("Connection closed (config)"), Return(true)));

    EXPECT_CALL(*mfd,terminateSession()).Times(AtLeast(1));

    WinFIOLClient wfc(mfd,"");
    EXPECT_EQ(Okay,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT,NODE=A"));
}

TEST(WinFIOLClient_connect,ValidConnection_Tokname_NODE_B)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillOnce(Return(Status::OK));
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(true)))
    .WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(false)));

    WinFIOLClient wfc(mfd,"");
    EXPECT_EQ(Okay,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT,NODE=B"));
}

TEST(WinFIOLClient_connect,ConnectionFailed_CONNECTION_INTERRUPTED)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillRepeatedly(Return(Status::OK));
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("CONNECTION INTERRUPTED (config)"), Return(true)));

    WinFIOLClient wfc(mfd,"");
    EXPECT_EQ(Okay,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT,NODE=B"));
}

TEST(WinFIOLClient_connect,ValidConnection_Tokname_NODE_C)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillOnce(Return(Status::OK));
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(true)))
        .WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(false)));

    WinFIOLClient wfc(mfd,"");
    EXPECT_EQ(Okay,wfc.connect("NE=MSC_BLADE_CLUSTER_ELEMENT,NODE=C"));
}

TEST(WinFIOLClient_connect,ValidConnection_Tokname_SIDE_EXECUTIVE)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,connect(_,_,_)).WillOnce(Return(Status::OK));
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(true)))
        .WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(false)));

    WinFIOLClient wfc(mfd,"");
    EXPECT_EQ(Okay,wfc.connect("NE=VMSC900,SIDE=EXECUTIVE"));
}

TEST(WinFIOLClient_connect,ValidConnection_Tokname_AD_XYZ)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");

    EXPECT_CALL(*mfd,connect(_,_,_)).WillOnce(Return(Status::OK));
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(true)))
        .WillOnce(DoAll(SetArgReferee<0>("(config)"), Return(false)));

    WinFIOLClient wfc(mfd,"");
    EXPECT_EQ(Okay,wfc.connect("NE=VMSC900,SIDE=EXECUTIVE, AD=535"));
}

TEST(WinFIOLClient_Disconnect,Disconnect_Success)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));  
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("Connection closed"), Return(true)));

    EXPECT_CALL(*mfd,terminateSession()).Times(AtLeast(1));
    WinFIOLClient wfc(mfd,"\3>");
    EXPECT_EQ(Okay,wfc.disconnect());
}

TEST(WinFIOLClient_Disconnect,Disconnect_Default_Prompt)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    EXPECT_CALL(*mfd,terminateSession()).Times(AtLeast(1));
    WinFIOLClient wfc(mfd,"cp ");
    EXPECT_EQ(Okay,wfc.disconnect());
}

TEST(WinFIOLClient_sendData,showCommandPositive)
{

    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::OK, "OKAY");
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("Show Command Response"), Return(true)))
        .WillRepeatedly(DoAll(SetArgReferee<0>("\3>"), Return(false)));
    WinFIOLClient wfc(mfd,"");
    wfc.sendData("show");
    std::string  my_response = wfc.getResponsedata();
    EXPECT_EQ(my_response,"Show Command Response");

}
TEST(WinFIOLClient_sendData,showCommandNegative)
{

    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::OK, "OKAY");
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("\3<Show Command Response"), Return(true)))
        .WillRepeatedly(DoAll(SetArgReferee<0>("\3<"), Return(false)));
    WinFIOLClient wfc(mfd,"");
    wfc.sendData("show");
    std::string  my_response = wfc.getResponsedata();
    EXPECT_EQ(my_response,"Show Command Response");

}

TEST(WINFIOLClient_sendData,labup_TEST_POSITIVE)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::OK, "OKAY");
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("ORDERED"), Return(true)))
        .WillRepeatedly(DoAll(SetArgReferee<0>("ORDERED"), Return(false)));
    EXPECT_CALL(*mfd,sendControlChar(_,_)).WillRepeatedly(Return(obj));
    WinFIOLClient wfc(mfd,"");
    wfc.sendData("labup;");
    std::string  my_response = wfc.getResponsedata();
    EXPECT_EQ(my_response,"ORDERED");
}

TEST(WINFIOLClient_sendData,labup_TEST_Negative)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::OK, "OKAY");
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>(" "), Return(true)))
        .WillRepeatedly(DoAll(SetArgReferee<0>(" "), Return(false)));
    EXPECT_CALL(*mfd,sendControlChar(_,_)).WillRepeatedly(Return(obj));

    WinFIOLClient wfc(mfd,"");
    wfc.sendData("labup;");
    std::string  my_response = wfc.getResponsedata();
    EXPECT_EQ(my_response,"");
}

TEST(WINFIOLClient_sendData,Sycle_Positive_Case)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::OK, "OKAY");
    std::stringstream confirmCmd;
    confirmCmd << "\r\n" << " " << "SYCLE;";
    std::stringstream confirmCmd1;
    confirmCmd1 << "\n " << "SYCLE;";

    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>(confirmCmd.str()), Return(true)))
        .WillOnce(DoAll(SetArgReferee<0>("\3<"), Return(true)))
        .WillRepeatedly(DoAll(SetArgReferee<0>(""), Return(false)));;
    EXPECT_CALL(*mfd,sendControlChar(_,_)).WillRepeatedly(Return(obj));

    WinFIOLClient wfc(mfd,"");
    wfc.sendData("SYCLE;");
    std::string  my_response = wfc.getResponsedata();
    EXPECT_EQ(my_response,confirmCmd1.str());
}

TEST(WINFIOLClient_sendData,Sycle_Negative_Case)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::OK, "OKAY");
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("SYCLE;"), Return(true)))
        .WillOnce(DoAll(SetArgReferee<0>("\3<"), Return(true)))
        .WillRepeatedly(DoAll(SetArgReferee<0>(""), Return(false)));;
    EXPECT_CALL(*mfd,sendControlChar(_,_)).WillRepeatedly(Return(obj));

    WinFIOLClient wfc(mfd,"");
    wfc.sendData("SYCLE;");
    std::string  my_response = wfc.getResponsedata();
    EXPECT_EQ(my_response,"SYCLE;");
}

TEST(WINFIOLClient_Order,Is_Ordered_True)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::OK, "OKAY");
   
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("ORDERED"), Return(true)))
    .WillOnce(DoAll(SetArgReferee<0>("\3<"), Return(true)))
    .WillRepeatedly(DoAll(SetArgReferee<0>(""), Return(false)));;
    EXPECT_CALL(*mfd,sendControlChar(_,_)).WillRepeatedly(Return(obj));
       
    WinFIOLClient wfc(mfd,"");
    wfc.orderedOn();
    wfc.sendData("SYRIP;");
}
TEST(WINFIOLClient_Order,Is_Ordered_True_Failed)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::OK, "OKAY");
   
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>(" "), Return(true)))
    .WillOnce(DoAll(SetArgReferee<0>("\3<"), Return(true)))
    .WillRepeatedly(DoAll(SetArgReferee<0>(""), Return(false)));      
    EXPECT_CALL(*mfd,sendControlChar(_,_)).WillRepeatedly(Return(obj));

    WinFIOLClient wfc(mfd,"");
    wfc.orderedOn();
    wfc.sendData("SYRIP;");
}
TEST(WINFIOLClient_Order,Is_Ordered_False)
{
    MockWinFiolDriver *mfd = new MockWinFiolDriver("12345");
    Status obj(StatusCode::OK, "OKAY");
   
    EXPECT_CALL(*mfd,sendData(_)).Times(AtLeast(1));
    EXPECT_CALL(*mfd,readData(_)).WillOnce(DoAll(SetArgReferee<0>("ORDERED"), Return(true)))
    .WillOnce(DoAll(SetArgReferee<0>("\3<"), Return(true)))
    .WillRepeatedly(DoAll(SetArgReferee<0>(""), Return(false)));;  
    EXPECT_CALL(*mfd,sendControlChar(_,_)).WillRepeatedly(Return(obj));
   
    WinFIOLClient wfc(mfd,"");
    wfc.orderedOff();
    wfc.sendData("SYRIP;");
}
