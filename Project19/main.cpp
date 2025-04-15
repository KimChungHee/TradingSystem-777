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

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}