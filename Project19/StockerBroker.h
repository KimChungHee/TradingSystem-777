#pragma once

class StockerBroker {
public:
	virtual int getPrice(std::string stockCode, int minute) = 0;
	virtual int buy(std::string stockCode, int price, int quantity) = 0;
};

class KiwerDriver : public StockerBroker {

};

class NemoDriver : public StockerBroker {

};
