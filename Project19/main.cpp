#include <iostream>
#include <string>

#include "AutoTradingSystem.h"
#include "mock_driver.h"
#include "gmock/gmock.h"

using namespace testing;
using namespace std;


TEST(BrokerSelectTest, ShouldSelectKiwerBroker) {
	MockDriver mock;
	AutoTradingSystem  system{ &mock };
	system.selectStockBroker("kiwer");
	EXPECT_EQ(system.getStockBroker(), "kiwer");
}

TEST(BrokerSelectTest, ShouldSelectNemoBroker) {
	MockDriver mock;
	AutoTradingSystem  system{ &mock };
	system.selectStockBroker("nemo");
	EXPECT_EQ(system.getStockBroker(), "nemo");
}

// 로그인 테스트
TEST(LoginTest, LoginWithCorrectCredentials_ShouldCallLoginAPI) {
	MockDriver mock;
	AutoTradingSystem trader{ &mock };

	trader.selectStockBroker("kiwer");
	trader.login("user1", "pass1");

	trader.selectStockBroker("nemo");
	trader.login("user1", "pass1");
}

// 매수 테스트
TEST(BuyTest, BuyStock_ShouldCallBuyAPIWithCorrectParams) {
	MockDriver mock;
	AutoTradingSystem  trader{ &mock };
	
	EXPECT_CALL(mock, buy("005930", 5000, 10))
		.Times(1)
		.WillOnce(Return(true));

	bool result = trader.buy("005930", 5000, 10);
	EXPECT_TRUE(result);
}

// 매도 테스트
TEST(SellTest, SellStock_ShouldCallSellAPIWithCorrectParams) {
	MockDriver mock;
	AutoTradingSystem  trader{ &mock };

	EXPECT_CALL(mock, sell("005930", 5100, 5))
		.Times(1)
		.WillOnce(Return(true));

	bool result = trader.sell("005930", 5100, 5);
}

// 현재가 확인 테스트
TEST(PriceTest, GetCurrentPrice_ShouldReturnCorrectPrice) {
	MockDriver mock;
	AutoTradingSystem  trader{ &mock };

	EXPECT_CALL(mock, getPrice("005930"))
		.Times(1)
		.WillOnce(Return(true));

	int price = trader.getPrice("005930");	
	EXPECT_GT(price, 0);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}