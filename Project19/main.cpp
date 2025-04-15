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

// ���ǻ� ���� �׽�Ʈ
TEST(BrokerSelectTest, ShouldSelectKiwerBroker) {
    bool result = selectStockBroker("kiwer");
    EXPECT_TRUE(result);
}

TEST(BrokerSelectTest, ShouldSelectNemoBroker) {
    bool result = selectStockBroker("nemo");
    EXPECT_TRUE(result);
}

// �α��� �׽�Ʈ
TEST(LoginTest, LoginWithCorrectCredentials_ShouldCallLoginAPI) {
    AutoTrader trader;
    bool success = trader.login("user1", "pass1");
    EXPECT_TRUE(success);
}

// buyNiceTiming - ���� �� �ִ� ���� �ż�
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

// buyNiceTiming - ���簡�� ���� �ʰ��� ��� �ż����� ����
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

// sellNiceTiming - ���簡�� ������ �ŵ�
TEST(SellLogicTest, SellNiceTiming_ShouldSellIfPriceFalls) {
    AutoTrader trader;
    bool result = trader.sellNiceTiming("005930", 3);
    EXPECT_TRUE(result);
}

// sellNiceTiming - ���簡�� ����� ������ �ŵ����� ����
TEST(SellLogicTest, SellNiceTiming_ShouldNotSellIfPriceHigh) {
    AutoTrader trader;
    bool result = trader.sellNiceTiming("005930", 3);
    EXPECT_FALSE(result);
}

// ===================== ���ǻ纰 �� �׽�Ʈ =====================

// Ű�� ���ǻ�: �α���, �ż�, �ŵ�, ���簡
TEST(KiwerTest, LoginBuySellPriceWithKiwer) {
    selectStockBroker("kiwer");
    AutoTrader trader;
    EXPECT_TRUE(trader.login("kiwer_user", "kiwer_pass"));
    EXPECT_TRUE(trader.buy("000660", 6000, 5));
    EXPECT_TRUE(trader.sell("000660", 6100, 2));
    int price = trader.getPrice("000660");
    EXPECT_GT(price, 0);
}

// �׸� ���ǻ�: ����, �ż�, �ŵ�, ���簡
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