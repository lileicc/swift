/*
 * Configuration.cpp
 *
 *  Stores shared configuration state for use by Translators.
 *
 *  Created on: Jan 28, 2014
 *      Author: leili
 */

#include "Configuration.h"

#include<iostream>


namespace swift {

Configuration* Configuration::config = NULL;

Configuration::Configuration() {
  // handle all defaults
  setValue("COMPUTE_LIKELIHOOD_IN_LOG", true);
  setValue("N_SAMPLES", 1000000);
  setValue("N_BURN_IN_SAMPLES", 500000);
  setValue("N_HIST_BUCKETS", 20);
  setValue("MODEL_OUT_FILENAME", "");
}

Configuration* Configuration::getConfiguration() {
  if (!config)
    config = new Configuration();
  return config;
}

bool Configuration::getBoolValue(std::string name) {
  return getValue(name) == "true";
}

int Configuration::getIntValue(std::string name) {
  return std::stoi(getValue(name));
}

Configuration::~Configuration() {
}

template<typename _T>
void Configuration::setValue(std::string name, _T value) {
  property[name] = std::to_string(value);
}

void Configuration::setValue(std::string name, std::string value) {
  property[name] = value;
}

void Configuration::setValue(std::string name, const char* value) {
  property[name] = std::string(value);
}

void Configuration::setValue(std::string name, bool value) {
  property[name] = (value ? "true": "false");
}

void Configuration::setValue(std::string name, int value) {
  property[name] = std::to_string(value);
}

std::string Configuration::getValue(std::string name) {
  auto x = property.find(name);
  if (x == property.end())
    return "";
  return x->second;
}

}
