#pragma once
#include <string>

class StockerBroker {
 protected:
  std::string name;

 public:
  StockerBroker(std::string name):name(name){}
  virtual std::string getName() = 0;
};

class KiwerDriver : public StockerBroker {
 public:
  KiwerDriver() : StockerBroker("kiwer") {}
  std::string getName() override { return name; }
};

class NemoDriver : public StockerBroker {
 public:
  NemoDriver() : StockerBroker("nemo") {}
  std::string getName() override { return name; }
};
