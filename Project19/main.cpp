#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace testing;
using namespace std;

// ===================== TEST CASE =====================

// sellNiceTiming - 현재가가 낮으면 매도
TEST(SellLogicTest, SellNiceTiming_ShouldSellIfPriceFalls) {
    AutoTrader trader;
    trader.sellNiceTiming("005930", 3);
    // 기대 결과: 현재가가 기준치보다 낮으면 지정 수량만큼 매도
}

// sellNiceTiming - 현재가가 충분히 높으면 매도하지 않음
TEST(SellLogicTest, SellNiceTiming_ShouldNotSellIfPriceHigh) {
    AutoTrader trader;
    trader.sellNiceTiming("005930", 3);
    // 기대 결과: 현재가가 충분히 높으면 매도하지 않음
}



int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}