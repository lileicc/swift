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
  template<typename _T>
  void setValue(std::string name, _T value);
  void setValue(std::string name, std::string value);
  void setValue(std::string name, const char* value);
  void setValue(std::string name, bool value);
  std::string getValue(std::string name);
  bool getBoolValue(std::string name);
  int getIntValue(std::string name);

private:
  Configuration();
  ~Configuration();
  std::map<std::string, std::string> property;
  static Configuration* config;
};

}
