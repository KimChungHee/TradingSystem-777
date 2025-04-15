#pragma once
#include <string>
#include "kiwer_api.cpp"
#include "nemo_api.cpp"

using namespace std;

class StockerBroker {
protected:
	std::string name;

public:
	StockerBroker(std::string name) :name(name) {}
	virtual string getName() = 0;
	virtual bool login(string id, string pass) = 0;
	virtual bool buy(string code, int price, int amount) = 0;
	virtual bool sell(string code, int price, int amount) = 0;
	virtual int getPrice(string code) = 0;

	StockerBroker() = default;
};

class KiwerDriver : public StockerBroker {
public:
	KiwerDriver() : StockerBroker("kiwer") {}
	string getName() override { return name; }
	bool login(string id, string pass) {
		kiwerAPI.login(id, pass);
		return true;
	}

	bool buy(string code, int price, int amount) override {
		kiwerAPI.buy(code, amount, price);
		return true;
	}

	bool sell(string code, int price, int amount) override {
		kiwerAPI.sell(code, amount, price);
		return true;
	}

	int getPrice(string code) override {
		return kiwerAPI.currentPrice(code);
	}

private:
	KiwerAPI kiwerAPI;
};

class NemoDriver : public StockerBroker {
public:
	NemoDriver() : StockerBroker("nemo") {}
	std::string getName() override { return name; }

	bool login(string id, string pass) { 
		nemoAPI.certification(id, pass);
		return true;
	}

	bool buy(string code, int price, int amount) override {
		nemoAPI.purchasingStock(code, price, amount);
		return true;
	}

	bool sell(string code, int price, int amount) override {
		nemoAPI.sellingStock(code, price, amount);
		return true;
	}

	int getPrice(string code) override {
		return nemoAPI.getMarketPrice(code, 5);
	}
private:
	NemoAPI nemoAPI;
};
