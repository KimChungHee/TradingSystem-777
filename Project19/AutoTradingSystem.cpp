#include "AutoTradingSystem.h"

AutoTradingSystem::AutoTradingSystem(StockerBroker* stockBroker)
	: mock(stockBroker)
{
}

void AutoTradingSystem::selectStockBroker(string nameOfStockBroker) {
	mock->selectStockBroker(nameOfStockBroker);
}

string AutoTradingSystem::getStockBroker() {
	return mock->getName();
}

bool AutoTradingSystem::login(string id, string pass) {
	return mock->login(id, pass);
}

bool AutoTradingSystem::buy(string code, int price, int amount) {
	return mock->buy(code, price, amount);
}

bool AutoTradingSystem::sell(string code, int price, int amount) {
	return mock->sell(code, price, amount);
}

int AutoTradingSystem::getPrice(string code) {
	return mock->getPrice(code);
}
