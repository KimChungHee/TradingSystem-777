#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace testing;
using namespace std;

// ===================== TEST CASE =====================

// buyNiceTiming - ���� �� �ִ� ���� �ż�
// ����: ���簡 �������� ���� �� �ִ� ������ �ż���
TEST(BuyLogicTest, BuyNiceTiming_ShouldBuyMaximumQtyWithinBudget) {
    AutoTrader trader;
    trader.buyNiceTiming("005930", 10000);
    // ��� ���: getPrice()�� ���� �޾ƿ� ���� �������� �ִ� ���� �ż�
}

// buyNiceTiming - ���簡�� ���� �ʰ��� ��� �ż����� ����
TEST(BuyLogicTest, BuyNiceTiming_ShouldNotBuyIfTooExpensive) {
    AutoTrader trader;
    trader.buyNiceTiming("005930", 1000);
    // ��� ���: ���簡�� �ʹ� ��θ� �ż� ���� �������� ����
}



int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}