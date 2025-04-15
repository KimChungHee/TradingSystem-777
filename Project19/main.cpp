#include <iostream>
#include <string>

#include "AutoTradingSystem.h"
#include "gmock/gmock.h"

using namespace testing;
using namespace std;

// ===================== TEST CASE =====================

// ���ǻ� ���� �׽�Ʈ
// ����: selectStockBroker�� ���� ���ϴ� ���ǻ縦 ������ �� �־�� �Ѵ�
TEST(BrokerSelectTest, ShouldSelectKiwerBroker) {
  AutoTradingSystem system;
  system.selectStockBroker("kiwer");
  // ��� ���: ���������� Kiwer API�� ����ϴ� ������ ������
}

TEST(BrokerSelectTest, ShouldSelectNemoBroker) {
  AutoTradingSystem system;
  system.selectStockBroker("nemo");
  // ��� ���: ���������� Nemo API�� ����ϴ� ������ ������
}

int main() {
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}