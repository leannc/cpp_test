#pragma once


class BankServer
{
public:
    virtual ~BankServer() = default;
    virtual void Connect() = 0;
    virtual void Disconnect() = 0;
    virtual int GetBalance(int account_num) = 0;
    virtual bool Debit(int account_num,int amount) = 0;
};