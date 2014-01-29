/*
 * Configuration.h
 *
 *  Created on: Jan 28, 2014
 *      Author: leili
 */

#pragma once
#include <map>
#include <string>

namespace swift {

class Configuration {
public:
  static Configuration* getConfiguration();
  template <typename _T=std::string>
  void setValue(std::string name, _T value);
  std::string getValue(std::string name);
  bool getBoolValue(std::string name);
  int getIntValue(std::string name);

private:
  Configuration();
  ~Configuration();
  std::map<std::string, std::string> property;
  static Configuration* config;
};

Configuration* Configuration::config = nullptr;
  
Configuration::Configuration(){
  setValue("COMPUTE_LIKELIHOOD_IN_LOG", false);
}

Configuration* Configuration::getConfiguration(){
  if (!config)
    config = new Configuration();
  return config;
}

inline bool Configuration::getBoolValue(std::string name) {
  return getValue(name) == "true";
}

inline int Configuration::getIntValue(std::string name) {
  return std::stoi(getValue(name));
}

inline Configuration::~Configuration() {
}

template <typename _T>
inline void Configuration::setValue(std::string name, _T value) {
  property[name] = std::to_string(value);
}


inline std::string Configuration::getValue(std::string name) {
  auto x = property.find(name);
  if (x == property.end())
    return "";
  return x->second;
}


}
