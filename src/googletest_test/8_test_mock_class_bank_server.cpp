#include "MockClass/MockServer.h"
#include "MockClass/ATMMachineAsTestTarget.h"

TEST(AtmMachineTest, CannotWithDraw)
{
    const int account = 123;
    const int amount = 1000;

    NiceMock<MockServer> mock_server;
    ATMMachineAsTestTarget atm(&mock_server);
    bool widthdraw_result = atm.Withdraw(account, amount);

    EXPECT_FALSE(widthdraw_result);
}


TEST(AtmMachineTest, CanWithDrawOnCall)
{
    const int account = 123;
    const int amount = 2000;

    NiceMock<MockServer> mock_server;

    //----为GetBalance函数设置返回值，只要等于123，或者大于1000的，都返回3000。
    ON_CALL(mock_server, GetBalance(AnyOf(Eq(123), Gt(1000)))).WillByDefault(Return(3000));

    //----为Debit函数设置返回值，只有第一个参数小于第二个参数，才会返回true。
    ON_CALL(mock_server, Debit(_,_))
            .With(AllOf(Args<0,1>(Lt())))
            .WillByDefault(Return(true));


    ATMMachineAsTestTarget atm(&mock_server);
    bool widthdraw_result = atm.Withdraw(account, amount);
    bool widthdraw_result2 = atm.Withdraw(account+1, amount);
    bool widthdraw_result3 = atm.Withdraw(account+1000, amount);  //可以过，因为超过了1000，满足GetBalance的Matcher
    bool widthdraw_result4 = atm.Withdraw(account+2000, amount);  //不能过，因为Debit的条件没满足，account>amount了。虽然这个对比没有油盐，但是可以作为一个功能展示。

    EXPECT_TRUE(widthdraw_result);
    EXPECT_FALSE(widthdraw_result2);
    EXPECT_TRUE(widthdraw_result3);
    EXPECT_FALSE(widthdraw_result4);
}


TEST(AtmMachineTest, ExpectCall)
{
    const int account = 123;
    const int amount = 2000;

    NiceMock<MockServer> mock_server;

    //---- 如果使用EXPECT_CALL的时候没有Times，也没有WillRepeatedly，那么默认是Times(1)，后面的调用都会失败。
    EXPECT_CALL(mock_server, GetBalance)
    .Times(AtMost(2))  
    .WillOnce(Return(3000))  //第一次调用返回3000
    .WillOnce(Return(500))  //第二次调用返回500，后面的依次类推
    .WillRepeatedly(Return(0)); //后面每次调用返回0

    EXPECT_CALL(mock_server, Debit(_,_))
            .With(Lt())  //可以对两个参数之间进行约束
            .Times(AtLeast(1)) //可以对调用次数进行约束
            .WillRepeatedly(Return(true));


    ATMMachineAsTestTarget atm(&mock_server);
    bool widthdraw_result = atm.Withdraw(account, amount);//可以过
    bool widthdraw_result2 = atm.Withdraw(account, amount);//不能过，因为GetBalance第二次就只会返回500了，不够amount；

    EXPECT_TRUE(widthdraw_result);
    EXPECT_FALSE(widthdraw_result2);

}


TEST(AtmMachineTest, UnExpectCall)
{
    const int account = 123;
    const int amount = 2000;

    NiceMock<MockServer> mock_server;

    //---- 如果使用EXPECT_CALL的时候没有Times，也没有WillRepeatedly，那么默认是Times(1)，后面的调用都会失败。
    EXPECT_CALL(mock_server, GetBalance(345))
    .WillRepeatedly(Return(2000)); //后面每次调用返回0

    EXPECT_CALL(mock_server, Debit(_,_))
            .WillRepeatedly(Return(true));

    EXPECT_CALL(mock_server, Connect)
    .Times(AtLeast(1)); 

    EXPECT_CALL(mock_server, Disconnect)
    .Times(AtLeast(1)); 

    ATMMachineAsTestTarget atm(&mock_server);
    bool widthdraw_result = atm.Withdraw(account, amount);//不能过，因为GetBalance的参数不对，它成了一个UnExpectCall，会直接导致fail。

    //----前面直接就fail了，与expect无关了，因为出现了unexpect call。
    EXPECT_FALSE(widthdraw_result);

}


TEST(AtmMachineTest, SequenceCall)
{
    const int account = 123;
    const int amount = 2000;

    NiceMock<MockServer> mock_server;
    Sequence s1;

    EXPECT_CALL(mock_server, Debit(_,_))
        .WillRepeatedly(Return(true))
        .InSequence(s1);

    EXPECT_CALL(mock_server, GetBalance(123))
        .WillRepeatedly(Return(2000))
        .InSequence(s1);

    ATMMachineAsTestTarget atm(&mock_server);
    bool widthdraw_result = atm.Withdraw(account, amount);//不能过，调用顺序指定的是先Debit再GetBalance，但是实际调用顺序是先GetBalance再Debit。

    //----前面直接就fail了，与expect无关了，因为顺序就错了
    EXPECT_FALSE(widthdraw_result);

}

TEST(AtmMachineTest, SequenceCallAfter)
{
    const int account = 123;
    const int amount = 2000;

    NiceMock<MockServer> mock_server;
    Expectation e_debit = EXPECT_CALL(mock_server,Debit);
    ExpectationSet e_debit_set;

    for(int i = 0; i < 5; i++) {
        e_debit_set += e_debit;    //----这种方式可以指定，Debit需要被调用5次，才能被后面的调用。
    }

    EXPECT_CALL(mock_server, GetBalance(123))
        .WillRepeatedly(Return(2000))
        .After(e_debit_set);  //----也可以 .After(e_debit)

    EXPECT_CALL(mock_server, Debit(_,_))
        .WillRepeatedly(Return(true));

    ATMMachineAsTestTarget atm(&mock_server);
    bool widthdraw_result = atm.Withdraw(account, amount);//不能过，调用顺序指定的是GetBalance要afterDebit，但是实际反的。

    //----前面直接就fail了，与expect无关了，因为顺序就错了
    EXPECT_FALSE(widthdraw_result);
}

TEST(AtmMachineTest, GlobalInSequenceCall)
{
    const int account = 123;
    const int amount = 2000;

    NiceMock<MockServer> mock_server;

    {
        InSequence seq;
        EXPECT_CALL(mock_server, Debit(_,_)).WillRepeatedly(Return(true));
        EXPECT_CALL(mock_server, GetBalance(123)).WillRepeatedly(Return(2000));
    }

    ATMMachineAsTestTarget atm(&mock_server);
    bool widthdraw_result = atm.Withdraw(account, amount);//不能过，调用顺序先Debit，再GetBalance，但是实际反的。

    //----前面直接就fail了，与expect无关了，因为顺序就错了
    EXPECT_FALSE(widthdraw_result);
}