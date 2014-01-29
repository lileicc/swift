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
  static Configuration& getConfiguration();
  template <typename _T=std::string>
  void setProperty(std::string name, _T value);
  template <typename _T=std::string>
  _T getProperty();

private:
  Configuration();
  ~Configuration();
  std::map<std::string, std::string> property;
  static Configuration config;
};

Configuration::Configuration(){
}

Configuration& Configuration::getConfiguration(){
  return config;
}

}
