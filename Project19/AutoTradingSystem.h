#pragma once
#include <string>
#include "StockerBroker.h"

class AutoTradingSystem {
	StockerBroker *stockBroker;
 public:
	AutoTradingSystem(StockerBroker* stockBroker) : stockBroker(stockBroker) {};
	void selectStockBroker(std::string nameOfStockBroker);
	bool buyNiceTiming(std::string stockCode, int price);
};