#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace testing;
using namespace std;

// ===================== TEST CASE =====================

// sellNiceTiming - ���簡�� ������ �ŵ�
TEST(SellLogicTest, SellNiceTiming_ShouldSellIfPriceFalls) {
    AutoTrader trader;
    trader.sellNiceTiming("005930", 3);
    // ��� ���: ���簡�� ����ġ���� ������ ���� ������ŭ �ŵ�
}

// sellNiceTiming - ���簡�� ����� ������ �ŵ����� ����
TEST(SellLogicTest, SellNiceTiming_ShouldNotSellIfPriceHigh) {
    AutoTrader trader;
    trader.sellNiceTiming("005930", 3);
    // ��� ���: ���簡�� ����� ������ �ŵ����� ����
}



int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}