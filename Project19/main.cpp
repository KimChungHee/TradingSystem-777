#include <iostream>
#include <string>

#include "AutoTradingSystem.h"
#include "gmock/gmock.h"

using namespace testing;
using namespace std;

class StockerBrokerMock : public StockerBroker {
public:
    MOCK_METHOD(int, buy, (std::string stockCode, int price, int quantity), (override));
    MOCK_METHOD(int, getPrice, (std::string stockCode, int minute), (override));
};

// ===================== TEST CASE =====================

// 증권사 선택 테스트
TEST(BrokerSelectTest, ShouldSelectKiwerBroker) {
    bool result = selectStockBroker("kiwer");
    EXPECT_TRUE(result);
}

TEST(BrokerSelectTest, ShouldSelectNemoBroker) {
    bool result = selectStockBroker("nemo");
    EXPECT_TRUE(result);
}

// 로그인 테스트
TEST(LoginTest, LoginWithCorrectCredentials_ShouldCallLoginAPI) {
    AutoTrader trader;
    bool success = trader.login("user1", "pass1");
    EXPECT_TRUE(success);
}

// buyNiceTiming - 예산 내 최대 수량 매수
TEST(BuyLogicTest, BuyNiceTiming_ShouldBuyMaximumQtyWithinBudget) {
    StockerBrokerMock mock;
    EXPECT_CALL(mock, getPrice(_, _))
        .Times(2)
        .WillOnce(Return(4900))
        .WillOnce(Return(5000));

    EXPECT_CALL(mock, buy("005930", 5000, 200))
        .Times(1);

    AutoTradingSystem trader{ &mock };

    bool result = trader.buyNiceTiming("005930", 10000);
    EXPECT_TRUE(result);
}

// buyNiceTiming - 현재가가 예산 초과인 경우 매수하지 않음
TEST(BuyLogicTest, BuyNiceTiming_ShouldNotBuyIfTooExpensive) {
    StockerBrokerMock mock;
    EXPECT_CALL(mock, getPrice(_, _))
        .Times(2)
        .WillOnce(Return(5100))
        .WillOnce(Return(5000));

    AutoTradingSystem trader{ &mock };
    bool result = trader.buyNiceTiming("005930", 1000);
    EXPECT_FALSE(result);
}

// sellNiceTiming - 현재가가 낮으면 매도
TEST(SellLogicTest, SellNiceTiming_ShouldSellIfPriceFalls) {
    AutoTrader trader;
    bool result = trader.sellNiceTiming("005930", 3);
    EXPECT_TRUE(result);
}

// sellNiceTiming - 현재가가 충분히 높으면 매도하지 않음
TEST(SellLogicTest, SellNiceTiming_ShouldNotSellIfPriceHigh) {
    AutoTrader trader;
    bool result = trader.sellNiceTiming("005930", 3);
    EXPECT_FALSE(result);
}

// ===================== 증권사별 상세 테스트 =====================

// 키워 증권사: 로그인, 매수, 매도, 현재가
TEST(KiwerTest, LoginBuySellPriceWithKiwer) {
    selectStockBroker("kiwer");
    AutoTrader trader;
    EXPECT_TRUE(trader.login("kiwer_user", "kiwer_pass"));
    EXPECT_TRUE(trader.buy("000660", 6000, 5));
    EXPECT_TRUE(trader.sell("000660", 6100, 2));
    int price = trader.getPrice("000660");
    EXPECT_GT(price, 0);
}

// 네모 증권사: 인증, 매수, 매도, 현재가
TEST(NemoTest, LoginBuySellPriceWithNemo) {
    selectStockBroker("nemo");
    AutoTrader trader;
    EXPECT_TRUE(trader.login("nemo_user", "nemo_pass"));
    EXPECT_TRUE(trader.buy("035420", 7000, 3));
    EXPECT_TRUE(trader.sell("035420", 7200, 1));
    int price = trader.getPrice("035420");
    EXPECT_GT(price, 0);
}

int main() {
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}