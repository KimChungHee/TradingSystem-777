#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace testing;
using namespace std;

//  공통 인터페이스: 증권사 API 통합용
class IStockBroker {
public:
    virtual void login(const string& id, const string& pass) = 0;
    virtual void buy(const string& code, int price, int qty) = 0;
    virtual void sell(const string& code, int price, int qty) = 0;
    virtual int getPrice(const string& code) = 0;
    virtual ~IStockBroker() = default;
};

//  자동 매매 클래스: 증권사 API를 이용한 매매 로직 담당
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

//  테스트용 모의 증권사 클래스 (GMock)
class MockBroker : public IStockBroker {
public:
    MOCK_METHOD(void, login, (const string&, const string&), (override));
    MOCK_METHOD(void, buy, (const string&, int, int), (override));
    MOCK_METHOD(void, sell, (const string&, int, int), (override));
    MOCK_METHOD(int, getPrice, (const string&), (override));
};

//
//  테스트 케이스 시작
//

//  기능 요청 1: 로그인 기능은 증권사 API로 위임되어야 한다
TEST(AutoTraderTest, 로그인_증권사API에_위임) {
    MockBroker mock;
    AutoTrader trader(&mock);

    EXPECT_CALL(mock, login("user", "1234")).Times(1);

    trader.login("user", "1234");
}

//  기능 요청 2: 예산 안에서 최대 수량 매수 (가격 = 5000, 예산 = 10000 → 수량 2)
TEST(AutoTraderTest, 예산내_최대수량_매수_성공케이스) {
    MockBroker mock;
    AutoTrader trader(&mock);

    EXPECT_CALL(mock, getPrice("005930")).WillOnce(Return(5000));
    EXPECT_CALL(mock, buy("005930", 5000, 2)).Times(1);

    trader.buyNiceTiming("005930", 10000);
}

//  기능 요청 3: 가격이 너무 비싸면 매수 안함 (예산 10000, 가격 11000)
TEST(AutoTraderTest, 예산초과로_매수불가) {
    MockBroker mock;
    AutoTrader trader(&mock);

    EXPECT_CALL(mock, getPrice("005930")).WillOnce(Return(11000));
    EXPECT_CALL(mock, buy).Times(0);

    trader.buyNiceTiming("005930", 10000);
}

//  기능 요청 4: 현재가가 6000원 미만일 경우 수량만큼 매도
TEST(AutoTraderTest, 주가하락_시_매도진행) {
    MockBroker mock;
    AutoTrader trader(&mock);

    EXPECT_CALL(mock, getPrice("005930")).WillOnce(Return(5900));
    EXPECT_CALL(mock, sell("005930", 5900, 3)).Times(1);

    trader.sellNiceTiming("005930", 3);
}

//  기능 요청 5: 주가가 충분히 높으면 매도하지 않음
TEST(AutoTraderTest, 주가안정시_매도하지않음) {
    MockBroker mock;
    AutoTrader trader(&mock);

    EXPECT_CALL(mock, getPrice("005930")).WillOnce(Return(6100));
    EXPECT_CALL(mock, sell).Times(0);

    trader.sellNiceTiming("005930", 3);
}

//  GMock 실행 메인
int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
