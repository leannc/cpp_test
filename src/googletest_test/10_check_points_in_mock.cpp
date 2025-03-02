#include "MockClass/ATMMachineAsTestTarget.h"
#include "MockClass/MockServer.h"

TEST(CheckPointsInMock, InsertCheckPoints) {
  const int account = 123;
  const int amount = 2000;

  MockFunction<void(std::string check_point_name)> checkpoint;
  NiceMock<MockServer> mock_server;

  {
    InSequence s;
    EXPECT_CALL(checkpoint, Call("Start withdraw"));
    EXPECT_CALL(mock_server, GetBalance(123)).WillRepeatedly(Return(3000));
  }

  {
    InSequence s;
    EXPECT_CALL(mock_server, Debit(_, _)).WillRepeatedly(Return(true));
    EXPECT_CALL(checkpoint, Call("End withdraw"));
  }

  ATMMachineAsTestTarget atm(&mock_server);
  checkpoint.Call("Start withdraw");
  bool widthdraw_result = atm.Withdraw(account, amount);
  checkpoint.Call("End withdraw");
}
