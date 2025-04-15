#include "AutoTradingSystem.h"

AutoTradingSystem::AutoTradingSystem(StockerBroker* stockBroker)
	: stockBroker(stockBroker)
{
}

void AutoTradingSystem::selectStockBroker(string nameOfStockBroker) {
	if (nameOfStockBroker == "kiwer")
		stockBroker = new KiwerDriver();
	else if (nameOfStockBroker == "nemo")
		stockBroker = new NemoDriver();
}

string AutoTradingSystem::getStockBroker() {
	return stockBroker->getName();
}

void AutoTradingSystem::login(string id, string pass) {
	stockBroker->login(id, pass);
}

bool AutoTradingSystem::buy(string code, int price, int amount) {
	return stockBroker->buy(code, price, amount);
}

bool AutoTradingSystem::sell(string code, int price, int amount) {
	return stockBroker->sell(code, price, amount);
}

int AutoTradingSystem::getPrice(string code) {
	return stockBroker->getPrice(code);
}

bool AutoTradingSystem::buyNiceTiming(string code, int price) {
	const int Budget = 1000000;
	int price_before, price_after;

	price_before = stockBroker->getPrice(code);
	price_after = stockBroker->getPrice(code);

	if (price_after > price_before) {
		if (Budget < price_after)
			return false;
		stockBroker->buy(code, price_after, Budget / price_after);
		return true;
	}
	else if (price_after < price) {
		stockBroker->buy(code, price, Budget / price);
		return true;
	}
	return false;
}

