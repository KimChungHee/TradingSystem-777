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
