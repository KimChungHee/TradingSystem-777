#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace testing;
using namespace std;

// ===================== TEST CASE =====================

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

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}