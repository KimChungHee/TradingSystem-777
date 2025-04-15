#pragma once
#include <string>
#include "StockerBroker.h"

class AutoTradingSystem {
  StockerBroker *stockBroker;
 public:
  void selectStockBroker(std::string nameOfStockBroker);
};