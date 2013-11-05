/*
 * Symbol.h
 *
 *  Created on: Oct 29, 2013
 *      Author: yiwu
 */

#pragma once

#include<string>

namespace swift {
namespace absyn {

class Symbol {
  std::string value;
public:
  Symbol(std::string v = "");
  ~Symbol();

  const std::string& getValue() const;
};

}
}
