#include <iostream>
#include <string>

#include "AutoTradingSystem.h"
#include "gmock/gmock.h"

using namespace testing;
using namespace std;

// ===================== TEST CASE =====================

// 증권사 선택 테스트
// 설명: selectStockBroker를 통해 원하는 증권사를 선택할 수 있어야 한다
TEST(BrokerSelectTest, ShouldSelectKiwerBroker) {
  AutoTradingSystem system;
  system.selectStockBroker("kiwer");
  EXPECT_EQ(system.getStockBroker(), "kiwer");
}

TEST(BrokerSelectTest, ShouldSelectNemoBroker) {
  AutoTradingSystem system;
  system.selectStockBroker("nemo");
  EXPECT_EQ(system.getStockBroker(), "nemo");
}

int main() {
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}