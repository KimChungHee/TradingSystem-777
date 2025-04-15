#include "AutoTradingSystem.h"

void AutoTradingSystem::selectStockBroker(std::string nameOfStockBroker) {
  if (nameOfStockBroker == "kiwer")
    stockBroker = new KiwerDriver();
  else if (nameOfStockBroker == "nemo")
    stockBroker = new NemoDriver();
}

std::string AutoTradingSystem::getStockBroker() { 
    return stockBroker->getName(); }
