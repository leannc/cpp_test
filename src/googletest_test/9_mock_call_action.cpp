#include "MockClass/ATMMachineAsTestTarget.h"
#include "MockClass/MockServer.h"

TEST(MockCallAction, SideEffects) {
  const int account = 123;
  const int amount = 2000;

  int test_variable = 1;
  int test_account;

  NiceMock<MockServer> mock_server;

  EXPECT_CALL(mock_server, GetBalance(123))
      .WillRepeatedly(DoAll(Assign(&test_variable, 2), SaveArg<0>(&test_account), Return(3000)));
  EXPECT_CALL(mock_server, Debit(_, _)).WillRepeatedly(Return(true));

  ATMMachineAsTestTarget atm(&mock_server);
  bool widthdraw_result = atm.Withdraw(account, amount);

  EXPECT_EQ(test_variable, 2);
  EXPECT_EQ(test_account, 123);
}
