#pragma once
#include <string>
#include "StockerBroker.h"
using namespace std;

class AutoTradingSystem {
	StockerBroker* stockBroker;

public:
	AutoTradingSystem(StockerBroker* stockBroker);

	void selectStockBroker(string nameOfStockBroker);
	string getStockBroker();
	void login(string id, string pass);
	bool buy(string code, int price, int amount);
	bool sell(string code, int price, int amount);
	int getPrice(string code);
};