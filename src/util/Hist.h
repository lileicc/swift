/*
 * Hist.h
 *
 *  Created on: Jan 12, 2014
 *      Author: leili
 */
#include <map>
#pragma once

/**
 * histogram for storing answer
 */
template <class T>
class Hist {
private:
  std::map<T, double> table;
public:
  Hist() {};
  virtual ~Hist() {};
  void add(T element, double weight) {
    if (table.find(element) != table.end()) {
      weight += table[element];
    }
    table[element] = weight;
  };

  std::map<T, double> & getResult(){
    return table;
  };
};


