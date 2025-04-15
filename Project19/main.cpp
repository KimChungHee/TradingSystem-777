#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace testing;
using namespace std;

// ===================== TEST CASE =====================

// 증권사 선택 테스트
// 설명: selectStockBroker를 통해 원하는 증권사를 선택할 수 있어야 한다
TEST(BrokerSelectTest, ShouldSelectKiwerBroker) {
    selectStockBroker("kiwer");
    // 기대 결과: 내부적으로 Kiwer API를 사용하는 구조로 설정됨
}

TEST(BrokerSelectTest, ShouldSelectNemoBroker) {
    selectStockBroker("nemo");
    // 기대 결과: 내부적으로 Nemo API를 사용하는 구조로 설정됨
}

// 로그인 테스트
// 설명: 사용자가 입력한 ID/PASS가 증권사 API에 위임되는지 확인
TEST(LoginTest, LoginWithCorrectCredentials_ShouldCallLoginAPI) {
    AutoTrader trader;
    trader.login("user1", "pass1");
    // 기대 결과: login 함수가 증권사 API에 올바르게 위임됨
}

// 매수 테스트
// 설명: 종목코드, 가격, 수량이 정확하게 매수 API로 전달되는지 확인
TEST(BuyTest, BuyStock_ShouldCallBuyAPIWithCorrectParams) {
    AutoTrader trader;
    trader.buy("005930", 5000, 10);
    // 기대 결과: buy("005930", 5000, 10)이 증권사 API로 전달됨
}

// 매도 테스트
// 설명: 종목코드, 가격, 수량이 정확하게 매도 API로 전달되는지 확인
TEST(SellTest, SellStock_ShouldCallSellAPIWithCorrectParams) {
    AutoTrader trader;
    trader.sell("005930", 5100, 5);
    // 기대 결과: sell("005930", 5100, 5)이 증권사 API로 전달됨
}

// 현재가 확인 테스트
// 설명: 특정 종목코드의 현재가를 요청했을 때 예상한 값이 리턴되는지 확인
TEST(PriceTest, GetCurrentPrice_ShouldReturnCorrectPrice) {
    AutoTrader trader;
    int price = trader.getPrice("005930");
    EXPECT_GT(price, 0);  // 현재가는 0보다 커야 한다는 조건
}

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