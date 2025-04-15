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

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}