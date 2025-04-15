#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace testing;
using namespace std;

// ===================== TEST CASE =====================

// ���ǻ� ���� �׽�Ʈ
// ����: selectStockBroker�� ���� ���ϴ� ���ǻ縦 ������ �� �־�� �Ѵ�
TEST(BrokerSelectTest, ShouldSelectKiwerBroker) {
    selectStockBroker("kiwer");
    // ��� ���: ���������� Kiwer API�� ����ϴ� ������ ������
}

TEST(BrokerSelectTest, ShouldSelectNemoBroker) {
    selectStockBroker("nemo");
    // ��� ���: ���������� Nemo API�� ����ϴ� ������ ������
}

// �α��� �׽�Ʈ
// ����: ����ڰ� �Է��� ID/PASS�� ���ǻ� API�� ���ӵǴ��� Ȯ��
TEST(LoginTest, LoginWithCorrectCredentials_ShouldCallLoginAPI) {
    AutoTrader trader;
    trader.login("user1", "pass1");
    // ��� ���: login �Լ��� ���ǻ� API�� �ùٸ��� ���ӵ�
}

// �ż� �׽�Ʈ
// ����: �����ڵ�, ����, ������ ��Ȯ�ϰ� �ż� API�� ���޵Ǵ��� Ȯ��
TEST(BuyTest, BuyStock_ShouldCallBuyAPIWithCorrectParams) {
    AutoTrader trader;
    trader.buy("005930", 5000, 10);
    // ��� ���: buy("005930", 5000, 10)�� ���ǻ� API�� ���޵�
}

// �ŵ� �׽�Ʈ
// ����: �����ڵ�, ����, ������ ��Ȯ�ϰ� �ŵ� API�� ���޵Ǵ��� Ȯ��
TEST(SellTest, SellStock_ShouldCallSellAPIWithCorrectParams) {
    AutoTrader trader;
    trader.sell("005930", 5100, 5);
    // ��� ���: sell("005930", 5100, 5)�� ���ǻ� API�� ���޵�
}

// ���簡 Ȯ�� �׽�Ʈ
// ����: Ư�� �����ڵ��� ���簡�� ��û���� �� ������ ���� ���ϵǴ��� Ȯ��
TEST(PriceTest, GetCurrentPrice_ShouldReturnCorrectPrice) {
    AutoTrader trader;
    int price = trader.getPrice("005930");
    EXPECT_GT(price, 0);  // ���簡�� 0���� Ŀ�� �Ѵٴ� ����
}

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