#include <iostream>
#include <string>

#include "StockerBroker.h"
#include "gmock/gmock.h"

using namespace std;

struct Account {
    string id;
    string pass;
    int code;
    int amount;
};

class MockDriver : public StockerBroker {
public:
    MOCK_METHOD(bool, login, (string id, string pass), (override));
    MOCK_METHOD(bool, buy, (string code, int price, int amount), (override));
    MOCK_METHOD(bool, sell, (string code, int price, int amount), (override));
    MOCK_METHOD(int, getPrice, (string code), (override));

    string getName() { return stock->getName(); }

    void selectStockBroker(string nameOfStockBroker) {
        if (nameOfStockBroker == "kiwer")
            stock = new KiwerDriver();
        else if (nameOfStockBroker == "nemo")
            stock = new NemoDriver();
    }

    bool delegateLogin(string id, string pass)
    {
        if (id == kiwerAccount.id && pass == kiwerAccount.pass) {
            return stock->login(id, pass);
        }
        return false;
    }

    MockDriver() = default;

private:
    StockerBroker* stock;
    Account kiwerAccount = { "user1", "pass1", 0, 0 };
    Account NemoAccount = { "user2", "pass2", 0, 0 };;
};