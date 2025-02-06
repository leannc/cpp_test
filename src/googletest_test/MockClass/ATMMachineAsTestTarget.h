#include "../UseCase.h"
#include "BankServer.h"

class ATMMachineAsTestTarget {
public:
    ATMMachineAsTestTarget(BankServer* bankServer) : bank_(bankServer) {}
    bool Withdraw(int account,int amount) { 
        bank_->Connect();
        if (amount > bank_->GetBalance(account)) {
            std::cout << "there is not enough money in the account" << std::endl;
            return false;
        }
        bool result = bank_->Debit(account, amount);
        bank_->Disconnect();
        return result;
    }

private:
    BankServer* bank_;
};