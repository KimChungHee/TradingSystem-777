#include <iostream>
#include <string>

#include "StockerBroker.h"
#include "gmock/gmock.h"

using namespace std;
class MockDriver : public StockerBroker {
public:
    MOCK_METHOD(bool, login, (string id, string pass), (override));
    MOCK_METHOD(bool, buy, (string code, int price, int amount), (override));
    MOCK_METHOD(bool, sell, (string code, int price, int amount), (override));
    MOCK_METHOD(int, getPrice, (string code), (override));

    string getName() { return ""; }
    //bool login(string id, string pass) { return true; }

    MockDriver() = default;
};