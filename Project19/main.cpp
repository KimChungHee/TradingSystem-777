#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace testing;
using namespace std;

//  ���� �������̽�: ���ǻ� API ���տ�
class IStockBroker {
public:
    virtual void login(const string& id, const string& pass) = 0;
    virtual void buy(const string& code, int price, int qty) = 0;
    virtual void sell(const string& code, int price, int qty) = 0;
    virtual int getPrice(const string& code) = 0;
    virtual ~IStockBroker() = default;
};

//  �ڵ� �Ÿ� Ŭ����: ���ǻ� API�� �̿��� �Ÿ� ���� ���
class AutoTrader {
    IStockBroker* broker;
public:
    AutoTrader(IStockBroker* b) : broker(b) {}

    void login(const string& id, const string& pass) {
        broker->login(id, pass);
    }

    void buyNiceTiming(const string& code, int budget) {
        int price = broker->getPrice(code);
        int qty = budget / price;
        if (qty > 0) broker->buy(code, price, qty);
    }

    void sellNiceTiming(const string& code, int qty) {
        int price = broker->getPrice(code);
        if (price < 6000) broker->sell(code, price, qty);
    }
};

//  �׽�Ʈ�� ���� ���ǻ� Ŭ���� (GMock)
class MockBroker : public IStockBroker {
public:
    MOCK_METHOD(void, login, (const string&, const string&), (override));
    MOCK_METHOD(void, buy, (const string&, int, int), (override));
    MOCK_METHOD(void, sell, (const string&, int, int), (override));
    MOCK_METHOD(int, getPrice, (const string&), (override));
};

//
//  �׽�Ʈ ���̽� ����
//

//  ��� ��û 1: �α��� ����� ���ǻ� API�� ���ӵǾ�� �Ѵ�
TEST(AutoTraderTest, �α���_���ǻ�API��_����) {
    MockBroker mock;
    AutoTrader trader(&mock);

    EXPECT_CALL(mock, login("user", "1234")).Times(1);

    trader.login("user", "1234");
}

//  ��� ��û 2: ���� �ȿ��� �ִ� ���� �ż� (���� = 5000, ���� = 10000 �� ���� 2)
TEST(AutoTraderTest, ���곻_�ִ����_�ż�_�������̽�) {
    MockBroker mock;
    AutoTrader trader(&mock);

    EXPECT_CALL(mock, getPrice("005930")).WillOnce(Return(5000));
    EXPECT_CALL(mock, buy("005930", 5000, 2)).Times(1);

    trader.buyNiceTiming("005930", 10000);
}

//  ��� ��û 3: ������ �ʹ� ��θ� �ż� ���� (���� 10000, ���� 11000)
TEST(AutoTraderTest, �����ʰ���_�ż��Ұ�) {
    MockBroker mock;
    AutoTrader trader(&mock);

    EXPECT_CALL(mock, getPrice("005930")).WillOnce(Return(11000));
    EXPECT_CALL(mock, buy).Times(0);

    trader.buyNiceTiming("005930", 10000);
}

//  ��� ��û 4: ���簡�� 6000�� �̸��� ��� ������ŭ �ŵ�
TEST(AutoTraderTest, �ְ��϶�_��_�ŵ�����) {
    MockBroker mock;
    AutoTrader trader(&mock);

    EXPECT_CALL(mock, getPrice("005930")).WillOnce(Return(5900));
    EXPECT_CALL(mock, sell("005930", 5900, 3)).Times(1);

    trader.sellNiceTiming("005930", 3);
}

//  ��� ��û 5: �ְ��� ����� ������ �ŵ����� ����
TEST(AutoTraderTest, �ְ�������_�ŵ���������) {
    MockBroker mock;
    AutoTrader trader(&mock);

    EXPECT_CALL(mock, getPrice("005930")).WillOnce(Return(6100));
    EXPECT_CALL(mock, sell).Times(0);

    trader.sellNiceTiming("005930", 3);
}

//  GMock ���� ����
int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
