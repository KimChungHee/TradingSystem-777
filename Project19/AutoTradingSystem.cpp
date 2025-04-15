#include "AutoTradingSystem.h"

void AutoTradingSystem::selectStockBroker(std::string nameOfStockBroker) {

}

bool AutoTradingSystem::buyNiceTiming(std::string stockCode, int price) {
	const int Budget = 1000000;
	int price_before, price_after;

	price_before = stockBroker->getPrice(stockCode, 0);
	price_after = stockBroker->getPrice(stockCode, 0);

	if (price_after > price_before) {
		if (Budget < price_after)
			return false;
		stockBroker->buy(stockCode, price_after, Budget / price_after);
		return true;
	}
	else if (price_after < price) {
		stockBroker->buy(stockCode, price, Budget / price);
		return true;
	}
	return false;
}

