#pragma once
#include "../UseCase.h"
#include "BankServer.h"

class MockServer : public BankServer {
 public:
  MOCK_METHOD(void, Connect, (), (override));
  MOCK_METHOD(void, Disconnect, (), (override));
  MOCK_METHOD(bool, Debit, (int, int), (override));
  MOCK_METHOD(int, GetBalance, (int), (override));
};
