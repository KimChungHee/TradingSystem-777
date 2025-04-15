#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace testing;
using namespace std;

// ===================== TEST CASE =====================

// buyNiceTiming - 예산 내 최대 수량 매수
// 설명: 현재가 기준으로 예산 내 최대 수량을 매수함
TEST(BuyLogicTest, BuyNiceTiming_ShouldBuyMaximumQtyWithinBudget) {
    AutoTrader trader;
    trader.buyNiceTiming("005930", 10000);
    // 기대 결과: getPrice()를 통해 받아온 가격 기준으로 최대 수량 매수
}

// buyNiceTiming - 현재가가 예산 초과인 경우 매수하지 않음
TEST(BuyLogicTest, BuyNiceTiming_ShouldNotBuyIfTooExpensive) {
    AutoTrader trader;
    trader.buyNiceTiming("005930", 1000);
    // 기대 결과: 현재가가 너무 비싸면 매수 로직 수행하지 않음
}



int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}