#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace testing;
using namespace std;

// ===================== TEST CASE =====================

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

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}